#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include <iostream>
#include <string>
#include <limits>
#include "Player.h"
#include "Enemy.h"
#include "map.h"
#include "combatScreen.h" // Para mostrar interfaz de combate con arte ASCII

const int MAX_LINES = 6; // Número máximo de líneas para mostrar en el recuadro de mensaje

// ======= Combate contra enemigo común =======
// Devuelve true si el jugador sobrevive, false si muere
bool Combat(Player &player, Enemy &enemy, Map &map)
{
    bool isPlayerAlive = true;

    std::string texto[MAX_LINES];
    int lineCount = 0;

    while (player.getHealth() > 0 && enemy.getHealth() > 0)
    {
        // Preparar el texto con las opciones de ataque
        texto[0] = "Choose your action:";
        texto[1] = "1. Normal Attack (" + std::to_string(player.getAttack()) + " dmg)";
        texto[2] = "2. Special Attack (" + std::to_string(player.getSpecialAttack()) + " dmg)";
        texto[3] = "Enter option: ";
        lineCount = 4;

        // Setear texto en el mapa y mostrar pantalla
        map.setPanelTexto(lineCount, texto);
        clearScreen();
        drawCombatScreen(map, player, enemy);

        int option = 0;
        std::cout << " > ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> option;

        int damage = 0;

        switch (option)
        {
        case 1:
            damage = player.getAttack();
            texto[0] = "You used a normal attack!";
            break;
        case 2:
            damage = player.getSpecialAttack();
            texto[0] = "You used a special attack!";
            break;
        default:
            damage = player.getAttack();
            texto[0] = "Invalid option. Normal attack used by default.";
            break;
        }

        enemy.receiveDamage(damage);

        texto[1] = "Enemy health: " + std::to_string(enemy.getHealth());
        lineCount = 2;
        map.setPanelTexto(lineCount, texto); 
        drawCombatScreen(map, player, enemy, true);

        if (enemy.getHealth() <= 0)
        {
            texto[0] = enemy.getName() + " was defeated!";
            lineCount = 1;

            map.setPanelTexto(lineCount, texto);

            drawCombatScreen(map, player, enemy);
            break;
        }

        // Turno enemigo: ataque normal
        int enemyDamage = enemy.getAttack();
        std::string enemyAction = enemy.getName() + " attacks with " + std::to_string(enemyDamage) + " damage!";

        // Aplicar daño con mitigación dentro de receiveDamage
        player.receiveDamage(enemyDamage);

        texto[0] = enemyAction;
        texto[1] = "Your health: " + std::to_string(player.getHealth());
        lineCount = 2;
        map.setPanelTexto(lineCount, texto);
        drawCombatScreen(map, player, enemy, true);

        if (player.getHealth() <= 0)
        {
            texto[0] = "You were defeated in battle...";
            lineCount = 1;

            map.setPanelTexto(lineCount, texto);

            drawCombatScreen(map, player, enemy, true);
            isPlayerAlive = false;
            break;
        }

        // Mostrar resultado del turno enemigo
        map.setPanelTexto(lineCount, texto);

        drawCombatScreen(map, player, enemy);
    }

    texto[0] = "Combat ended.";
    lineCount = 1;
    map.setPanelTexto(lineCount, texto);
    drawCombatScreen(map, player, enemy, true);

    return isPlayerAlive;
}

#endif
