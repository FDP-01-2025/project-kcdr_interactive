#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "map.h"

class TitleScreen
{
public:
    // Display the main title with ASCII art
    static void displayGameTitle();
    
    // Display the introduction screen after title
    static void displayIntroduction();
    
    // Clear console screen
    static void clearScreen();
    
    // Animation delay function
    static void animationDelay(int cycles);
};

void TitleScreen::displayGameTitle()
{
    clearScreen();
    std::cout << "\n\n";
    
    // ASCII Art Title - BROTHERS OF THE DAWN
    std::cout << "  ____  ____   ___ _____ _   _ _____ ____  ____  \n";
    animationDelay(30000000);
    std::cout << " | __ )|  _ \\ / _ \\_   _| | | | ____|  _ \\/ ___| \n";
    animationDelay(30000000);
    std::cout << " |  _ \\| |_) | | | || | | |_| |  _| | |_) \\___ \\ \n";
    animationDelay(30000000);
    std::cout << " | |_) |  _ <| |_| || | |  _  | |___|  _ < ___) |\n";
    animationDelay(30000000);
    std::cout << " |____/|_| \\_\\\\___/ |_| |_| |_|_____|_| \\_\\____/ \n";
    animationDelay(30000000);
    std::cout << "\n";
    std::cout << "    ___  _____   _____ _   _ _____   ____    _    _    _ _   _ \n";
    animationDelay(30000000);
    std::cout << "   / _ \\|  ___| |_   _| | | | ____| |  _ \\  / \\  | |  | | \\ | |\n";
    animationDelay(30000000);
    std::cout << "  | | | | |_      | | | |_| |  _|   | | | |/ _ \\ | |  | |  \\| |\n";
    animationDelay(30000000);
    std::cout << "  | |_| |  _|     | | |  _  | |___  | |_| / ___ \\| |/\\| | |\\  |\n";
    animationDelay(30000000);
    std::cout << "   \\___/|_|       |_| |_| |_|_____| |____/_/   \\_\\__/\\__|_| \\_|\n";
    animationDelay(30000000);
    std::cout << "\n";
    std::cout << "         _____ ____      _    ____ __  __ _____ _   _ _____ ____  \n";
    animationDelay(30000000);
    std::cout << "        |  ___|  _ \\    / \\  / ___|  \\/  | ____| \\ | |_   _/ ___| \n";
    animationDelay(30000000);
    std::cout << "        | |_  | |_) |  / _ \\| |  _| |\\/| |  _| |  \\| | | | \\___ \\ \n";
    animationDelay(30000000);
    std::cout << "        |  _| |  _ <  / ___ \\ |_| | |  | | |___| |\\  | | |  ___) |\n";
    animationDelay(30000000);
    std::cout << "        |_|   |_| \\_\\/_/   \\_\\____|_|  |_|_____|_| \\_| |_| |____/ \n";
    animationDelay(30000000);
    std::cout << "\n";
    std::cout << "               ___  _____   _____ _   _ _____     _    _     ____    _    \n";
    animationDelay(30000000);
    std::cout << "              / _ \\|  ___| |_   _| | | | ____|   / \\  | |   | __ )  / \\   \n";
    animationDelay(30000000);
    std::cout << "             | | | | |_      | | | |_| |  _|    / _ \\ | |   |  _ \\ / _ \\  \n";
    animationDelay(30000000);
    std::cout << "             | |_| |  _|     | | |  _  | |___  / ___ \\| |___| |_) / ___ \\ \n";
    animationDelay(30000000);
    std::cout << "              \\___/|_|       |_| |_| |_|_____|/_/   \\_\\_____|____/_/   \\_\\\n";
    animationDelay(50000000);
    std::cout << "\n\n";
    std::cout << "                    Press any key to continue...\n";
    _getch();
}

void TitleScreen::displayIntroduction()
{
    clearScreen();
    
    Map gameMap;
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset();
    
    // Add content to the map
    std::string line1 = "A FANTASY RPG ADVENTURE";
    std::string line2 = "In the realm of Alba, ancient powers stir...";
    std::string line3 = "Four brothers must unite to restore the balance";
    std::string line4 = "Choose your destiny, brave warrior!";
    std::string line5 = "Press any key to enter the realm...";
    
    int startRow = 8;
    int startCol1 = (COLUMNS - line1.length()) / 2;
    int startCol2 = (COLUMNS - line2.length()) / 2;
    int startCol3 = (COLUMNS - line3.length()) / 2;
    int startCol4 = (COLUMNS - line4.length()) / 2;
    int startCol5 = (COLUMNS - line5.length()) / 2;
    
    // Ensure all positions are valid before writing
    if (startCol1 >= 0 && startCol1 + line1.length() < COLUMNS) {
        for (int i = 0; i < line1.length(); ++i) grid[startRow][startCol1 + i] = line1[i];
    }
    if (startCol2 >= 0 && startCol2 + line2.length() < COLUMNS) {
        for (int i = 0; i < line2.length(); ++i) grid[startRow + 2][startCol2 + i] = line2[i];
    }
    if (startCol3 >= 0 && startCol3 + line3.length() < COLUMNS) {
        for (int i = 0; i < line3.length(); ++i) grid[startRow + 3][startCol3 + i] = line3[i];
    }
    if (startCol4 >= 0 && startCol4 + line4.length() < COLUMNS) {
        for (int i = 0; i < line4.length(); ++i) grid[startRow + 4][startCol4 + i] = line4[i];
    }
    if (startCol5 >= 0 && startCol5 + line5.length() < COLUMNS) {
        for (int i = 0; i < line5.length(); ++i) grid[startRow + 6][startCol5 + i] = line5[i];
    }
    
    gameMap.display();
    
    // Add a small pause to ensure the screen is displayed
    animationDelay(10000000);
    
    _getch();
}

void TitleScreen::clearScreen()
{
    system("cls");
}

void TitleScreen::animationDelay(int cycles)
{
    for(int i = 0; i < cycles; i++) {}
}

#endif // TITLE_SCREEN_H
