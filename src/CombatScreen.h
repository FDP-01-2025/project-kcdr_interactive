#ifndef COMBATSCREEN_H
#define COMBATSCREEN_H

#include <string>

// Forward declarations
class Map;
class Player;
class Enemy;

#define ROWS 30
#define COLUMNS 90
#define MESSAGE_START_ROW (ROWS - 6)

// Include headers after forward declarations
#include "map.h"
#include "Player.h"
#include "Enemy.h"

#include "characters_Draw.h"
#include "unique_character.h"
#include "enemy_draw.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#endif
// ===== Limpiar la pantalla =====
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

// ===== Esperar pulsación de tecla para avanzar =====
void waitForKey()
{
#ifdef _WIN32
    _getch();
#else
    std::cin.get();
#endif
}

// ===== Draw a Decorative Health Bar (Safe for Console Width) =====
void drawHealthBar(char map[ROWS][COLUMNS], int row, int col, int current, const std::string &label)
{
    int barWidth = 20;

    // Si la salud actual es mayor que el ancho, lo limitamos (protección opcional)
    if (current > barWidth)
        current = barWidth;
    if (current < 0)
        current = 0;

    std::string full = label + " [";

    for (int i = 0; i < barWidth; ++i)
        full += (i < current) ? '=' : ' ';
    full += ']';

    for (size_t i = 0; i < full.length() && (col + i) < COLUMNS; ++i)
        map[row][col + i] = full[i];
}

// ===== Draw Character Name with Decorative Angle Brackets =====
void drawName(char map[ROWS][COLUMNS], int row, int col, const std::string &name)
{
    std::string formatted = "<" + name + ">";
    for (size_t i = 0; i < formatted.length(); ++i)
        if (col + i < COLUMNS)
            map[row][col + i] = formatted[i];
}

// ===== Draw Simple Combat Options (No Box) =====
void drawCombatMessage(char map[ROWS][COLUMNS], const std::string texto[], int lineCount)
{
    int maxCols = COLUMNS - 4;

    // Panel superior e inferior
    for (int r = MESSAGE_START_ROW; r < ROWS; ++r)
        for (int c = 0; c < COLUMNS; ++c)
            map[r][c] = (r == ROWS - 1) ? '-' : ' ';

    for (int i = 0; i < lineCount && i < 6; ++i)
    {
        const std::string &line = texto[i];
        for (size_t j = 0; j < line.length() && j < static_cast<size_t>(maxCols); ++j)
            map[MESSAGE_START_ROW + i][j + 2] = line[j];

        // Bordes verticales por línea
        map[MESSAGE_START_ROW + i][0] = '|';
        map[MESSAGE_START_ROW + i][COLUMNS - 1] = '|';
    }

    // Última línea del panel con bordes laterales
    map[ROWS - 1][0] = '+';
    map[ROWS - 1][COLUMNS - 1] = '+';
}

// ===== Draw a Horizontal Divider =====
void drawDivider(char map[ROWS][COLUMNS], int row)
{
    for (int i = 0; i < COLUMNS; ++i)
        map[row][i] = '-';
}

// ===== Main Combat Screen Drawing Function =====
void drawCombatScreen(Map &map, const Player &player, const Enemy &enemy, bool pause)
{
    clearScreen();
    char (&grid)[ROWS][COLUMNS] = map.getGrid();
    map.reset();

    // Divider between top (UI) and combat section
    drawDivider(grid, 4);
    drawDivider(grid, MESSAGE_START_ROW - 1);

    // Draw characters
    drawSelectedCharacter(grid, 8, 5); // Player character
    drawEnemy(enemy, grid, 8, 50);     // Enemy character safely on right

    // Draw names
    drawName(grid, 1, 5, player.getName());
    drawName(grid, 1, 50, enemy.getName());

    // Draw health bars
    drawHealthBar(grid, 2, 5, (player.getHealth() * 20) / 100, "HP");
    drawHealthBar(grid, 2, 50, (enemy.getHealth() * 20) / 100, "HP"); // stays within width

    // Draw message/options in bottom part of screen
    drawCombatMessage(grid, map.getPanelTexto(), map.getPanelLineCount());

    // Final render
    map.display();
    if (pause)
        waitForKey();
}

void drawCombatScreenBoss(Map &map, const Player &player, const Boss &boss, bool pause)
{
    clearScreen();
    char (&grid)[ROWS][COLUMNS] = map.getGrid();
    map.reset();

    // Divider between top (UI) and combat section
    drawDivider(grid, 4);
    drawDivider(grid, MESSAGE_START_ROW - 1);

    // Draw characters
    drawSelectedCharacter(grid, 8, 5); // Player character
    drawBoss(boss, grid, 8, 50);      // Use drawBoss instead of drawEnemy

    // Draw names
    drawName(grid, 1, 5, player.getName());
    drawName(grid, 1, 50, boss.getName());

    // Draw health bars
    drawHealthBar(grid, 2, 5, (player.getHealth() * 20) / 100, "HP");
    drawHealthBar(grid, 2, 50, (boss.getHealth() * 20) / 100, "HP");

    // Draw message/options in bottom part of screen
    drawCombatMessage(grid, map.getPanelTexto(), map.getPanelLineCount());

    // Final render
    map.display();
    if (pause)
        waitForKey();
}

#endif // COMBATSCREEN_H
