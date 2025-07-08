#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include <iostream>
#include <string>
#include <limits>    // Required for std::numeric_limits
#include <cstdlib>   // Required for rand()
#include <windows.h> // For Sleep function (Windows only)
#include <conio.h>   // For _getch()
#include <sstream>   // For capturing cout output

// Combat pace control functions
void combatPause(int milliseconds = 1500)
{
    Sleep(milliseconds); // Pause for specified milliseconds (Windows)
}

void combatWaitForKey(const std::string &message = "\nPress any key to continue...")
{
    std::cout << message;
    _getch();
}

// Forward declarations
class Player;
class Enemy;
class Boss;
class Map;

// Function declarations
void drawCombatScreen(Map &map, const Player &player, const Enemy &enemy, bool pause = true);
void drawCombatScreenBoss(Map &map, const Player &player, const Boss &boss, bool pause = true);
void clearScreen();

// Include headers after forward declarations
#include "Player.h"
#include "Enemy.h"
#include "GameMenu.h"
#include "Boss.h"
#include "ItemFactory.h"

// Variable global para el oro del jugador
extern int playerGold;
extern Inventory playerInventory;

const int MAX_LINES = 8; // Maximum number of lines to display in the message box

// ======= Combat against common enemy =======
// Returns true if the player survives, false if the player dies
bool Combat(Player &player, Enemy &enemy, Map &map)
{
    bool isPlayerAlive = true;

    std::string text[MAX_LINES];
    int lineCount = 0;

    while (player.getHealth() > 0 && enemy.getHealth() > 0)
    {
        // Prepare the text with attack options
        text[0] = "Choose your action:";
        text[1] = "1. Normal Attack (" + std::to_string(player.getAttack()) + " dmg)";
        text[2] = "2. Special Attack (" + std::to_string(player.getSpecialAttack()) + " dmg)";
        text[3] = "3. Use Healing Item";
        text[4] = "4. Use Damage Item";
        text[5] = "Enter option (1-4): ";
        lineCount = 6;

        // Set text in the map and display screen
        map.setPanelText(lineCount, text);
        clearScreen();
        drawCombatScreen(map, player, enemy);

        int option = 0;
        std::cin >> option;

        // Clear input buffer to prevent issues
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Validate input
        if (option < 1 || option > 4)
        {
            option = 1; // Default to normal attack
        }

        int damage = 0;
        bool playerUsedTurn = true; // Track if player's turn was consumed

        switch (option)
        {
        case 1:
            damage = player.getAttack();
            text[0] = "You used a normal attack!";
            map.setPanelText(1, text);
            drawCombatScreen(map, player, enemy, false);
            combatPause(1000); // Pause 1 second to show attack message

            enemy.receiveDamage(damage);
            text[1] = enemy.getName() + " health: " + std::to_string(enemy.getHealth());
            lineCount = 2;
            break;
        case 2:
            damage = player.getSpecialAttack();
            text[0] = "You used a special attack!";
            map.setPanelText(1, text);
            drawCombatScreen(map, player, enemy, false);
            combatPause(1000); // Pause 1 second to show attack message

            enemy.receiveDamage(damage);
            text[1] = enemy.getName() + " health: " + std::to_string(enemy.getHealth());
            lineCount = 2;
            break;
        case 3:
            // Use healing item - First check if player needs healing
            if (player.getHealth() >= player.getMaxHealth())
            {
                text[0] = "Your health is already full!";
                text[1] = "No need to use healing items.";
                lineCount = 2;
                playerUsedTurn = false; // Don't consume turn if health is full
            }
            else if (playerInventory.hasHealingItems())
            {
                text[0] = "=== HEALING ITEMS ===";
                text[1] = "Select an item to use:";
                lineCount = 2;

                // Create a list of available items with continuous numbering
                int availableItemIndices[8]; // Store actual inventory indices of available items
                int availableItems = 0;

                // Collect available items
                for (int i = 0; i < playerInventory.getHealingItemCount() && availableItems < 8; i++)
                {
                    if (playerInventory.getHealingItem(i).isAvailable())
                    {
                        availableItemIndices[availableItems] = i;
                        availableItems++;
                    }
                }

                // Display items in two columns with continuous numbering
                int leftColumnItems = (availableItems + 1) / 2; // Ceiling division

                // Display left column items
                for (int i = 0; i < leftColumnItems; i++)
                {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " +
                                           playerInventory.getHealingItem(itemIndex).getName() +
                                           " (+" + std::to_string(playerInventory.getHealingItem(itemIndex).getHealAmount()) +
                                           " HP, x" + std::to_string(playerInventory.getHealingItem(itemIndex).getQuantity()) + ")";
                    text[lineCount] = itemText;
                    lineCount++;
                }

                // Display right column items (if any)
                for (int i = leftColumnItems; i < availableItems; i++)
                {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " +
                                           playerInventory.getHealingItem(itemIndex).getName() +
                                           " (+" + std::to_string(playerInventory.getHealingItem(itemIndex).getHealAmount()) +
                                           " HP, x" + std::to_string(playerInventory.getHealingItem(itemIndex).getQuantity()) + ")";

                    // Add to the corresponding left column line
                    int leftLineIndex = lineCount - availableItems + i;
                    if (leftLineIndex >= 2 && leftLineIndex < lineCount)
                    {
                        text[leftLineIndex] += "     " + itemText; // Add spacing and right column item
                    }
                }

                if (availableItems > 0)
                {
                    text[lineCount] = "Enter item number (0 to cancel): ";
                    lineCount++;

                    map.setPanelText(lineCount, text);
                    clearScreen();
                    drawCombatScreen(map, player, enemy, false);

                    int itemChoice = 0;
                    std::cin >> itemChoice;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (itemChoice > 0 && itemChoice <= availableItems)
                    {
                        // Use the continuous numbering to get the actual inventory index
                        int actualInventoryIndex = availableItemIndices[itemChoice - 1];

                        if (playerInventory.useHealingItem(actualInventoryIndex + 1, player))
                        { // +1 because useHealingItem expects 1-based index
                            text[0] = "You used a healing item!";
                            text[1] = "Your health: " + std::to_string(player.getHealth());
                            lineCount = 2;
                        }
                        else
                        {
                            text[0] = "Couldn't use that item!";
                            lineCount = 1;
                            playerUsedTurn = false;
                        }
                    }
                    else
                    {
                        text[0] = "Cancelled item use.";
                        lineCount = 1;
                        playerUsedTurn = false;
                    }
                }
                else
                {
                    text[0] = "No healing items available!";
                    lineCount = 1;
                    playerUsedTurn = false;
                }
            }
            else
            {
                text[0] = "No healing items available!";
                lineCount = 1;
                playerUsedTurn = false; // Don't consume turn if no items
            }
            break;
        case 4:
            // Use damage item
            if (playerInventory.hasDamageItems())
            {
                text[0] = "=== DAMAGE ITEMS ===";
                text[1] = "Select an item to use:";
                lineCount = 2;

                // Create a list of available items with continuous numbering
                int availableItemIndices[8]; // Store actual inventory indices of available items
                int availableItems = 0;

                // Collect available items
                for (int i = 0; i < playerInventory.getDamageItemCount() && availableItems < 8; i++)
                {
                    if (playerInventory.getDamageItem(i).isAvailable())
                    {
                        availableItemIndices[availableItems] = i;
                        availableItems++;
                    }
                }

                // Display items in two columns with continuous numbering
                int leftColumnItems = (availableItems + 1) / 2; // Ceiling division

                // Display left column items
                for (int i = 0; i < leftColumnItems; i++)
                {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " +
                                           playerInventory.getDamageItem(itemIndex).getName() +
                                           " (" + std::to_string(playerInventory.getDamageItem(itemIndex).getDamage()) +
                                           " DMG, x" + std::to_string(playerInventory.getDamageItem(itemIndex).getQuantity()) + ")";
                    text[lineCount] = itemText;
                    lineCount++;
                }

                // Display right column items (if any)
                for (int i = leftColumnItems; i < availableItems; i++)
                {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " +
                                           playerInventory.getDamageItem(itemIndex).getName() +
                                           " (" + std::to_string(playerInventory.getDamageItem(itemIndex).getDamage()) +
                                           " DMG, x" + std::to_string(playerInventory.getDamageItem(itemIndex).getQuantity()) + ")";

                    // Add to the corresponding left column line
                    int leftLineIndex = lineCount - availableItems + i;
                    if (leftLineIndex >= 2 && leftLineIndex < lineCount)
                    {
                        text[leftLineIndex] += "     " + itemText; // Add spacing and right column item
                    }
                }

                if (availableItems > 0)
                {
                    text[lineCount] = "Enter item number (0 to cancel): ";
                    lineCount++;

                    map.setPanelText(lineCount, text);
                    clearScreen();
                    drawCombatScreen(map, player, enemy, false);

                    int itemChoice = 0;
                    std::cin >> itemChoice;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (itemChoice > 0 && itemChoice <= availableItems)
                    {
                        // Use the continuous numbering to get the actual inventory index
                        int actualInventoryIndex = availableItemIndices[itemChoice - 1];

                        if (playerInventory.useDamageItem(actualInventoryIndex + 1, player, enemy))
                        { // +1 because useDamageItem expects 1-based index
                            text[0] = "You used a damage item!";
                            text[1] = enemy.getName() + " health: " + std::to_string(enemy.getHealth());
                            lineCount = 2;
                        }
                        else
                        {
                            text[0] = "Couldn't use that item!";
                            lineCount = 1;
                            playerUsedTurn = false;
                        }
                    }
                    else
                    {
                        text[0] = "Cancelled item use.";
                        lineCount = 1;
                        playerUsedTurn = false;
                    }
                }
                else
                {
                    text[0] = "No damage items available!";
                    lineCount = 1;
                    playerUsedTurn = false;
                }
            }
            else
            {
                text[0] = "No damage items available!";
                lineCount = 1;
                playerUsedTurn = false; // Don't consume turn if no items
            }
            break;
        default:
            damage = player.getAttack();
            text[0] = "Invalid option! Using normal attack by default.";
            map.setPanelText(1, text);
            drawCombatScreen(map, player, enemy, false);
            combatPause(1500); // Pause 1.5 seconds to show invalid option message

            enemy.receiveDamage(damage);
            text[1] = enemy.getName() + " health: " + std::to_string(enemy.getHealth());
            lineCount = 2;
            break;
        }

        // Display the result of player's action
        map.setPanelText(lineCount, text);
        drawCombatScreen(map, player, enemy, false);

        // Pause to show action result
        std::cout << "\nPress any key to continue...";
        _getch();

        // Only continue to enemy turn if player actually used their turn
        if (!playerUsedTurn)
        {
            continue; // Skip enemy turn and let player choose again
        }

        // Logica cuando el enemigo es derrotado
        if (enemy.getHealth() <= 0)
        {
            player.addEnemyKill();

            // Increment global enemy counter and save progress
            GameMenu::incrementEnemiesDefeated();
            GameMenu::saveProgressAfterCombat("Combat Area");

            // Show victory message first
            text[0] = enemy.getName() + " was defeated!";
            text[1] = "Victory is yours!";
            lineCount = 2;
            map.setPanelText(lineCount, text);
            drawCombatScreen(map, player, enemy, false);
            combatPause(2000); // Pause 2 seconds to celebrate victory

            // Show collecting drops message
            text[0] = "Searching for battle rewards...";
            text[1] = "Looking through the defeated enemy...";
            lineCount = 2;
            map.setPanelText(lineCount, text);
            drawCombatScreen(map, player, enemy, false);
            combatPause(1500); // Pause 1.5 seconds for suspense

            // Store player state before drops
            int goldBefore = playerGold;
            int healingItemsBefore = 0;
            int damageItemsBefore = 0;

            // Count items before drops
            for (int i = 0; i < playerInventory.getHealingItemCount(); i++)
            {
                if (playerInventory.getHealingItem(i).isAvailable())
                {
                    healingItemsBefore += playerInventory.getHealingItem(i).getQuantity();
                }
            }
            for (int i = 0; i < playerInventory.getDamageItemCount(); i++)
            {
                if (playerInventory.getDamageItem(i).isAvailable())
                {
                    damageItemsBefore += playerInventory.getDamageItem(i).getQuantity();
                }
            }

            // Temporarily capture cout to suppress direct printing from giveDropsToPlayer
            std::streambuf *orig = std::cout.rdbuf();
            std::ostringstream buffer;
            std::cout.rdbuf(buffer.rdbuf());

            // Give enemy-specific drops (output will be captured)
            enemy.giveDropsToPlayer(playerInventory, playerGold);

            // Restore cout
            std::cout.rdbuf(orig);

            // Calculate what was gained
            int goldGained = playerGold - goldBefore;
            int healingItemsGained = 0;
            int damageItemsGained = 0;

            // Count items after drops
            for (int i = 0; i < playerInventory.getHealingItemCount(); i++)
            {
                if (playerInventory.getHealingItem(i).isAvailable())
                {
                    healingItemsGained += playerInventory.getHealingItem(i).getQuantity();
                }
            }
            for (int i = 0; i < playerInventory.getDamageItemCount(); i++)
            {
                if (playerInventory.getDamageItem(i).isAvailable())
                {
                    damageItemsGained += playerInventory.getDamageItem(i).getQuantity();
                }
            }
            healingItemsGained -= healingItemsBefore;
            damageItemsGained -= damageItemsBefore;

            // Show each reward with pauses
            if (goldGained > 0)
            {
                text[0] = "*** TREASURE FOUND! ***";
                text[1] = "You found " + std::to_string(goldGained) + " gold coins!";
                lineCount = 2;
                map.setPanelText(lineCount, text);
                drawCombatScreen(map, player, enemy, false);
                combatPause(2000); // Pause 2 seconds to enjoy the gold
            }

            if (healingItemsGained > 0)
            {
                text[0] = "*** HEALING ITEMS FOUND! ***";
                text[1] = "You found " + std::to_string(healingItemsGained) + " healing item(s)!";
                lineCount = 2;
                map.setPanelText(lineCount, text);
                drawCombatScreen(map, player, enemy, false);
                combatPause(2000); // Pause 2 seconds to see healing items
            }

            if (damageItemsGained > 0)
            {
                text[0] = "*** WEAPONS FOUND! ***";
                text[1] = "You found " + std::to_string(damageItemsGained) + " weapon(s)!";
                lineCount = 2;
                map.setPanelText(lineCount, text);
                drawCombatScreen(map, player, enemy, false);
                combatPause(2000); // Pause 2 seconds to see weapons
            }

            // Show final rewards summary
            text[0] = "=== BATTLE REWARDS SUMMARY ===";
            if (goldGained > 0 || healingItemsGained > 0 || damageItemsGained > 0)
            {
                text[1] = "Gold: +" + std::to_string(goldGained) + " (Total: " + std::to_string(playerGold) + ")";
                if (healingItemsGained > 0 || damageItemsGained > 0)
                {
                    text[2] = "Items: +" + std::to_string(healingItemsGained + damageItemsGained) + " new items!";
                    lineCount = 3;
                }
                else
                {
                    lineCount = 2;
                }
            }
            else
            {
                text[1] = "No items found this time...";
                text[2] = "Total Gold: " + std::to_string(playerGold);
                lineCount = 3;
            }
            map.setPanelText(lineCount, text);
            drawCombatScreen(map, player, enemy, false);
            combatPause(2000); // Pause 2 seconds to read rewards

            combatWaitForKey("\nPress any key to continue...");
            break;
        }

        // Enemy turn: normal attack
        int enemyDamage = enemy.getAttack();
        std::string enemyAction = enemy.getName() + " attacks with " + std::to_string(enemyDamage) + " damage!";

        // Show enemy attack message first
        text[0] = enemyAction;
        text[1] = ""; // Clear second line
        map.setPanelText(2, text);
        drawCombatScreen(map, player, enemy, false);
        combatPause(1200); // Pause 1.2 seconds to show enemy attack message

        // Apply damage with mitigation inside receiveDamage
        player.receiveDamage(enemyDamage);

        text[0] = enemyAction;
        text[1] = "Your health: " + std::to_string(player.getHealth());
        lineCount = 2;
        map.setPanelText(lineCount, text);
        drawCombatScreen(map, player, enemy, false);

        // Pause to show enemy attack result
        std::cout << "\nPress any key to continue...";
        _getch();

        if (player.getHealth() <= 0)
        {
            // Show dramatic defeat message
            text[0] = "You were defeated in battle...";
            text[1] = "Your vision fades to black...";
            lineCount = 2;
            map.setPanelText(lineCount, text);
            drawCombatScreen(map, player, enemy, false);
            combatPause(2500); // Pause 2.5 seconds for dramatic effect

            // Show final message
            text[0] = "GAME OVER";
            text[1] = "Your adventure has ended...";
            lineCount = 2;
            map.setPanelText(lineCount, text);
            drawCombatScreen(map, player, enemy, false);

            combatWaitForKey("\nPress any key to continue...");
            isPlayerAlive = false;

            // Show death screen
            GameMenu::displayDeathScreen();
            break;
        }
    }

    text[0] = "Combat ended.";
    lineCount = 1;
    map.setPanelText(lineCount, text);
    drawCombatScreen(map, player, enemy, false); // No pause here to avoid double input

    return isPlayerAlive;
}
// Returns true if the player survives, false if the player dies
bool CombatBosss(Player &player, Boss &boss, Map &map)
{
    bool isPlayerAlive = true;

    std::string text[MAX_LINES];
    int lineCount = 0;

    // Initial message
    text[0] = "*** BOSS BATTLE ***";
    text[1] = boss.getName() + " appears before you!";
    lineCount = 2;
    map.setPanelText(lineCount, text);
    clearScreen();
    drawCombatScreenBoss(map, player, boss, false); // No pause to avoid double input

    while (player.getHealth() > 0 && boss.getHealth() > 0)
    {
        // Prepare the text with attack options
        text[0] = "Choose your action:";
        text[1] = "1. Normal Attack (" + std::to_string(player.getAttack()) + " dmg)";
        text[2] = "2. Special Attack (" + std::to_string(player.getSpecialAttack()) + " dmg)";
        text[3] = "3. Use Healing Item";
        text[4] = "4. Use Damage Item";
        text[5] = "Enter option (1-4): ";
        lineCount = 6;

        // Set text in the map and display screen
        map.setPanelText(lineCount, text);
        clearScreen();
        drawCombatScreenBoss(map, player, boss, false); // No pause to avoid double input

        int option = 0;
        std::cin >> option;

        // Clear input buffer to prevent issues
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Validate input
        if (option < 1 || option > 4)
        {
            option = 1; // Default to normal attack
        }

        int damage = 0;
        bool playerUsedTurn = true; // Track if player's turn was consumed

        switch (option)
        {
        case 1:
            damage = player.getAttack();
            text[0] = "You used a normal attack!";
            boss.takeDamage(damage);
            text[1] = boss.getName() + " health: " + std::to_string(boss.getHealth());
            lineCount = 2;
            break;
        case 2:
            damage = player.getSpecialAttack();
            text[0] = "You used a special attack!";
            boss.takeDamage(damage);
            text[1] = boss.getName() + " health: " + std::to_string(boss.getHealth());
            lineCount = 2;
            break;
        case 3:
            // Use healing item - First check if player needs healing
            if (player.getHealth() >= player.getMaxHealth())
            {
                text[0] = "Your health is already full!";
                text[1] = "No need to use healing items.";
                lineCount = 2;
                playerUsedTurn = false; // Don't consume turn if health is full
            }
            else if (playerInventory.hasHealingItems())
            {
                text[0] = "=== HEALING ITEMS ===";
                text[1] = "Select an item to use:";
                lineCount = 2;

                // Create a list of available items with continuous numbering
                int availableItemIndices[8]; // Store actual inventory indices of available items
                int availableItems = 0;

                // Collect available items
                for (int i = 0; i < playerInventory.getHealingItemCount() && availableItems < 8; i++)
                {
                    if (playerInventory.getHealingItem(i).isAvailable())
                    {
                        availableItemIndices[availableItems] = i;
                        availableItems++;
                    }
                }

                // Display items with continuous numbering
                for (int i = 0; i < availableItems; i++)
                {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " +
                                           playerInventory.getHealingItem(itemIndex).getName() +
                                           " (Heals " + std::to_string(playerInventory.getHealingItem(itemIndex).getHealAmount()) +
                                           " HP, Qty: " + std::to_string(playerInventory.getHealingItem(itemIndex).getQuantity()) + ")";
                    text[lineCount] = itemText;
                    lineCount++;
                }

                if (availableItems > 0)
                {
                    text[lineCount] = "Enter item number (0 to cancel): ";
                    lineCount++;

                    map.setPanelText(lineCount, text);
                    clearScreen();
                    drawCombatScreenBoss(map, player, boss, false);

                    int itemChoice = 0;
                    std::cin >> itemChoice;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (itemChoice > 0 && itemChoice <= availableItems)
                    {
                        // Use the continuous numbering to get the actual inventory index
                        int actualInventoryIndex = availableItemIndices[itemChoice - 1];

                        if (playerInventory.useHealingItem(actualInventoryIndex + 1, player))
                        { // +1 because useHealingItem expects 1-based index
                            text[0] = "You used a healing item!";
                            text[1] = "Your health: " + std::to_string(player.getHealth());
                            lineCount = 2;
                        }
                        else
                        {
                            text[0] = "Couldn't use that item!";
                            lineCount = 1;
                            playerUsedTurn = false;
                        }
                    }
                    else
                    {
                        text[0] = "Cancelled item use.";
                        lineCount = 1;
                        playerUsedTurn = false;
                    }
                }
                else
                {
                    text[0] = "No healing items available!";
                    lineCount = 1;
                    playerUsedTurn = false;
                }
            }
            else
            {
                text[0] = "No healing items available!";
                lineCount = 1;
                playerUsedTurn = false;
            }
            break;
        case 4:
            // Use damage item (same logic as in regular combat)
            if (playerInventory.hasDamageItems())
            {
                text[0] = "=== DAMAGE ITEMS ===";
                text[1] = "Select an item to use:";
                lineCount = 2;

                // Create a list of available items with continuous numbering
                int availableItemIndices[8]; // Store actual inventory indices of available items
                int availableItems = 0;

                // Collect available items
                for (int i = 0; i < playerInventory.getDamageItemCount() && availableItems < 8; i++)
                {
                    if (playerInventory.getDamageItem(i).isAvailable())
                    {
                        availableItemIndices[availableItems] = i;
                        availableItems++;
                    }
                }

                // Display items with continuous numbering
                for (int i = 0; i < availableItems; i++)
                {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " +
                                           playerInventory.getDamageItem(itemIndex).getName() +
                                           " (Dmg: " + std::to_string(playerInventory.getDamageItem(itemIndex).getDamage()) +
                                           ", Qty: " + std::to_string(playerInventory.getDamageItem(itemIndex).getQuantity()) + ")";
                    text[lineCount] = itemText;
                    lineCount++;
                }

                if (availableItems > 0)
                {
                    text[lineCount] = "Enter item number (0 to cancel): ";
                    lineCount++;

                    map.setPanelText(lineCount, text);
                    clearScreen();
                    drawCombatScreenBoss(map, player, boss, false);

                    int itemChoice = 0;
                    std::cin >> itemChoice;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (itemChoice > 0 && itemChoice <= availableItems)
                    {
                        // Use the continuous numbering to get the actual inventory index
                        int actualInventoryIndex = availableItemIndices[itemChoice - 1];

                        // For boss combat, we need to create a temporary Enemy reference
                        // This is a workaround since DamageItem::use expects an Enemy reference
                        // We'll apply damage directly instead
                        const DamageItem &item = playerInventory.getDamageItem(actualInventoryIndex);
                        if (item.isAvailable())
                        {
                            boss.takeDamage(item.getDamage());
                            // Manually reduce item quantity (since we can't use the use() method directly)
                            DamageItem &mutableItem = const_cast<DamageItem &>(item);
                            mutableItem.addQuantity(-1);
                            text[0] = "You used " + item.getName() + "!";
                            text[1] = boss.getName() + " health: " + std::to_string(boss.getHealth());
                            lineCount = 2;
                        }
                        else
                        {
                            text[0] = "Couldn't use that item!";
                            lineCount = 1;
                            playerUsedTurn = false;
                        }
                    }
                    else
                    {
                        text[0] = "Cancelled item use.";
                        lineCount = 1;
                        playerUsedTurn = false;
                    }
                }
                else
                {
                    text[0] = "No damage items available!";
                    lineCount = 1;
                    playerUsedTurn = false;
                }
            }
            else
            {
                text[0] = "No damage items available!";
                lineCount = 1;
                playerUsedTurn = false;
            }
            break;
        default:
            damage = player.getAttack();
            text[0] = "Invalid option! Using normal attack by default.";
            map.setPanelText(1, text);
            drawCombatScreenBoss(map, player, boss, false);
            combatPause(1500); // Pause 1.5 seconds to show invalid option message

            boss.takeDamage(damage);
            text[1] = boss.getName() + " health: " + std::to_string(boss.getHealth());
            lineCount = 2;
            break;
        }

        // Display the result of player's action
        map.setPanelText(lineCount, text);
        drawCombatScreenBoss(map, player, boss, false);

        // Pause to show action result
        std::cout << "\nPress any key to continue...";
        _getch();

        // Only continue to boss turn if player actually used their turn
        if (!playerUsedTurn)
        {
            continue; // Skip boss turn and let player choose again
        }

        if (boss.getHealth() <= 0)
        {
            // Increment global enemy counter and save progress for boss defeat
            GameMenu::incrementEnemiesDefeated();
            GameMenu::saveProgressAfterCombat("Boss Arena");

            // Show epic victory message
            text[0] = "*** " + boss.getName() + " HAS BEEN DEFEATED! ***";
            text[1] = "The mighty boss falls before you!";
            lineCount = 2;
            map.setPanelText(lineCount, text);
            drawCombatScreenBoss(map, player, boss, false);
            combatPause(3000); // Pause 3 seconds for epic victory

            // Show final victory message
            text[0] = "*** LEGENDARY VICTORY! ***";
            text[1] = "You have proven yourself a true hero!";
            text[2] = "The realm is safer thanks to your bravery!";
            lineCount = 3;
            map.setPanelText(lineCount, text);
            drawCombatScreenBoss(map, player, boss, false);

            combatWaitForKey("\nPress any key to continue...");
            break;
        }

        // Boss turn: can use normal or special attack randomly
        int bossDamage = 0;
        std::string bossAction = "";

        // Boss randomly decides which attack to use (50% each)
        if (rand() % 2 == 0)
        {
            bossDamage = boss.getAttack();
            bossAction = boss.getName() + "uses a devastating attack for " + std::to_string(bossDamage) + " damage!";
        }
        else
        {
            bossDamage = boss.getSpecialAttack();
            bossAction = boss.getName() + " unleashes a SPECIAL ATTACK for " + std::to_string(bossDamage) + " damage!";
        }

        // Apply damage inside receiveDamage
        player.receiveDamage(bossDamage);
        text[0] = bossAction;
        text[1] = "Your health: " + std::to_string(player.getHealth());
        lineCount = 2;
        map.setPanelText(lineCount, text);
        drawCombatScreenBoss(map, player, boss, false);

        // Pause to show boss attack result
        std::cout << "\nPress any key to continue...";
        _getch();

        if (player.getHealth() <= 0)
        {
            // Show dramatic boss defeat message
            text[0] = "*** YOU HAVE BEEN DEFEATED ***";
            text[1] = boss.getName() + " stands victorious...";
            lineCount = 2;
            map.setPanelText(lineCount, text);
            drawCombatScreenBoss(map, player, boss, false);
            combatPause(3000); // Pause 3 seconds for dramatic boss defeat

            // Show final defeat message
            text[0] = "THE BOSS REIGNS SUPREME";
            text[1] = "You fought valiantly, but it was not enough...";
            text[2] = "The realm remains in darkness...";
            lineCount = 3;
            map.setPanelText(lineCount, text);
            drawCombatScreenBoss(map, player, boss, false);

            combatWaitForKey("\nPress any key to continue...");
            isPlayerAlive = false;

            // Show death screen
            GameMenu::displayDeathScreen();
            break;
        }
    }
    text[0] = "Boss battle ended.";
    lineCount = 1;
    map.setPanelText(lineCount, text);
    drawCombatScreenBoss(map, player, boss, false); // No pause here to avoid double input

    return isPlayerAlive;
}

#endif
