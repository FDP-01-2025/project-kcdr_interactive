#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <iostream>
#include <conio.h>
#include "TitleScreen.h"
#include "MenuSystem.h"
#include "SaveManager.h"
#include "configurationDifficulty.h"
#include "unique_character.h"
#include "map.h"

// Forward declarations
extern Player playerSelected;
extern std::string selectedName;
void playGame();

class GameController
{
public:
    // Main menu loop
    static void runMainMenu();
    
    // Handle new game creation
    static void handleNewGame();
    
    // Handle load game functionality
    static void handleLoadGame();
    
    // Handle death screen
    static void handleDeathScreen();
    
    // Display character selection
    static void displayCharacterSelection();
    
    // Display difficulty selection
    static configurationDifficulty displayDifficultySelection();
    
    // Display all saves with info
    static void displayAllSaves();
    
    // Show successful operations
    static void showSuccessMessage(const std::string& message);
    static void showErrorMessage(const std::string& message);
};

void GameController::runMainMenu()
{
    SaveManager::loadExistingSaves();
    
    int choice;
    bool exitGame = false;

    while (!exitGame)
    {
        MenuSystem::displayMainMenu();
        choice = MenuSystem::getValidatedInput(1, 3);

        switch (choice)
        {
        case 1:
            handleNewGame();
            break;
        case 2:
            handleLoadGame();
            break;
        case 3:
            MenuSystem::displayExitScreen();
            _getch();
            exitGame = true;
            break;
        }
    }
}

void GameController::handleNewGame()
{
    MenuSystem::clearScreen();
    
    Map gameMap;
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset();
    
    std::string title = "NEW QUEST";
    std::string message1 = "The dawn of a new adventure begins...";
    std::string message2 = "Press any key to continue...";
    
    int startRow = 10;
    int titleCol = (COLUMNS - title.length()) / 2;
    int msg1Col = (COLUMNS - message1.length()) / 2;
    int msg2Col = (COLUMNS - message2.length()) / 2;
    
    for (int i = 0; i < title.length(); ++i) grid[startRow][titleCol + i] = title[i];
    for (int i = 0; i < message1.length(); ++i) grid[startRow + 2][msg1Col + i] = message1[i];
    for (int i = 0; i < message2.length(); ++i) grid[startRow + 4][msg2Col + i] = message2[i];
    
    gameMap.display();
    _getch();

    // Character selection first
    displayCharacterSelection();
    
    // Then difficulty selection
    configurationDifficulty selectedConfig = displayDifficultySelection();
    SaveManager::setCurrentDifficulty(selectedConfig);

    // Find available save slot
    int emptySlot = SaveManager::findEmptySlot();
    std::string saveSlot = "Game" + std::to_string(emptySlot);
    
    if (emptySlot > 5) // MAX_SAVE_SLOTS
    {
        // All slots full, let user choose which to overwrite
        MenuSystem::clearScreen();
        displayAllSaves();
        std::cout << "\nAll save slots are full. Choose slot to overwrite (1-5): ";
        int choice = MenuSystem::getValidatedInput(1, 5);
        saveSlot = "Game" + std::to_string(choice);
    }

    // Create comprehensive game data
    GameData newGame(selectedName, SaveManager::getCurrentDateTime(), "Starting Village",
                     playerSelected, selectedConfig, 0, 15, 45, 0);
    SaveManager::saveGameData(saveSlot, newGame);

    showSuccessMessage("Quest log saved successfully!");

    // Start the game
    playGame();
}

void GameController::handleLoadGame()
{
    SaveManager::loadExistingSaves();
    
    // Check if any saves exist
    bool hasAnySave = false;
    std::map<std::string, GameData>& saves = SaveManager::getGameSaves();
    
    for (int i = 1; i <= 5; i++)
    {
        std::string saveKey = "Game" + std::to_string(i);
        if (saves[saveKey].exists)
        {
            hasAnySave = true;
            break;
        }
    }
    
    if (!hasAnySave)
    {
        showErrorMessage("No saved quests found in the archives.");
        handleNewGame();
        return;
    }

    // Display all available saves
    MenuSystem::clearScreen();
    displayAllSaves();
    
    int selectedSave = MenuSystem::getValidatedInput(1, 5);
    
    if (!SaveManager::loadSave(selectedSave))
    {
        showErrorMessage("Selected save slot is empty!");
        return;
    }

    showSuccessMessage("Quest loaded successfully!");
    playGame();
}

void GameController::handleDeathScreen()
{
    MenuSystem::displayDeathScreen();
    std::cout << "\nEnter choice: ";
    
    int choice = MenuSystem::getValidatedInput(1, 2);
    
    switch (choice)
    {
    case 1:
        {
            // Find most recent save (no pointers)
            GameData mostRecentSave;
            bool foundSave = SaveManager::getMostRecentSave(mostRecentSave);
            
            if (foundSave)
            {
                playerSelected = mostRecentSave.playerData;
                selectedName = mostRecentSave.characterName;
                SaveManager::updatePlayerPosition(mostRecentSave.currentMapX, mostRecentSave.currentMapY);
                SaveManager::setCurrentDifficulty(mostRecentSave.difficultyConfig);
                
                showSuccessMessage("Returning to your last checkpoint...");
                playGame();
            }
            else
            {
                runMainMenu();
            }
        }
        break;
        
    case 2:
        runMainMenu();
        break;
    }
}

void GameController::displayCharacterSelection()
{
    MenuSystem::clearScreen();
    chooseCharacterAndSave();
}

configurationDifficulty GameController::displayDifficultySelection()
{
    MenuSystem::clearScreen();
    
    Map gameMap;
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset();
    
    std::string title = "DIFFICULTY SELECTION";
    std::string subtitle = "Choose the challenge level for your quest:";
    std::string opt1 = "1. APPRENTICE - For new adventurers";
    std::string desc1 = "Enemy stats reduced | Recommended for beginners";
    std::string opt2 = "2. VETERAN - The standard challenge";
    std::string desc2 = "Balanced gameplay | Classic RPG experience";
    std::string opt3 = "3. LEGENDARY - For master warriors";
    std::string desc3 = "Enhanced enemy stats | True test of skill";
    
    int startRow = 6;
    int titleCol = (COLUMNS - title.length()) / 2;
    int subtitleCol = (COLUMNS - subtitle.length()) / 2;
    int opt1Col = (COLUMNS - opt1.length()) / 2;
    int desc1Col = (COLUMNS - desc1.length()) / 2;
    int opt2Col = (COLUMNS - opt2.length()) / 2;
    int desc2Col = (COLUMNS - desc2.length()) / 2;
    int opt3Col = (COLUMNS - opt3.length()) / 2;
    int desc3Col = (COLUMNS - desc3.length()) / 2;
    
    for (int i = 0; i < title.length(); ++i) grid[startRow][titleCol + i] = title[i];
    for (int i = 0; i < subtitle.length(); ++i) grid[startRow + 2][subtitleCol + i] = subtitle[i];
    for (int i = 0; i < opt1.length(); ++i) grid[startRow + 4][opt1Col + i] = opt1[i];
    for (int i = 0; i < desc1.length(); ++i) grid[startRow + 5][desc1Col + i] = desc1[i];
    for (int i = 0; i < opt2.length(); ++i) grid[startRow + 7][opt2Col + i] = opt2[i];
    for (int i = 0; i < desc2.length(); ++i) grid[startRow + 8][desc2Col + i] = desc2[i];
    for (int i = 0; i < opt3.length(); ++i) grid[startRow + 10][opt3Col + i] = opt3[i];
    for (int i = 0; i < desc3.length(); ++i) grid[startRow + 11][desc3Col + i] = desc3[i];
    
    gameMap.display();
    
    // Add space and clear prompt before asking for input
    std::cout << "\n";
    int choice = MenuSystem::getValidatedInput(1, 3);

    switch (choice)
    {
    case 1:
        {
            MenuSystem::clearScreen();
            Map successMap;
            char (&successGrid)[ROWS][COLUMNS] = successMap.getGrid();
            successMap.reset();
            
            std::string msg = "Apprentice difficulty selected. May fortune favor you!";
            int msgCol = (COLUMNS - msg.length()) / 2;
            for (int i = 0; i < msg.length(); ++i) successGrid[12][msgCol + i] = msg[i];
            
            std::string continueMsg = "Press any key to continue...";
            int continueCol = (COLUMNS - continueMsg.length()) / 2;
            for (int i = 0; i < continueMsg.length(); ++i) successGrid[14][continueCol + i] = continueMsg[i];
            
            successMap.display();
            _getch();
            return configurationDifficulty(-10, -5);
        }
    case 2:
        {
            MenuSystem::clearScreen();
            Map successMap;
            char (&successGrid)[ROWS][COLUMNS] = successMap.getGrid();
            successMap.reset();
            
            std::string msg = "Veteran difficulty selected. Prepare for battle!";
            int msgCol = (COLUMNS - msg.length()) / 2;
            for (int i = 0; i < msg.length(); ++i) successGrid[12][msgCol + i] = msg[i];
            
            std::string continueMsg = "Press any key to continue...";
            int continueCol = (COLUMNS - continueMsg.length()) / 2;
            for (int i = 0; i < continueMsg.length(); ++i) successGrid[14][continueCol + i] = continueMsg[i];
            
            successMap.display();
            _getch();
            return configurationDifficulty(0, 0);
        }
    case 3:
        {
            MenuSystem::clearScreen();
            Map successMap;
            char (&successGrid)[ROWS][COLUMNS] = successMap.getGrid();
            successMap.reset();
            
            std::string msg = "Legendary difficulty selected. Steel yourself, warrior!";
            int msgCol = (COLUMNS - msg.length()) / 2;
            for (int i = 0; i < msg.length(); ++i) successGrid[12][msgCol + i] = msg[i];
            
            std::string continueMsg = "Press any key to continue...";
            int continueCol = (COLUMNS - continueMsg.length()) / 2;
            for (int i = 0; i < continueMsg.length(); ++i) successGrid[14][continueCol + i] = continueMsg[i];
            
            successMap.display();
            _getch();
            return configurationDifficulty(15, 10);
        }
    default:
        return configurationDifficulty(0, 0);
    }
}

void GameController::displayAllSaves()
{
    Map gameMap;
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset();
    
    std::string title = "SAVE SLOT SELECTION";
    int titleCol = (COLUMNS - title.length()) / 2;
    for (int i = 0; i < title.length(); ++i) grid[5][titleCol + i] = title[i];
    
    std::map<std::string, GameData>& saves = SaveManager::getGameSaves();
    
    int row = 8;
    for (int i = 1; i <= 5; i++)
    {
        std::string saveKey = "Game" + std::to_string(i);
        std::string slotInfo;
        
        if (saves[saveKey].exists)
        {
            slotInfo = std::to_string(i) + ". " + saves[saveKey].characterName + 
                      " - " + saves[saveKey].creationDate.substr(0, 10);
        }
        else
        {
            slotInfo = std::to_string(i) + ". Empty Slot";
        }
        
        int slotCol = (COLUMNS - slotInfo.length()) / 2;
        for (int j = 0; j < slotInfo.length(); ++j) grid[row][slotCol + j] = slotInfo[j];
        row++;
    }
    
    // Add prompt message
    std::string prompt = "Select save to load (1-5):";
    int promptCol = (COLUMNS - prompt.length()) / 2;
    for (int i = 0; i < prompt.length(); ++i) grid[15][promptCol + i] = prompt[i];
    
    gameMap.display();
}

void GameController::showSuccessMessage(const std::string& message)
{
    MenuSystem::clearScreen();
    Map gameMap;
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset();
    
    // Split long messages into multiple lines
    std::string line1, line2, line3;
    if (message.find("Quest log saved") != std::string::npos)
    {
        line1 = "Quest log saved successfully!";
        line2 = "Press any key to begin your adventure...";
    }
    else if (message.find("Quest loaded") != std::string::npos)
    {
        line1 = "Quest loaded successfully!";
        line2 = "Welcome back, " + selectedName + "!";
        line3 = "Press any key to continue your adventure...";
    }
    else if (message.find("Returning") != std::string::npos)
    {
        line1 = "Returning to your last checkpoint...";
        line2 = "Press any key to continue...";
    }
    else
    {
        line1 = message;
        line2 = "Press any key to continue...";
    }
    
    int line1Col = (COLUMNS - line1.length()) / 2;
    for (int i = 0; i < line1.length(); ++i) grid[10][line1Col + i] = line1[i];
    
    if (!line2.empty())
    {
        int line2Col = (COLUMNS - line2.length()) / 2;
        for (int i = 0; i < line2.length(); ++i) grid[12][line2Col + i] = line2[i];
    }
    
    if (!line3.empty())
    {
        int line3Col = (COLUMNS - line3.length()) / 2;
        for (int i = 0; i < line3.length(); ++i) grid[14][line3Col + i] = line3[i];
    }
    
    gameMap.display();
    _getch();
}

void GameController::showErrorMessage(const std::string& message)
{
    MenuSystem::clearScreen();
    Map gameMap;
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset();
    
    // Split long error messages
    std::string line1, line2;
    if (message.find("No saved quests") != std::string::npos)
    {
        line1 = "No saved quests found in the archives.";
        line2 = "Redirecting to New Quest...";
    }
    else if (message.find("Selected save slot") != std::string::npos)
    {
        line1 = "Selected save slot is empty!";
        line2 = "Press any key to return to main menu...";
    }
    else
    {
        line1 = message;
        line2 = "Press any key to continue...";
    }
    
    int line1Col = (COLUMNS - line1.length()) / 2;
    for (int i = 0; i < line1.length(); ++i) grid[10][line1Col + i] = line1[i];
    
    if (!line2.empty())
    {
        int line2Col = (COLUMNS - line2.length()) / 2;
        for (int i = 0; i < line2.length(); ++i) grid[12][line2Col + i] = line2[i];
    }
    
    gameMap.display();
    _getch();
}

// Wrapper function for use in other modules
inline void handleDeathScreen()
{
    GameController::handleDeathScreen();
}

#endif // GAME_CONTROLLER_H
