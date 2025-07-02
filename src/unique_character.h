#ifndef UNIQUE_CHARACTER_H
#define UNIQUE_CHARACTER_H

#include <iostream>
#include <string>
#include <conio.h>           // For _getch()
#include <cstdlib>           // For system()
#include "characters_draw.h" // To use drawing functions
#include "Player.h"          // Player class
#include "map.h"             // To use map and its dimensions

// Create character instances as Player class objects
const Player allCharacters[4] = {
    Player(60, 100, 40, 120), // Rhaekor
    Player(80, 40, 100, 60),  // Cerephios
    Player(100, 60, 60, 90),  // Kaelren
    Player(70, 80, 70, 100)   // Valdrik
};

// Name of each character, to identify which one has been chosen
const std::string characterNames[4] = {
    "Rhaekor", "Cerephios", "Kaelren", "Valdrik"
};

// Global variable that stores the character chosen by the player
Player playerSelected(0, 0, 0, 0); // Empty initialization by default
std::string selectedName;          // Name of the selected character

// Shows the selection menu and saves the chosen character
void chooseCharacterAndSave()
{
    Map gameMap; // Create map instance
    int option;
    
    // Clear the grid and get reference to it
    gameMap.reset();
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    
    // Draw title in the main grid
    std::string title = "=== CHARACTER SELECTION ===";
    int titleStartCol = (COLUMNS - title.length()) / 2;
    for (int i = 0; i < title.length(); ++i) {
        grid[3][titleStartCol + i] = title[i];
    }
    
    // Draw character options in the main grid
    for (int i = 0; i < 4; ++i) {
        std::string characterInfo = std::to_string(i + 1) + ". " + characterNames[i] +
                                  " (HP:" + std::to_string(allCharacters[i].getHealth()) +
                                  " ATK:" + std::to_string(allCharacters[i].getAttack()) +
                                  " DEF:" + std::to_string(allCharacters[i].getDefense()) +
                                  " ESP:" + std::to_string(allCharacters[i].getSpecialAttack()) + ")";
        
        // Center the text
        int startCol = (COLUMNS - characterInfo.length()) / 2;
        for (int j = 0; j < characterInfo.length() && startCol + j < COLUMNS - 1; ++j) {
            grid[6 + i * 2][startCol + j] = characterInfo[j];
        }
    }
    
    // Draw selection prompt
    std::string prompt = "Select your character (1-4):";
    int promptStartCol = (COLUMNS - prompt.length()) / 2;
    for (int i = 0; i < prompt.length(); ++i) {
        grid[16][promptStartCol + i] = prompt[i];
    }
    
    // Display the map
    system("cls");
    gameMap.display();
    
    // Get player selection
    std::cin >> option;

    if (option < 1 || option > 4) {
        // Clear grid and show error message
        gameMap.reset();
        std::string errorMsg = "Invalid selection. Defaulting to Rhaekor.";
        int errorStartCol = (COLUMNS - errorMsg.length()) / 2;
        for (int i = 0; i < errorMsg.length(); ++i) {
            grid[10][errorStartCol + i] = errorMsg[i];
        }
        
        playerSelected = allCharacters[0];
        selectedName = characterNames[0];
    } else {
        playerSelected = allCharacters[option - 1];
        selectedName = characterNames[option - 1];
    }

    // Set the player's name to the selected character name
    playerSelected.setName(selectedName);
    
    // Clear grid and show confirmation
    gameMap.reset();
    std::string confirmation = "You have selected: " + selectedName;
    int confirmStartCol = (COLUMNS - confirmation.length()) / 2;
    for (int i = 0; i < confirmation.length(); ++i) {
        grid[10][confirmStartCol + i] = confirmation[i];
    }
    
    std::string continueMsg = "Press any key to continue...";
    int continueStartCol = (COLUMNS - continueMsg.length()) / 2;
    for (int i = 0; i < continueMsg.length(); ++i) {
        grid[12][continueStartCol + i] = continueMsg[i];
    }
    
    system("cls");
    gameMap.display();
    
    _getch(); // Wait for user input
}

// Automatically draws the chosen character based on its name
void drawSelectedCharacter(char map[ROWS][COLUMNS], int row, int col)
{
    if (selectedName == "Rhaekor")
        drawRhaekor(map, row, col);
    else if (selectedName == "Cerephios")
        drawCerephios(map, row, col);
    else if (selectedName == "Kaelren")
        drawKaelren(map, row, col);
    else if (selectedName == "Valdrik")
        drawValdrik(map, row, col);
}

#endif // UNIQUE_CHARACTER_H
