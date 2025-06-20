#ifndef ENEMY_DRAW_H             // Include guard: ensures this file is included only once during compilation
#define ENEMY_DRAW_H             // Defines the macro if not already defined

#include "map.h"                // Includes the Map class definition to access and manipulate the game map
#include "enemy.h"              // Includes the Enemy class definition to access enemy attributes and methods

// ===== Enemy Initialization with ASCII Art =====

// This global array holds 12 Enemy objects. Each enemy is initialized with a name,
// health, attack power, defense, and optionally some ASCII art for display on the map.
Enemy enemy[12] = {
    // Slime enemy with ASCII representation
    Enemy("Slime", 20, 5, 2, R"(
   __
  ( oo )
  /|__|\
)"),

    // Goblin enemy with ASCII representation
    Enemy("Goblin", 25, 7, 3, R"(
  ,      ,
 /(.-""-.)\
 |\  \/  /|
 (_/    \_)
  /      \
  \      /
   `----`
)"),

    // The rest of the enemies are initialized with empty ASCII art for now (could be added later)
    Enemy("Orc", 35, 10, 5, ""),
    Enemy("Bandit", 28, 8, 2, ""),
    Enemy("Wolf", 22, 6, 1, ""),
    Enemy("Skeleton", 18, 9, 2, ""),
    Enemy("Bat", 15, 4, 1, ""),
    Enemy("Spider", 17, 5, 2, ""),
    Enemy("Zombie", 30, 6, 4, ""),
    Enemy("Witch", 24, 11, 3, ""),
    Enemy("Knight", 40, 12, 8, ""),
    Enemy("Dragonling", 45, 15, 6, "")
};

// ===== Function to Draw Any Enemy on the Map =====

// This function takes an Enemy object `e`, a reference to the map grid,
// and the coordinates `row` and `col` where the ASCII art should be drawn.

void drawEnemy(const Enemy &e, char map[ROWS][COLUMNS], int row, int col)
{
    std::string art = e.getAsciiArt();   // Get the enemy's ASCII art as a string
    int currentRow = 0;                  // Tracks the current row offset while drawing
    int currentCol = 0;                  // Tracks the current column offset while drawing

    // Iterate through each character in the ASCII art string
    for (char ch : art)
    {
        if (ch == '\n')                  // If a newline character is encountered,
        {
            currentRow++;               // move to the next row of the drawing
            currentCol = 0;             // reset the column offset
            continue;                   // skip to the next character
        }

        // Ensure that we stay within the map boundaries when writing characters
        if (row + currentRow < ROWS && col + currentCol < COLUMNS)
        {
            map[row + currentRow][col + currentCol] = ch;  // Copy character to correct position in the map
        }

        currentCol++;                   // Move to the next column in the ASCII art line
    }
}

#endif // ENEMY_DRAW_H             // End of include guard
