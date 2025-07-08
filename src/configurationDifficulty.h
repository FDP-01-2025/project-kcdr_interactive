#ifndef DIFICULTY_H // Define to check if this file has already been included in another .h
#define DIFICULTY_H // If it hasn't been included anywhere else, this allows it to be used here

// DO NOT INCLUDE "using namespace std;" IN A HEADER FILE BECAUSE IT COULD CAUSE CONFLICTS WITH OTHER .cpp FILES OR NAME DECLARATIONS (GOOD PRACTICE)
#include <iostream>
#include <conio.h> // For _getch()
#include <cstdlib> // For system()
#include "map.h"   // To use map and its dimensions

// Enum to define the difficulty levels
enum Difficulty
{
    EASY = 1,   // Easy difficulty level
    NORMAL = 2, // Normal difficulty level
    HARD = 3    // Hard difficulty level
};

// Class to hold the configuration for each difficulty level
// This class contains the player's and enemy's stats for each difficulty level
class configurationDifficulty
{
public:
    int enemyHealth;
    int enemyAttack;

    configurationDifficulty(int h = 0, int a = 0) // constructor con valores por defecto (0,0)
        : enemyHealth(h), enemyAttack(a)
    {
    } // Se inician los valores con los datos dados
};

configurationDifficulty selectDifficult()
{
    Map gameMap; // Create map instance
    int option;

    // Clear the grid and get reference to it
    gameMap.reset();
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();

    // Draw title in the main grid
    std::string title = "=== DIFFICULTY SELECTION ===";
    int titleStartCol = (COLUMNS - title.length()) / 2;
    for (int i = 0; i < title.length(); ++i)
    {
        grid[3][titleStartCol + i] = title[i];
    }

    // Draw difficulty options in the main grid
    std::string difficulties[3] = {
        "1. Easy   (Enemies weaker: -10 HP, -3 ATK)",
        "2. Normal (Enemies standard stats)",
        "3. Hard   (Enemies stronger: +15 HP, +8 ATK)"};

    for (int i = 0; i < 3; ++i)
    {
        // Center the text
        int startCol = (COLUMNS - difficulties[i].length()) / 2;
        for (int j = 0; j < difficulties[i].length() && startCol + j < COLUMNS - 1; ++j)
        {
            grid[6 + i * 2][startCol + j] = difficulties[i][j];
        }
    }

    // Draw selection prompt
    std::string prompt = "Select your difficulty (1-3):";
    int promptStartCol = (COLUMNS - prompt.length()) / 2;
    for (int i = 0; i < prompt.length(); ++i)
    {
        grid[14][promptStartCol + i] = prompt[i];
    }

    do
    {
        // Display the map
        system("cls");
        gameMap.display();

        // Get player selection
        std::cin >> option;

        switch (option)
        {
        case 1: // Easy
        {
            // Clear grid and show confirmation
            gameMap.reset();
            std::string confirmation = "You selected: EASY difficulty";
            int confirmStartCol = (COLUMNS - confirmation.length()) / 2;
            for (int i = 0; i < confirmation.length(); ++i)
            {
                grid[10][confirmStartCol + i] = confirmation[i];
            }

            std::string continueMsg = "Press any key to continue...";
            int continueStartCol = (COLUMNS - continueMsg.length()) / 2;
            for (int i = 0; i < continueMsg.length(); ++i)
            {
                grid[12][continueStartCol + i] = continueMsg[i];
            }

            system("cls");
            gameMap.display();
            _getch();

            return configurationDifficulty(-10, -3); // Weaker enemies
        }
        break;

        case 2: // Normal
        {
            // Clear grid and show confirmation
            gameMap.reset();
            std::string confirmation = "You selected: NORMAL difficulty";
            int confirmStartCol = (COLUMNS - confirmation.length()) / 2;
            for (int i = 0; i < confirmation.length(); ++i)
            {
                grid[10][confirmStartCol + i] = confirmation[i];
            }

            std::string continueMsg = "Press any key to continue...";
            int continueStartCol = (COLUMNS - continueMsg.length()) / 2;
            for (int i = 0; i < continueMsg.length(); ++i)
            {
                grid[12][continueStartCol + i] = continueMsg[i];
            }

            system("cls");
            gameMap.display();
            _getch();

            return configurationDifficulty(0, 0); // enemies with basic stats
        }
        break;

        case 3:
        {
            // Clear grid and show confirmation
            gameMap.reset();
            std::string confirmation = "You selected: HARD difficulty";
            int confirmStartCol = (COLUMNS - confirmation.length()) / 2;
            for (int i = 0; i < confirmation.length(); ++i)
            {
                grid[10][confirmStartCol + i] = confirmation[i];
            }

            std::string continueMsg = "Press any key to continue...";
            int continueStartCol = (COLUMNS - continueMsg.length()) / 2;
            for (int i = 0; i < continueMsg.length(); ++i)
            {
                grid[12][continueStartCol + i] = continueMsg[i];
            }

            system("cls");
            gameMap.display();
            _getch();

            return configurationDifficulty(15, 8); // Stronger enemies
        }
        break;

        default:
        {
            // Clear grid and show error message
            gameMap.reset();
            std::string errorMsg = "Invalid option. Please select 1, 2, or 3.";
            int errorStartCol = (COLUMNS - errorMsg.length()) / 2;
            for (int i = 0; i < errorMsg.length(); ++i)
            {
                grid[10][errorStartCol + i] = errorMsg[i];
            }

            std::string continueMsg = "Press any key to try again...";
            int continueStartCol = (COLUMNS - continueMsg.length()) / 2;
            for (int i = 0; i < continueMsg.length(); ++i)
            {
                grid[12][continueStartCol + i] = continueMsg[i];
            }

            system("cls");
            gameMap.display();
            _getch();

            // Restore the original difficulty selection screen
            gameMap.reset();

            // Redraw title
            for (int i = 0; i < title.length(); ++i)
            {
                grid[3][titleStartCol + i] = title[i];
            }

            // Redraw difficulty options
            for (int i = 0; i < 3; ++i)
            {
                int startCol = (COLUMNS - difficulties[i].length()) / 2;
                for (int j = 0; j < difficulties[i].length() && startCol + j < COLUMNS - 1; ++j)
                {
                    grid[6 + i * 2][startCol + j] = difficulties[i][j];
                }
            }

            // Redraw selection prompt
            for (int i = 0; i < prompt.length(); ++i)
            {
                grid[14][promptStartCol + i] = prompt[i];
            }
        }
        break;
        }
    } while (true);
}

#endif