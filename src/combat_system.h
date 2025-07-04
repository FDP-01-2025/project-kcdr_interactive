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
#include "Boss.h"

const int MAX_LINES = 6; // Número máximo de líneas para mostrar en el recuadro de mensaje

// ======= Combate contra enemigo común =======
// Devuelve true si el jugador sobrevive, false si muere
bool Combat(Player &player, Enemy &enemy, Map &map)
{
    bool isPlayerAlive = true;

    std::string text[MAX_LINES];
    int lineCount = 0;

    while (player.getHealth() > 0 && enemy.getHealth() > 0)
    {
        // Preparar el texto con las opciones de ataque
        text[0] = "Choose your action:";
        text[1] = "1. Normal Attack (" + std::to_string(player.getAttack()) + " dmg)";
        text[2] = "2. Special Attack (" + std::to_string(player.getSpecialAttack()) + " dmg)";
        text[3] = "Enter option: ";
        lineCount = 4;

        // Setear texto en el mapa y mostrar pantalla
        map.setPanelText(lineCount, text);
        clearScreen();
        drawCombatScreen(map, player, enemy);

        int option = 0;
        std::cout << " > ";
        std::cin >> option;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            option = 0;
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

        text[1] = enemy.getName() + "health: " + std::to_string(enemy.getHealth());
        lineCount = 2;
        map.setPanelText(lineCount, text);
        drawCombatScreen(map, player, enemy, true);

        if (enemy.getHealth() <= 0)
        {
            text[0] = enemy.getName() + " was defeated!";
            lineCount = 1;

            map.setPanelText(lineCount, text);

            drawCombatScreen(map, player, enemy);
            break;
        }

        // Turno enemigo: ataque normal
        int enemyDamage = enemy.getAttack();
        std::string enemyAction = enemy.getName() + " attacks with " + std::to_string(enemyDamage) + " damage!";

        // Aplicar daño con mitigación dentro de receiveDamage
        player.receiveDamage(enemyDamage);

        text[0] = enemyAction;
        text[1] = "Your health: " + std::to_string(player.getHealth());
        lineCount = 2;
        map.setPanelText(lineCount, text);
        drawCombatScreen(map, player, enemy, true);

        if (player.getHealth() <= 0)
        {
            text[0] = "You were defeated in battle...";
            lineCount = 1;

            map.setPanelText(lineCount, text);

            drawCombatScreen(map, player, enemy, true);
            isPlayerAlive = false;
            break;
        }

        // Mostrar resultado del turno enemigo
        map.setPanelText(lineCount, text);

        drawCombatScreen(map, player, enemy);
    }

    text[0] = "Combat ended.";
    lineCount = 1;
    map.setPanelText(lineCount, text);
    drawCombatScreen(map, player, enemy, true);

    return isPlayerAlive;
}
// Devuelve true si el jugador sobrevive, false si muere
bool CombatBosss(Player &player, Boss &boss, Map &map)
{
    bool isPlayerAlive = true;

    std::string text[MAX_LINES];
    int lineCount = 0;

    // Mensaje inicial
    text[0] = "*** BOSS BATTLE ***";
    text[1] = boss.getName() + "appears before you!";
    lineCount = 2;
    map.setPanelText(lineCount, text);
    clearScreen();
    drawCombatScreenBoss(map, player, boss, true);

    while (player.getHealth() > 0 && boss.getHealth() > 0)
    {
        // Preparar el texto con las opciones de ataque
        text[0] = "Choose your action:";
        text[1] = "1. Normal Attack (" + std::to_string(player.getAttack()) + " dmg)";
        text[2] = "2. Special Attack (" + std::to_string(player.getSpecialAttack()) + " dmg)";
        text[3] = "Enter option: ";
        lineCount = 4;

        // Setear texto en el mapa y mostrar pantalla
        map.setPanelText(lineCount, text);
        clearScreen();
        drawCombatScreenBoss(map, player, boss, true);

        int option = 0;
        std::cout << " > ";
        std::cin >> option;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            option = 0;
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

        text[1] = boss.getName() + "health: " + std::to_string(boss.getHealth());
        lineCount = 2;

        map.setPanelText(lineCount, text);
        drawCombatScreenBoss(map, player, boss, true);

        if (boss.getHealth() <= 0)
        {
            text[0] = "*** " + boss.getName() + " HAS BEEN DEFEATED! ***";
            text[1] = "¡Victory is yours!";
            lineCount = 2;

            map.setPanelText(lineCount, text);
            drawCombatScreenBoss(map, player, boss, true);
            break;
        }

        //Turno del jefe: puede usar ataque normal o especial aleatoriamente
        int bossDamage = 0;
        std:: string  bossAction = "";

        //El jefe decide aleatoriamente que ataque usar (50% cada uno)
        if (rand() % 2 == 0)
        {
            bossDamage = boss.getAttack();
            bossAction = boss.getName() + "uses a devastating attack for " + std::to_string(bossDamage) + " damage!";
        }else{
            bossDamage = boss.getspecialAtack();
            bossAction = boss.getName() + "unleashes a SPECIAL ATTACK for " + std::to_string(bossDamage) + "damege!";
        }
        
        //Aplicar daño dentro de receuveDamage
        player.receiveDamage(bossDamage);
        text[0] = bossAction;
        text[1] = "Your health: " + std::to_string(player.getHealth());
        lineCount = 2;
        map.setPanelText(lineCount, text);
        drawCombatScreenBoss(map, player, boss, true);

        if (player.getHealth() <= 0)
        {
            text[0] = "*** YOU HAVE BEEN DEFEATED ***";
            text[1] = boss.getName() + " stands victorius...";
            lineCount = 2;

            map.setPanelText(lineCount, text);
            drawCombatScreenBoss(map, player, boss, true);
            isPlayerAlive = false;
            break;
        }
        //Mostrar resultado del turno del jefe
        map.setPanelText(lineCount, text);
        drawCombatScreenBoss(map, player, boss , true);
    }
    text[0] = "Boss battle ended.";
    lineCount = 1;
    map.setPanelText(lineCount, text);
    drawCombatScreenBoss(map, player, boss, true);

    return isPlayerAlive;
}

#endif
