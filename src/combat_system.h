#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include <iostream>
#include <string>
#include <limits>  // Required for std::numeric_limits
#include <cstdlib> // Required for rand()

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
        if (option < 1 || option > 4) {
            option = 1; // Default to normal attack
        }

        int damage = 0;
        bool playerUsedTurn = true; // Track if player's turn was consumed

        switch (option)
        {
        case 1:
            damage = player.getAttack();
            text[0] = "You used a normal attack!";
            enemy.receiveDamage(damage);
            text[1] = enemy.getName() + " health: " + std::to_string(enemy.getHealth());
            lineCount = 2;
            break;
        case 2:
            damage = player.getSpecialAttack();
            text[0] = "You used a special attack!";
            enemy.receiveDamage(damage);
            text[1] = enemy.getName() + " health: " + std::to_string(enemy.getHealth());
            lineCount = 2;
            break;
        case 3:
            // Use healing item - First check if player needs healing
            if (player.getHealth() >= player.getMaxHealth()) {
                text[0] = "Your health is already full!";
                text[1] = "No need to use healing items.";
                lineCount = 2;
                playerUsedTurn = false; // Don't consume turn if health is full
            }
            else if (playerInventory.hasHealingItems()) {
                text[0] = "=== HEALING ITEMS ===";
                text[1] = "Select an item to use:";
                lineCount = 2;
                
                // Create a list of available items with continuous numbering
                int availableItemIndices[8]; // Store actual inventory indices of available items
                int availableItems = 0;
                
                // Collect available items
                for (int i = 0; i < playerInventory.getHealingItemCount() && availableItems < 8; i++) {
                    if (playerInventory.getHealingItem(i).isAvailable()) {
                        availableItemIndices[availableItems] = i;
                        availableItems++;
                    }
                }
                
                // Display items in two columns with continuous numbering
                int leftColumnItems = (availableItems + 1) / 2;  // Ceiling division
                
                // Display left column items
                for (int i = 0; i < leftColumnItems; i++) {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " + 
                                         playerInventory.getHealingItem(itemIndex).getName() + 
                                         " (+" + std::to_string(playerInventory.getHealingItem(itemIndex).getHealAmount()) + 
                                         " HP, x" + std::to_string(playerInventory.getHealingItem(itemIndex).getQuantity()) + ")";
                    text[lineCount] = itemText;
                    lineCount++;
                }
                
                // Display right column items (if any)
                for (int i = leftColumnItems; i < availableItems; i++) {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " + 
                                         playerInventory.getHealingItem(itemIndex).getName() + 
                                         " (+" + std::to_string(playerInventory.getHealingItem(itemIndex).getHealAmount()) + 
                                         " HP, x" + std::to_string(playerInventory.getHealingItem(itemIndex).getQuantity()) + ")";
                    
                    // Add to the corresponding left column line
                    int leftLineIndex = lineCount - availableItems + i;
                    if (leftLineIndex >= 2 && leftLineIndex < lineCount) {
                        text[leftLineIndex] += "     " + itemText; // Add spacing and right column item
                    }
                }
                
                if (availableItems > 0) {
                    text[lineCount] = "Enter item number (0 to cancel): ";
                    lineCount++;
                    
                    map.setPanelText(lineCount, text);
                    clearScreen();
                    drawCombatScreen(map, player, enemy, false);
                    
                    int itemChoice = 0;
                    std::cin >> itemChoice;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (itemChoice > 0 && itemChoice <= availableItems) {
                        // Use the continuous numbering to get the actual inventory index
                        int actualInventoryIndex = availableItemIndices[itemChoice - 1];
                        
                        if (playerInventory.useHealingItem(actualInventoryIndex + 1, player)) { // +1 because useHealingItem expects 1-based index
                            text[0] = "You used a healing item!";
                            text[1] = "Your health: " + std::to_string(player.getHealth());
                            lineCount = 2;
                        } else {
                            text[0] = "Couldn't use that item!";
                            lineCount = 1;
                            playerUsedTurn = false;
                        }
                    } else {
                        text[0] = "Cancelled item use.";
                        lineCount = 1;
                        playerUsedTurn = false;
                    }
                } else {
                    text[0] = "No healing items available!";
                    lineCount = 1;
                    playerUsedTurn = false;
                }
            } else {
                text[0] = "No healing items available!";
                lineCount = 1;
                playerUsedTurn = false; // Don't consume turn if no items
            }
            break;
        case 4:
            // Use damage item
            if (playerInventory.hasDamageItems()) {
                text[0] = "=== DAMAGE ITEMS ===";
                text[1] = "Select an item to use:";
                lineCount = 2;
                
                // Create a list of available items with continuous numbering
                int availableItemIndices[8]; // Store actual inventory indices of available items
                int availableItems = 0;
                
                // Collect available items
                for (int i = 0; i < playerInventory.getDamageItemCount() && availableItems < 8; i++) {
                    if (playerInventory.getDamageItem(i).isAvailable()) {
                        availableItemIndices[availableItems] = i;
                        availableItems++;
                    }
                }
                
                // Display items in two columns with continuous numbering
                int leftColumnItems = (availableItems + 1) / 2;  // Ceiling division
                
                // Display left column items
                for (int i = 0; i < leftColumnItems; i++) {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " + 
                                         playerInventory.getDamageItem(itemIndex).getName() + 
                                         " (" + std::to_string(playerInventory.getDamageItem(itemIndex).getDamage()) + 
                                         " DMG, x" + std::to_string(playerInventory.getDamageItem(itemIndex).getQuantity()) + ")";
                    text[lineCount] = itemText;
                    lineCount++;
                }
                
                // Display right column items (if any)
                for (int i = leftColumnItems; i < availableItems; i++) {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " + 
                                         playerInventory.getDamageItem(itemIndex).getName() + 
                                         " (" + std::to_string(playerInventory.getDamageItem(itemIndex).getDamage()) + 
                                         " DMG, x" + std::to_string(playerInventory.getDamageItem(itemIndex).getQuantity()) + ")";
                    
                    // Add to the corresponding left column line
                    int leftLineIndex = lineCount - availableItems + i;
                    if (leftLineIndex >= 2 && leftLineIndex < lineCount) {
                        text[leftLineIndex] += "     " + itemText; // Add spacing and right column item
                    }
                }
                
                if (availableItems > 0) {
                    text[lineCount] = "Enter item number (0 to cancel): ";
                    lineCount++;
                    
                    map.setPanelText(lineCount, text);
                    clearScreen();
                    drawCombatScreen(map, player, enemy, false);
                    
                    int itemChoice = 0;
                    std::cin >> itemChoice;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (itemChoice > 0 && itemChoice <= availableItems) {
                        // Use the continuous numbering to get the actual inventory index
                        int actualInventoryIndex = availableItemIndices[itemChoice - 1];
                        
                        if (playerInventory.useDamageItem(actualInventoryIndex + 1, player, enemy)) { // +1 because useDamageItem expects 1-based index
                            text[0] = "You used a damage item!";
                            text[1] = enemy.getName() + " health: " + std::to_string(enemy.getHealth());
                            lineCount = 2;
                        } else {
                            text[0] = "Couldn't use that item!";
                            lineCount = 1;
                            playerUsedTurn = false;
                        }
                    } else {
                        text[0] = "Cancelled item use.";
                        lineCount = 1;
                        playerUsedTurn = false;
                    }
                } else {
                    text[0] = "No damage items available!";
                    lineCount = 1;
                    playerUsedTurn = false;
                }
            } else {
                text[0] = "No damage items available!";
                lineCount = 1;
                playerUsedTurn = false; // Don't consume turn if no items
            }
            break;
        default:
            damage = player.getAttack();
            text[0] = "Invalid option. Normal attack used by default.";
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
        if (!playerUsedTurn) {
            continue; // Skip enemy turn and let player choose again
        }

        //Logica cuando el enemigo es derrotado
        if (enemy.getHealth() <= 0)
        {
            player.addEnemyKill();
            
            // Increment global enemy counter and save progress
            GameMenu::incrementEnemiesDefeated();
            GameMenu::saveProgressAfterCombat("Combat Area");
            
            // Give enemy-specific drops
            enemy.giveDropsToPlayer(playerInventory, playerGold);
            
            text[0] = enemy.getName() + " was defeated!";

            text[1] = "You received battle rewards!";
            text[2] = "Gold: " + std::to_string(playerGold);
            lineCount = 3;

            text[1] = "Press any key to continue...";
            lineCount = 2;


            map.setPanelText(lineCount, text);

            drawCombatScreen(map, player, enemy, false);
            std::cout << "\nPress any key to continue...";
            _getch(); // Single controlled pause
            break;
        }

        // Enemy turn: normal attack
        int enemyDamage = enemy.getAttack();
        std::string enemyAction = enemy.getName() + " attacks with " + std::to_string(enemyDamage) + " damage!";

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
            text[0] = "You were defeated in battle...";
            text[1] = "Press any key to continue...";
            lineCount = 2;

            map.setPanelText(lineCount, text);

            drawCombatScreen(map, player, enemy, false);
            std::cout << "\nPress any key to continue...";
            _getch(); // Single controlled pause
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
        if (option < 1 || option > 4) {
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
            if (player.getHealth() >= player.getMaxHealth()) {
                text[0] = "Your health is already full!";
                text[1] = "No need to use healing items.";
                lineCount = 2;
                playerUsedTurn = false; // Don't consume turn if health is full
            }
            else if (playerInventory.hasHealingItems()) {
                text[0] = "=== HEALING ITEMS ===";
                text[1] = "Select an item to use:";
                lineCount = 2;
                
                // Create a list of available items with continuous numbering
                int availableItemIndices[8]; // Store actual inventory indices of available items
                int availableItems = 0;
                
                // Collect available items
                for (int i = 0; i < playerInventory.getHealingItemCount() && availableItems < 8; i++) {
                    if (playerInventory.getHealingItem(i).isAvailable()) {
                        availableItemIndices[availableItems] = i;
                        availableItems++;
                    }
                }
                
                // Display items with continuous numbering
                for (int i = 0; i < availableItems; i++) {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " + 
                                         playerInventory.getHealingItem(itemIndex).getName() + 
                                         " (Heals " + std::to_string(playerInventory.getHealingItem(itemIndex).getHealAmount()) + 
                                         " HP, Qty: " + std::to_string(playerInventory.getHealingItem(itemIndex).getQuantity()) + ")";
                    text[lineCount] = itemText;
                    lineCount++;
                }
                
                if (availableItems > 0) {
                    text[lineCount] = "Enter item number (0 to cancel): ";
                    lineCount++;
                    
                    map.setPanelText(lineCount, text);
                    clearScreen();
                    drawCombatScreenBoss(map, player, boss, false);
                    
                    int itemChoice = 0;
                    std::cin >> itemChoice;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (itemChoice > 0 && itemChoice <= availableItems) {
                        // Use the continuous numbering to get the actual inventory index
                        int actualInventoryIndex = availableItemIndices[itemChoice - 1];
                        
                        if (playerInventory.useHealingItem(actualInventoryIndex + 1, player)) { // +1 because useHealingItem expects 1-based index
                            text[0] = "You used a healing item!";
                            text[1] = "Your health: " + std::to_string(player.getHealth());
                            lineCount = 2;
                        } else {
                            text[0] = "Couldn't use that item!";
                            lineCount = 1;
                            playerUsedTurn = false;
                        }
                    } else {
                        text[0] = "Cancelled item use.";
                        lineCount = 1;
                        playerUsedTurn = false;
                    }
                } else {
                    text[0] = "No healing items available!";
                    lineCount = 1;
                    playerUsedTurn = false;
                }
            } else {
                text[0] = "No healing items available!";
                lineCount = 1;
                playerUsedTurn = false;
            }
            break;
        case 4:
            // Use damage item (same logic as in regular combat)
            if (playerInventory.hasDamageItems()) {
                text[0] = "=== DAMAGE ITEMS ===";
                text[1] = "Select an item to use:";
                lineCount = 2;
                
                // Create a list of available items with continuous numbering
                int availableItemIndices[8]; // Store actual inventory indices of available items
                int availableItems = 0;
                
                // Collect available items
                for (int i = 0; i < playerInventory.getDamageItemCount() && availableItems < 8; i++) {
                    if (playerInventory.getDamageItem(i).isAvailable()) {
                        availableItemIndices[availableItems] = i;
                        availableItems++;
                    }
                }
                
                // Display items with continuous numbering
                for (int i = 0; i < availableItems; i++) {
                    int itemIndex = availableItemIndices[i];
                    std::string itemText = std::to_string(i + 1) + ". " + 
                                         playerInventory.getDamageItem(itemIndex).getName() + 
                                         " (Dmg: " + std::to_string(playerInventory.getDamageItem(itemIndex).getDamage()) + 
                                         ", Qty: " + std::to_string(playerInventory.getDamageItem(itemIndex).getQuantity()) + ")";
                    text[lineCount] = itemText;
                    lineCount++;
                }
                
                if (availableItems > 0) {
                    text[lineCount] = "Enter item number (0 to cancel): ";
                    lineCount++;
                    
                    map.setPanelText(lineCount, text);
                    clearScreen();
                    drawCombatScreenBoss(map, player, boss, false);
                    
                    int itemChoice = 0;
                    std::cin >> itemChoice;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (itemChoice > 0 && itemChoice <= availableItems) {
                        // Use the continuous numbering to get the actual inventory index
                        int actualInventoryIndex = availableItemIndices[itemChoice - 1];
                        
                        // For boss combat, we need to create a temporary Enemy reference
                        // This is a workaround since DamageItem::use expects an Enemy reference
                        // We'll apply damage directly instead
                        const DamageItem& item = playerInventory.getDamageItem(actualInventoryIndex);
                        if (item.isAvailable()) {
                            boss.takeDamage(item.getDamage());
                            // Manually reduce item quantity (since we can't use the use() method directly)
                            DamageItem& mutableItem = const_cast<DamageItem&>(item);
                            mutableItem.addQuantity(-1);
                            text[0] = "You used " + item.getName() + "!";
                            text[1] = boss.getName() + " health: " + std::to_string(boss.getHealth());
                            lineCount = 2;
                        } else {
                            text[0] = "Couldn't use that item!";
                            lineCount = 1;
                            playerUsedTurn = false;
                        }
                    } else {
                        text[0] = "Cancelled item use.";
                        lineCount = 1;
                        playerUsedTurn = false;
                    }
                } else {
                    text[0] = "No damage items available!";
                    lineCount = 1;
                    playerUsedTurn = false;
                }
            } else {
                text[0] = "No damage items available!";
                lineCount = 1;
                playerUsedTurn = false;
            }
            break;
        default:
            damage = player.getAttack();
            text[0] = "Invalid option. Normal attack used by default.";
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
        if (!playerUsedTurn) {
            continue; // Skip boss turn and let player choose again
        }

        if (boss.getHealth() <= 0)
        {
            // Increment global enemy counter and save progress for boss defeat
            GameMenu::incrementEnemiesDefeated();
            GameMenu::saveProgressAfterCombat("Boss Arena");
            
            text[0] = "*** " + boss.getName() + " HAS BEEN DEFEATED! ***";
            text[1] = "Victory is yours!";
            text[2] = "Press any key to continue...";
            lineCount = 3;

            map.setPanelText(lineCount, text);
            drawCombatScreenBoss(map, player, boss, false);
            std::cout << "\nPress any key to continue...";
            _getch(); // Single controlled pause
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
        }else{
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
            text[0] = "*** YOU HAVE BEEN DEFEATED ***";
            text[1] = boss.getName() + " stands victorious...";
            text[2] = "Press any key to continue...";
            lineCount = 3;

            map.setPanelText(lineCount, text);
            drawCombatScreenBoss(map, player, boss, false);
            std::cout << "\nPress any key to continue...";
            _getch(); // Single controlled pause
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
