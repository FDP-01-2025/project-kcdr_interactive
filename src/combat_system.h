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

const int MAX_LINES = 6; // Maximum number of lines to display in the message box

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
        text[3] = "Enter option: ";
        lineCount = 4;

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
        if (option < 1 || option > 2) {
            option = 1; // Default to normal attack
        }

        int damage = 0;

        switch (option)
        {
        case 1:
            damage = player.getAttack();
            text[0] = "You used a normal attack!";
            break;
        case 2:
            damage = player.getSpecialAttack();
            text[0] = "You used a special attack!";
            break;
        default:
            damage = player.getAttack();
            text[0] = "Invalid option. Normal attack used by default.";
            break;
        }

        enemy.receiveDamage(damage);
        text[1] = enemy.getName() + " health: " + std::to_string(enemy.getHealth());
        lineCount = 2;
        map.setPanelText(lineCount, text);
        drawCombatScreen(map, player, enemy, false);
        
        // Pause to show attack result
        std::cout << "\nPress any key to continue...";
        _getch();

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
        text[3] = "Enter option: ";
        lineCount = 4;

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
        if (option < 1 || option > 2) {
            option = 1; // Default to normal attack
        }

        int damage = 0;
        switch (option)
        {
        case 1:
            damage = player.getAttack();
            text[0] = "You used a normal attack!";
            break;
        case 2:
            damage = player.getSpecialAttack();
            text[0] = "You used a special attack!";
            break;
        default:
            damage = player.getAttack();
            text[0] = "Invalid option. Normal attack used by default.";
            break;
        }

        boss.takeDamage(damage);

        text[1] = boss.getName() + " health: " + std::to_string(boss.getHealth());
        lineCount = 2;

        map.setPanelText(lineCount, text);
        drawCombatScreenBoss(map, player, boss, false);
        
        // Pause to show attack result
        std::cout << "\nPress any key to continue...";
        _getch();

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
