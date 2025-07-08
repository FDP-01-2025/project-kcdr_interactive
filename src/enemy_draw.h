#ifndef ENEMY_DRAW_H // Include guard: prevents this header file from being included more than once
#define ENEMY_DRAW_H // Defines ENEMY_DRAW_H if it hasn't been defined already

#include "map.h"   // Includes the map.h file, which provides access to the game map (e.g., a 2D grid)
#include "enemy.h" // Includes the enemy.h file, which defines the Enemy class and its attributes/methods
#include "Boss.h"
// ===== Enemy Initialization with ASCII Art =====

// Define a global array of 12 Enemy objects.
// Each Enemy is initialized with:
// - a name (string)
// - health points (int)
// - attack value (int)
// - defense value (int)
// - ASCII art (string literal using raw string syntax `R"(...)`)
Enemy enemy[12] = {
    // Slime enemy: small, basic creature with increased health for longer combat
    Enemy("Slime", 45, 8, 2, R"(
   __
  ( oo )
  /|__|\
)"),

    // Goblin enemy: weak humanoid enemy with balanced stats
    Enemy("Goblin", 55, 12, 3, R"(
  ,      ,
 /(.-""-.)\
 |\  \/  /|
 (_/    \_)
  /      \
  \      /
   `----`
)"),

    // Orc: stronger enemy with increased health and moderate damage
    Enemy("Orc", 80, 18, 5, R"(
  ,   A           {}
 / \, | ,        .--.
|    =|= >      /.--.\
 \ /` | `       |====|
  `   |         |`::`|
      |     .-;`\..../`;-.
     /\ /  /  |...::...|\
     |:'\ |   /'''::'''\\|
      \ /\;-,/\   ::   /
      |\ <` >  >._::_.<
      | `""`  /   ^^   \
      |       |        |
)"),

    // Wraith: ghost-like entity with moderate health
    Enemy("Wraith", 50, 10, 2, R"(
   .-.
  (   )
   \_/
  /   \
 |     |
  \___/
)"),

    // Gremlin: mischievous and quick creature with low defense
    Enemy("Gremlin", 40, 9, 1, R"(  ,     ,
 ( o o )
 /  V  \
/(  _  )\
  ^^ ^^
)"),

    // Skeleton: undead warrior with balanced stats
    Enemy("Skeleton", 48, 14, 2, R"(
   .-.
  (o.o)
   |=|
  __|__
//.=|=.\\
\\(_=_)// 
  (:| |:)
   || ||
   () ()
   || ||
   || ||
  ==' '==
)"),

    // Bat: flying enemy with low health but decent speed
    Enemy("Bat", 35, 7, 1, R"(
   /\                 /\
  / \'._   (\_/)   _.'/ \
 /_.''._'--('.')--'_.''._\
 | \_ / `;=/ " \=;` \ _/ |
  \/ `\__|`\___/`|__/`  \/
          \(/|\)/  
)"),

    // Boar: aggressive beast with good health and attack
    Enemy("Boar", 60, 13, 3, R"(
   (\____/)
   ( o  o )
  /   --   \
 (  (_) (_) )
  \   __   /
   \______/
)"),

    // Ghoul: creepy undead with high health
    Enemy("Ghoul", 70, 11, 4, R"(
   .-"      "-.
  /            \
 |              |
 |,  .-.  .-.  ,|
 | )(_o/  \o_)( |
 |/     /\\     \|
 (_     ^^     _)
  \__|IIIIII|__/
   | \IIIIII/ |
   \          /
    `--------`
)"),

    // Imp: small demonic creature with moderate stats
    Enemy("Imp", 42, 8, 1, R"(
   ,     ,
  ( o o )
 (   -   )
  \~(*)~/
   \___/
)"),

    // Golem: powerful stone guardian, high health and defense
    Enemy("Golem", 120, 20, 12, R"(
   _______
  /       \
 |  .-. .-.|
 |  |_| |_|
 |  _____  |
 | |     | |
 |_|     |_|
)"),

    // Dragonling: mini-boss level enemy with very high stats
    Enemy("Dragonling", 200, 25, 8, R"(
       / \  //\
 .-"\  \_/  //
|    \     //
 \    \___//
 /     /   \\
|     |     ||
 \    \___//
  \__/   \__/
)")};

// ===== Function to Draw Any Enemy on the Map =====

// This function takes:
// - a constant reference to an Enemy object `e`,
// - a reference to the map 2D array,
// - coordinates `row` and `col` to determine where to place the enemy's ASCII art.

void drawEnemy(const Enemy &e, char map[ROWS][COLUMNS], int row, int col)
{
    // Get the ASCII art string of the enemy using the class method
    std::string art = e.getAsciiArt();

    // Initialize row and column counters relative to the ASCII art being drawn
    int currentRow = 0;
    int currentCol = 0;

    // Loop through each character in the ASCII art string
    for (char ch : art)
    {
        if (ch == '\n') // When a newline is encountered,
        {
            currentRow++;   // move down one row
            currentCol = 0; // reset column position to the beginning
            continue;       // skip to the next character
        }

        // Only draw characters if the calculated position is within the map bounds
        if (row + currentRow < ROWS && col + currentCol < COLUMNS)
        {
            // Place the character onto the correct position of the game map
            map[row + currentRow][col + currentCol] = ch;
        }

        currentCol++; // Move to the next column for the current line
    }
}

void drawBoss(const Boss &e, char map[ROWS][COLUMNS], int row, int col)
{
    // Get the ASCII art string of the enemy using the class method
    std::string art = e.getAsciiArt();

    // Initialize row and column counters relative to the ASCII art being drawn
    int currentRow = 0;
    int currentCol = 0;

    // Loop through each character in the ASCII art string
    for (char ch : art)
    {
        if (ch == '\n') // When a newline is encountered,
        {
            currentRow++;   // move down one row
            currentCol = 0; // reset column position to the beginning
            continue;       // skip to the next character
        }

        // Only draw characters if the calculated position is within the map bounds
        if (row + currentRow < ROWS && col + currentCol < COLUMNS)
        {
            // Place the character onto the correct position of the game map
            map[row + currentRow][col + currentCol] = ch;
        }

        currentCol++; // Move to the next column for the current line
    }
}

#endif // ENEMY_DRAW_H // Marks the end of the include guard block
