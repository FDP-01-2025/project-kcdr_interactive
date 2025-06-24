#ifndef CHARACTERS_DRAW_H
#define CHARACTERS_DRAW_H

#include "map.h" // Include the map header which contains the 2D array 'map[ROWS][COLUMNS]'

// Function to draw the character Rhaekor on the map at a specified row and column
void drawRhaekor(char map[ROWS][COLUMNS], int row, int column)
{
    // Static 2D array representing Rhaekor's sprite art
    // 9 rows, each string up to 15 characters + null terminator (16 total)
    const char art[9][16] = {
        "   ////\\\\\\\\   ", // Long hair
        "  |  O  O  |  ",     // Determined face with eyes
        "  |   ==   |  ",     // Serious mouth expression
        "  |_______|  ",      // Jawline shape
        "  /|     |\\  ",     // Muscular arms
        " /_|_[]__|_\\ ",     // Chest with light armor
        "   /  |  \\   ",     // Waist
        "  /   |   \\  ",     // Legs spread apart
        " /____|____\\ "      // Boots
    };

    // Loop through each row of the sprite art
    for (int i = 0; i < 9; ++i)
        // Loop through each character in the current row until null terminator is found
        for (int j = 0; art[i][j] != '\0'; ++j)
            // Check if the position (row + i, column + j) is inside the map bounds
            if (row + i < ROWS && column + j < COLUMNS)
                // Copy the character from art to the map at the correct position
                map[row + i][column + j] = art[i][j];
}

// Function to draw the character Cerephios on the map at a specified row and column
void drawCerephios(char map[ROWS][COLUMNS], int row, int column)
{
    // Static 2D array representing Cerephios's sprite art
    const char art[9][16] = {
        "   _______   ",  // Helmet top
        "  | [o] [o]| ",  // Metallic visor eyes
        "  |_______| ",   // Closed helmet
        "   |=====|   ",  // Protected neck area
        "  /|#####|\\ ",  // Full armor on torso
        " | |#####| |",   // Armored chest
        "   |__|__|   ",  // Abdomen protection
        "  /   |   \\  ", // Strong legs stance
        " /____|____\\ "  // Reinforced boots
    };

    // Same nested loops and boundary checks as before to copy art to map
    for (int i = 0; i < 9; ++i)
        for (int j = 0; art[i][j] != '\0'; ++j)
            if (row + i < ROWS && column + j < COLUMNS)
                map[row + i][column + j] = art[i][j];
}

// Function to draw the character Kaelren on the map at a specified row and column
void drawKaelren(char map[ROWS][COLUMNS], int row, int column)
{
    // Static 2D array representing Kaelren's sprite art
    const char art[9][16] = {
        "    _____    ",  // Hood shape
        "   /     \\   ", // Calm face outline
        "  |  o o  |  ",  // Wise eyes
        "  |   ~   |  ",  // Calm mouth
        "  |_______|  ",  // Light beard
        "    |||||    ",  // Staff held by character
        "   /|||\\     ", // Magic robe details
        "  / | | \\    ", // Long flowing robe
        " /__|_|__\\   "  // Traveler boots
    };

    // Copy sprite art to map with bounds checking
    for (int i = 0; i < 9; ++i)
        for (int j = 0; art[i][j] != '\0'; ++j)
            if (row + i < ROWS && column + j < COLUMNS)
                map[row + i][column + j] = art[i][j];
}

// Function to draw the character Valdrik on the map at a specified row and column
void drawValdrik(char map[ROWS][COLUMNS], int row, int column)
{
    // Static 2D array representing Valdrik's sprite art
    const char art[9][16] = {
        "   /^^^^^\\   ", // Short hair detail
        "  |  o o  |  ",  // Firm face expression
        "  |   -   |  ",  // Concentrated mouth
        "  |_______|  ",  // Straight jawline
        "  /|     |\\  ", // Armed arms
        " | |=====| | ",  // Light armor chest plate
        "   |  |  |   ",  // Tight waist
        "  /   |   \\  ", // Ready legs stance
        " /____|____\\ "  // Functional boots
    };

    // Copy sprite art to map with bounds checking
    for (int i = 0; i < 9; ++i)
        for (int j = 0; art[i][j] != '\0'; ++j)
            if (row + i < ROWS && column + j < COLUMNS)
                map[row + i][column + j] = art[i][j];
}

#endif // CHARACTERS_DRAW_H
