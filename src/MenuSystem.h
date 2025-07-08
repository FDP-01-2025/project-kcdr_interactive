#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include "map.h"

class MenuSystem
{
public:
    // Display main menu
    static void displayMainMenu();

    // Display death screen
    static void displayDeathScreen();

    // Get validated user input
    static int getValidatedInput(int minOption, int maxOption);

    // Clear console screen
    static void clearScreen();

    // Display all save slots
    static void displayAllSaves();

    // Display exit confirmation
    static void displayExitScreen();
};

void MenuSystem::displayMainMenu()
{
    clearScreen();

    Map gameMap;
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset();

    // Add menu content to the map
    std::string title = "MAIN MENU";
    std::string option1 = "1. New Quest";
    std::string option2 = "2. Load Adventure";
    std::string option3 = "3. Exit Realm";
    std::string prompt = "Choose your path, warrior: ";

    int startRow = 8;
    int titleCol = (COLUMNS - title.length()) / 2;
    int option1Col = (COLUMNS - option1.length()) / 2;
    int option2Col = (COLUMNS - option2.length()) / 2;
    int option3Col = (COLUMNS - option3.length()) / 2;
    int promptCol = (COLUMNS - prompt.length()) / 2;

    for (int i = 0; i < title.length(); ++i)
        grid[startRow][titleCol + i] = title[i];
    for (int i = 0; i < option1.length(); ++i)
        grid[startRow + 3][option1Col + i] = option1[i];
    for (int i = 0; i < option2.length(); ++i)
        grid[startRow + 4][option2Col + i] = option2[i];
    for (int i = 0; i < option3.length(); ++i)
        grid[startRow + 5][option3Col + i] = option3[i];
    for (int i = 0; i < prompt.length(); ++i)
        grid[startRow + 7][promptCol + i] = prompt[i];

    gameMap.display();
}

void MenuSystem::displayDeathScreen()
{
    clearScreen();

    Map gameMap;
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset();

    std::string title = "YOU HAVE BEEN DEFEATED";
    std::string msg1 = "The darkness claims another warrior...";
    std::string msg2 = "But your legend need not end here.";
    std::string msg3 = "Choose your fate:";
    std::string option1 = "1. Continue from last save";
    std::string option2 = "2. Return to main menu";
    std::string prompt = "What is your choice?";

    int startRow = 6;
    int titleCol = (COLUMNS - title.length()) / 2;
    int msg1Col = (COLUMNS - msg1.length()) / 2;
    int msg2Col = (COLUMNS - msg2.length()) / 2;
    int msg3Col = (COLUMNS - msg3.length()) / 2;
    int option1Col = (COLUMNS - option1.length()) / 2;
    int option2Col = (COLUMNS - option2.length()) / 2;
    int promptCol = (COLUMNS - prompt.length()) / 2;

    for (int i = 0; i < title.length(); ++i)
        grid[startRow][titleCol + i] = title[i];
    for (int i = 0; i < msg1.length(); ++i)
        grid[startRow + 2][msg1Col + i] = msg1[i];
    for (int i = 0; i < msg2.length(); ++i)
        grid[startRow + 3][msg2Col + i] = msg2[i];
    for (int i = 0; i < msg3.length(); ++i)
        grid[startRow + 5][msg3Col + i] = msg3[i];
    for (int i = 0; i < option1.length(); ++i)
        grid[startRow + 7][option1Col + i] = option1[i];
    for (int i = 0; i < option2.length(); ++i)
        grid[startRow + 8][option2Col + i] = option2[i];
    for (int i = 0; i < prompt.length(); ++i)
        grid[startRow + 10][promptCol + i] = prompt[i];

    gameMap.display();
}

void MenuSystem::displayExitScreen()
{
    clearScreen();

    Map gameMap;
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset();

    std::string farewell1 = "FAREWELL";
    std::string farewell2 = "May the light of Alba guide your path...";
    std::string farewell3 = "Thank you for playing!";
    std::string farewell4 = "Press any key to exit...";

    int startRow = 8;
    int col1 = (COLUMNS - farewell1.length()) / 2;
    int col2 = (COLUMNS - farewell2.length()) / 2;
    int col3 = (COLUMNS - farewell3.length()) / 2;
    int col4 = (COLUMNS - farewell4.length()) / 2;

    for (int i = 0; i < farewell1.length(); ++i)
        grid[startRow][col1 + i] = farewell1[i];
    for (int i = 0; i < farewell2.length(); ++i)
        grid[startRow + 2][col2 + i] = farewell2[i];
    for (int i = 0; i < farewell3.length(); ++i)
        grid[startRow + 3][col3 + i] = farewell3[i];
    for (int i = 0; i < farewell4.length(); ++i)
        grid[startRow + 5][col4 + i] = farewell4[i];

    gameMap.display();
}

int MenuSystem::getValidatedInput(int minOption, int maxOption)
{
    int choice;
    while (true)
    {
        std::cout << "Select option (" << minOption << "-" << maxOption << "): ";
        std::cin >> choice;

        if (std::cin.fail() || choice < minOption || choice > maxOption)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid choice. Please try again: ";
        }
        else
        {
            std::cin.ignore(10000, '\n');
            return choice;
        }
    }
}

void MenuSystem::clearScreen()
{
    system("cls");
}

#endif // MENU_SYSTEM_H
