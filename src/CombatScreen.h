#ifndef COMBATSCREEN_H
#define COMBATSCREEN_H

// Include necessary headers
#include "map.h"              // Contains the Map class for grid display
#include "Player.h"           // Contains the Player class definition
#include "Enemy.h"            // Contains the Enemy class definition
#include "characters_Draw.h"  // Functions to draw different characters
#include "unique_character.h" // Provides drawSelectedCharacter() for current character
#include "enemy_draw.h"       // Contains drawEnemy() to render enemy ASCII art
#include <iomanip>            // For std::setw and std::setfill (not directly used here but kept for formatting if needed)

// ========== Function: drawHealthBar ==========
// Draws a health bar at the specified position with the given label.
// The bar is composed of '=' for filled health and ' ' for empty segments.
void drawHealthBar(char map[ROWS][COLUMNS], int row, int col, int current, int max, const std::string &label)
{
    int barWidth = 20;                       // Total width of the health bar (characters)
    int filled = (current * barWidth) / max; // Calculate how many '=' to fill based on current health

    // Draw the label (e.g., "Player HP")
    for (size_t i = 0; i < label.length(); ++i)
        if (col + i < COLUMNS)
            map[row][col + i] = label[i];

    // Draw left bracket of health bar
    if (col + label.length() + 1 < COLUMNS)
        map[row][col + label.length() + 1] = '[';

    // Draw right bracket of health bar
    if (col + label.length() + barWidth + 2 < COLUMNS)
        map[row][col + label.length() + barWidth + 2] = ']';

    // Fill the inside of the bar: '=' for health, ' ' for missing health
    for (int i = 0; i < barWidth; ++i)
    {
        char symbol = (i < filled) ? '=' : ' ';
        if (col + label.length() + 2 + i < COLUMNS)
            map[row][col + label.length() + 2 + i] = symbol;
    }
}

// ========== Function: drawName ==========
// Draws a string (e.g., a name) at a specific position on the map
void drawName(char map[ROWS][COLUMNS], int row, int col, const std::string &name)
{
    for (size_t i = 0; i < name.length(); ++i)
        if (col + i < COLUMNS)
            map[row][col + i] = name[i];
}

// ========== Function: drawCombatOptions ==========
// Displays the combat action menu at the bottom area of the screen (inside the panel box)
void drawCombatOptions(char map[ROWS][COLUMNS])
{
    // Array of options to be displayed
    const std::string options[] = {
        "Choose an action:", // Header
        "1. Normal Attack",  // Option 1
        "2. Special Attack", // Option 2
    };

    int startRow = ROWS - 5; // Starting row near bottom of screen panel
    int startCol = 3;        // Indent from the left border

    // Loop over each line of the options array
    for (int i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < options[i].length(); ++j)
            if (startCol + j < COLUMNS)
                map[startRow + i][startCol + j] = options[i][j]; // Draw each character
    }
}

// ========== Function: drawCombatScreen ==========
// Draws the full combat interface: characters, names, health bars, and options.
void drawCombatScreen(Map &map, const Player &player, const Enemy &enemy)
{
    // Get a reference to the internal map grid (2D char array)
    char (&grid)[ROWS][COLUMNS] = map.getGrid();

    // Clear the grid and redraw borders
    map.reset();

    // === CHARACTER DRAWING SECTION ===
    drawSelectedCharacter(grid, 10, 5); // Draw selected player character at left side (row 10, col 5)
    drawEnemy(enemy, grid, 10, 60);     // Draw enemy character at right side (row 10, col 60)

    // === NAME DISPLAY SECTION ===
    drawName(grid, 1, 5, player.getName()); // Draw player name on top-left
    drawName(grid, 1, 60, enemy.getName()); // Draw enemy name on top-right

    // === HEALTH BAR DISPLAY SECTION ===
    drawHealthBar(grid, 2, 5, player.getHealth(), 100, "HP"); // Draw player health bar (assumes 100 max HP)
    drawHealthBar(grid, 2, 60, enemy.getHealth(), 20, "HP");  // Draw enemy health bar (adjust 20 if needed)

    // === COMBAT MENU DISPLAY SECTION ===
    drawCombatOptions(grid); // Draw action options in the bottom panel

    // === FINAL DISPLAY TO CONSOLE ===
    map.display(); // Render the entire grid with all content to the console
}

#endif // End of include guard COMBATSCREEN_H
