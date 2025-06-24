#ifndef COMBATSCREEN_H
#define COMBATSCREEN_H

#include "map.h"
#include "Player.h"
#include "Enemy.h"
#include "characters_Draw.h"
#include "unique_character.h"
#include "enemy_draw.h"
#include <string>

// ===== Draw a Decorative Health Bar (Safe for Console Width) =====
void drawHealthBar(char map[ROWS][COLUMNS], int row, int col, int current, int max, const std::string &label)
{
    int barWidth = 20;
    int filled = (current * barWidth) / max;

    std::string full = label + " [";
    for (int i = 0; i < barWidth; ++i)
        full += (i < filled) ? '=' : ' ';
    full += ']';

    // Ensure it doesn't overflow the map width
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
void drawCombatOptions(char map[ROWS][COLUMNS])
{
    const std::string options[] = {
        "Choose an action:",
        "1. Normal Attack",
        "2. Special Attack"
    };

    int startRow = ROWS - 5;
    int startCol = 4;

    for (int i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < options[i].length(); ++j)
        {
            if (startCol + j < COLUMNS)
                map[startRow + i][startCol + j] = options[i][j];
        }
    }
}

// ===== Draw a Horizontal Divider =====
void drawDivider(char map[ROWS][COLUMNS], int row)
{
    for (int i = 0; i < COLUMNS; ++i)
        map[row][i] = '-';
}

// ===== Main Combat Screen Drawing Function =====
void drawCombatScreen(Map &map, const Player &player, const Enemy &enemy)
{
    char (&grid)[ROWS][COLUMNS] = map.getGrid();
    map.reset();

    // Divider between top (UI) and combat section
    drawDivider(grid, 4);

    // Draw characters
    drawSelectedCharacter(grid, 8, 5);      // Player character
    drawEnemy(enemy, grid, 8, 50);          // Enemy character safely on right

    // Draw names
    drawName(grid, 1, 5, player.getName());
    drawName(grid, 1, 50, enemy.getName());

    // Draw health bars
    drawHealthBar(grid, 2, 5, player.getHealth(), 100, "HP");
    drawHealthBar(grid, 2, 50, enemy.getHealth(), 20, "HP"); // stays within width

    // Combat options (bottom left, no box)
    drawCombatOptions(grid);

    // Final render
    map.display();
}

#endif // COMBATSCREEN_H
