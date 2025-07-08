#ifndef GAME_CONTROLLER_H // Header guard: prevents multiple inclusions during compilation
#define GAME_CONTROLLER_H

// ======== REQUIRED SYSTEM LIBRARIES ========
// Standard C++ libraries needed for game flow control and user interaction
#include <iostream> // For console input/output operations (std::cout, std::cin)
#include <conio.h>  // For immediate key capture without pressing Enter (_getch function)
#include <cstdlib>  // For program termination function (exit())

// ======== GAME SYSTEM MODULES ========
// Include custom game systems that the controller coordinates and manages
#include "TitleScreen.h"             // Title screen display and branding functionality
#include "MenuSystem.h"              // Menu navigation, input validation, and UI systems
#include "SaveManager.h"             // Save/load game state management and file operations
#include "configurationDifficulty.h" // Difficulty settings and enemy stat modifiers
#include "unique_character.h"        // Character creation and selection system
#include "map.h"                     // Map display, navigation, and world management
#include "enemy_utils.h"             // Enemy difficulty scaling functions
#include "Story.h"

// ======== EXTERNAL DEPENDENCIES ========
// Forward declarations for global variables and functions defined in other modules
// This avoids circular dependencies while allowing access to essential game components
extern Player playerSelected;    // Global player instance - maintains character state throughout the game
extern std::string selectedName; // Global player name - used for display and save identification
void playGame();                 // Main gameplay loop function - defined in map.h

// ======== MAIN GAME FLOW CONTROLLER CLASS ========
// This class serves as the central coordinator for all major game systems and user interactions
// It manages the complete game lifecycle from startup to shutdown, including menus, save/load, and transitions
// All methods are static to provide global access without requiring object instantiation
class GameController
{
public:
    // ======== CORE GAME FLOW METHODS ========
    // These methods handle the primary game flow and state transitions

    // Controls the main menu loop - the central hub for all game operations
    // Manages menu display, user input processing, and navigation to game functions
    static void runMainMenu();

    // Handles complete new game creation workflow
    // Manages character creation, difficulty selection, save slot assignment, and game initialization
    static void handleNewGame();

    // Manages the load game functionality and save file selection
    // Handles save file validation, loading, and error management for missing saves
    static void handleLoadGame();

    // Processes player death scenarios and recovery options
    // Provides choice between returning to last checkpoint or main menu
    static void handleDeathScreen();

    // ======== USER INTERFACE AND DISPLAY METHODS ========
    // These methods handle specialized UI screens and user interaction flows

    // Manages character selection screen and player customization
    // Interfaces with the character creation system to allow player choice
    static void displayCharacterSelection();

    // Presents difficulty selection interface and processes user choice
    // Returns the selected difficulty configuration for game balance adjustment
    static configurationDifficulty displayDifficultySelection();

    // Shows all available save slots with detailed information
    // Displays character names, creation dates, and slot availability status
    static void displayAllSaves();

    // ======== FEEDBACK AND MESSAGING SYSTEM ========
    // These methods provide consistent user feedback for various game operations

    // Displays success messages with consistent formatting and user acknowledgment
    // Used for save confirmations, load successes, and positive feedback
    static void showSuccessMessage(const std::string &message);

    // Displays error messages with consistent formatting and recovery options
    // Used for failed operations, missing files, and user guidance
    static void showErrorMessage(const std::string &message);
};

// ======== MAIN MENU CONTROL SYSTEM ========
// This function implements the primary game loop that manages the main menu interface
// It serves as the central hub for all game operations and maintains program flow
void GameController::runMainMenu()
{
    // ======== SAVE SYSTEM INITIALIZATION ========
    // Load all existing save files to make them available for the load game feature
    // This ensures the save system is ready and all save slots are properly indexed
    SaveManager::loadExistingSaves();

    // ======== MENU LOOP VARIABLES ========
    int choice;            // Stores the user's menu selection
    bool exitGame = false; // Flag to control the main menu loop (currently unused but kept for structure)

    // ======== MAIN MENU LOOP ========
    // Continuous loop that displays the menu and processes user choices until exit
    while (!exitGame)
    {
        // ======== MENU DISPLAY AND INPUT ========
        MenuSystem::displayMainMenu();                // Show the main menu options to the user
        choice = MenuSystem::getValidatedInput(1, 3); // Get user input with validation (options 1-3)

        // ======== MENU OPTION PROCESSING ========
        // Process the user's menu selection and route to appropriate handler
        switch (choice)
        {
        case 1:
            handleNewGame(); // Start new game creation workflow
            break;
        case 2:
            handleLoadGame(); // Start load game workflow
            break;
        case 3:
            // ======== GAME EXIT SEQUENCE ========
            MenuSystem::displayExitScreen(); // Show farewell message to user
            _getch();                        // Wait for user acknowledgment
            exit(0);                         // Terminate program immediately (prevents nested loop issues)
            break;
        }
    }
}

// ======== NEW GAME CREATION WORKFLOW ========
// This function manages the complete process of creating and starting a new game
// It handles character creation, difficulty selection, save management, and game initialization
void GameController::handleNewGame()
{
    // ======== GAME STATE RESET ========
    // Reset all global variables to ensure clean state for new game
    SaveManager::resetGameState();

    // ======== SCREEN PREPARATION ========
    MenuSystem::clearScreen(); // Clear console for clean display

    // ======== WELCOME SCREEN SETUP ========
    // Create a themed welcome screen using the map display system for consistency
    Map gameMap;                                     // Create map object for display framework
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid(); // Get reference to map grid for direct manipulation
    gameMap.reset();                                 // Clear map and setup borders/UI

    // ======== WELCOME MESSAGE COMPOSITION ========
    // Create atmospheric text for new game introduction
    std::string title = "NEW QUEST";                                // Main header
    std::string message1 = "The dawn of a new adventure begins..."; // Atmospheric subtitle
    std::string message2 = "Press any key to continue...";          // User instruction

    // ======== TEXT POSITIONING CALCULATIONS ========
    // Calculate center positions for each text element to ensure proper alignment
    int startRow = 10;                               // Vertical starting position
    int titleCol = (COLUMNS - title.length()) / 2;   // Center title horizontally
    int msg1Col = (COLUMNS - message1.length()) / 2; // Center first message
    int msg2Col = (COLUMNS - message2.length()) / 2; // Center second message

    // ======== TEXT RENDERING ========
    // Manually place each character of the text strings into the map grid
    for (int i = 0; i < title.length(); ++i)
        grid[startRow][titleCol + i] = title[i];
    for (int i = 0; i < message1.length(); ++i)
        grid[startRow + 2][msg1Col + i] = message1[i];
    for (int i = 0; i < message2.length(); ++i)
        grid[startRow + 4][msg2Col + i] = message2[i];

    // ======== DISPLAY AND USER INTERACTION ========
    gameMap.display(); // Render the welcome screen
    _getch();          // Wait for user to acknowledge before proceeding

    // ======== CHARACTER CREATION WORKFLOW ========
    displayCharacterSelection(); // Show character selection screen and process user choice

    // ======== DIFFICULTY CONFIGURATION ========
    configurationDifficulty selectedConfig = displayDifficultySelection(); // Get difficulty choice
    SaveManager::setCurrentDifficulty(selectedConfig);                     // Store difficulty for game balance
    applyDifficultyEnemies(selectedConfig);                                // Apply difficulty scaling to all enemies

    // ======== SAVE SLOT MANAGEMENT ========
    // Use the single available save slot
    int emptySlot = 1;                                         // Always use slot 1 (only slot available)
    std::string saveSlot = "Game" + std::to_string(emptySlot); // Create save slot identifier

    // ======== SAVE SLOT OVERWRITE HANDLING ========
    // Check if the single slot is occupied and prompt for overwrite confirmation
    if (SaveManager::countExistingSaves() > 0)
    {
        MenuSystem::clearScreen();
        std::cout << "\nA saved game already exists. Do you want to overwrite it? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice != 'y' && choice != 'Y')
        {
            return; // User chose not to overwrite, return to main menu
        }
    }

    // ======== GAME DATA CREATION ========
    // Create comprehensive game data structure with all necessary information
    GameData newGame(selectedName,                      // Player's chosen character name
                     SaveManager::getCurrentDateTime(), // Current timestamp for save tracking
                     "Starting Village",                // Initial location description
                     playerSelected,                    // Complete player character data
                     selectedConfig,                    // Chosen difficulty configuration
                     0,                                 // Current map ID (start at map 0)
                     15,                                // Starting X coordinate
                     45,                                // Starting Y coordinate
                     0,                                 // Initial enemy kill count
                     100);                              // Starting gold amount
    SaveManager::saveGameData(saveSlot, newGame);       // Write the game data to file

    // ======== SUCCESS FEEDBACK ========
    showSuccessMessage("Quest log saved successfully!"); // Inform user of successful save

    // ======== STORY PROLOGUE ========
    Story::showPrologueOnMap();

    // ======== GAME LAUNCH ========
    playGame(); // Start the main gameplay loop
}

// ======== LOAD GAME WORKFLOW MANAGEMENT ========
// This function handles the complete process of loading the single saved game
// It validates save file existence and loads the game automatically
void GameController::handleLoadGame()
{
    // ======== SAVE SYSTEM REFRESH ========
    // Reload save data to ensure we have the most current information
    SaveManager::loadExistingSaves();

    // ======== SAVE AVAILABILITY CHECK ========
    // Check if the single save slot contains a saved game
    std::map<std::string, GameData> &saves = SaveManager::getGameSaves(); // Get reference to save data
    std::string saveKey = "Game1";                                        // Only slot available

    // ======== NO SAVE FOUND HANDLING ========
    // If no save file exists, provide helpful feedback and redirect to new game creation
    if (!saves[saveKey].exists)
    {
        showErrorMessage("No saved quest found in the archives."); // Inform user with thematic message
        handleNewGame();                                           // Redirect to new game creation
        return;                                                    // Exit function
    }

    // ======== AUTOMATIC SAVE LOADING ========
    // Load the single available save without user selection
    if (!SaveManager::loadSave(1))
    {
        showErrorMessage("Failed to load saved quest!"); // Inform user of load failure
        return;                                          // Return to previous menu
    }

    // ======== SUCCESSFUL LOAD FEEDBACK AND GAME START ========
    showSuccessMessage("Quest loaded successfully!"); // Confirm successful load operation
    playGame();                                       // Start gameplay with loaded data
}

// ======== PLAYER DEATH RECOVERY SYSTEM ========
// This function manages the player death scenario and provides recovery options
// It handles checkpoint restoration and menu navigation after player death
void GameController::handleDeathScreen()
{
    // ======== DEATH SCREEN DISPLAY ========
    MenuSystem::displayDeathScreen(); // Show death screen with available options
    std::cout << "\nEnter choice: ";  // Prompt user for their choice

    // ======== USER CHOICE INPUT ========
    int choice = MenuSystem::getValidatedInput(1, 2); // Get validated input (options 1-2)

    // ======== DEATH RECOVERY OPTIONS ========
    switch (choice)
    {
    case 1:
    {
        // ======== CHECKPOINT RESTORATION OPTION ========
        // Attempt to restore the player's most recent save point

        // ======== SAVE DATA RETRIEVAL ========
        GameData mostRecentSave;                                         // Container for the most recent save data
        bool foundSave = SaveManager::getMostRecentSave(mostRecentSave); // Attempt to find recent save

        if (foundSave)
        {
            // ======== RESET GAME STATE BEFORE RESTORATION ========
            // Clear all global variables to ensure clean state before loading checkpoint data
            SaveManager::resetGameState();

            // ======== COMPLETE GAME STATE RESTORATION ========
            // Restore all aspects of the player's saved state

            // ======== PLAYER CHARACTER RESTORATION ========
            playerSelected = mostRecentSave.playerData;  // Restore player stats, health, etc.
            selectedName = mostRecentSave.characterName; // Restore player name

            // Restore player's inventory and gold from saved data
            mostRecentSave.restoreInventoryToGlobal(::playerInventory);
            ::playerGold = mostRecentSave.playerGold;

            // ======== WORLD STATE RESTORATION ========
            SaveManager::updatePlayerPosition(mostRecentSave.currentMapX, mostRecentSave.currentMapY); // Restore map position
            SaveManager::setCurrentDifficulty(mostRecentSave.difficultyConfig);                        // Restore difficulty settings
            applyDifficultyEnemies(mostRecentSave.difficultyConfig);                                   // Apply difficulty scaling to enemies

            // Restore the enemy defeat counters to maintain progression accuracy
            playerSelected.setEnemiesKilled(mostRecentSave.currentMapEnemiesKilled); // Current map progress
            playerSelected.setEnemiesKilledPerMap(mostRecentSave.enemiesPerMap);     // Per-map progress tracking

            // ======== RESTORATION FEEDBACK AND GAME RESUME ========
            showSuccessMessage("Returning to your last checkpoint..."); // Inform user of successful restoration
            playGame();                                                 // Resume gameplay from checkpoint
        }
        else
        {
            // ======== NO SAVE FOUND FALLBACK ========
            // If no recent save exists, return to main menu for new game or manual load
            runMainMenu();
        }
    }
    break;

    case 2:
        // ======== RETURN TO MAIN MENU OPTION ========
        // Allow player to return to main menu without loading a save
        // This provides access to new game creation or manual save loading
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

    for (int i = 0; i < title.length(); ++i)
        grid[startRow][titleCol + i] = title[i];
    for (int i = 0; i < subtitle.length(); ++i)
        grid[startRow + 2][subtitleCol + i] = subtitle[i];
    for (int i = 0; i < opt1.length(); ++i)
        grid[startRow + 4][opt1Col + i] = opt1[i];
    for (int i = 0; i < desc1.length(); ++i)
        grid[startRow + 5][desc1Col + i] = desc1[i];
    for (int i = 0; i < opt2.length(); ++i)
        grid[startRow + 7][opt2Col + i] = opt2[i];
    for (int i = 0; i < desc2.length(); ++i)
        grid[startRow + 8][desc2Col + i] = desc2[i];
    for (int i = 0; i < opt3.length(); ++i)
        grid[startRow + 10][opt3Col + i] = opt3[i];
    for (int i = 0; i < desc3.length(); ++i)
        grid[startRow + 11][desc3Col + i] = desc3[i];

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
        for (int i = 0; i < msg.length(); ++i)
            successGrid[12][msgCol + i] = msg[i];

        std::string continueMsg = "Press any key to continue...";
        int continueCol = (COLUMNS - continueMsg.length()) / 2;
        for (int i = 0; i < continueMsg.length(); ++i)
            successGrid[14][continueCol + i] = continueMsg[i];

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
        for (int i = 0; i < msg.length(); ++i)
            successGrid[12][msgCol + i] = msg[i];

        std::string continueMsg = "Press any key to continue...";
        int continueCol = (COLUMNS - continueMsg.length()) / 2;
        for (int i = 0; i < continueMsg.length(); ++i)
            successGrid[14][continueCol + i] = continueMsg[i];

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
        for (int i = 0; i < msg.length(); ++i)
            successGrid[12][msgCol + i] = msg[i];

        std::string continueMsg = "Press any key to continue...";
        int continueCol = (COLUMNS - continueMsg.length()) / 2;
        for (int i = 0; i < continueMsg.length(); ++i)
            successGrid[14][continueCol + i] = continueMsg[i];

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

    std::string title = "SAVED GAME INFORMATION";
    int titleCol = (COLUMNS - title.length()) / 2;
    for (int i = 0; i < title.length(); ++i)
        grid[5][titleCol + i] = title[i];

    std::map<std::string, GameData> &saves = SaveManager::getGameSaves();

    int row = 8;
    std::string saveKey = "Game1"; // Only slot available
    std::string slotInfo;

    if (saves[saveKey].exists)
    {
        slotInfo = "Saved Game: " + saves[saveKey].characterName +
                   " - " + saves[saveKey].creationDate.substr(0, 10);
    }
    else
    {
        slotInfo = "No saved game found";
    }

    int slotCol = (COLUMNS - slotInfo.length()) / 2;
    for (int j = 0; j < slotInfo.length(); ++j)
        grid[row][slotCol + j] = slotInfo[j];

    gameMap.display();
}

void GameController::showSuccessMessage(const std::string &message)
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
    for (int i = 0; i < line1.length(); ++i)
        grid[10][line1Col + i] = line1[i];

    if (!line2.empty())
    {
        int line2Col = (COLUMNS - line2.length()) / 2;
        for (int i = 0; i < line2.length(); ++i)
            grid[12][line2Col + i] = line2[i];
    }

    if (!line3.empty())
    {
        int line3Col = (COLUMNS - line3.length()) / 2;
        for (int i = 0; i < line3.length(); ++i)
            grid[14][line3Col + i] = line3[i];
    }

    gameMap.display();
    _getch();
}

void GameController::showErrorMessage(const std::string &message)
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
    for (int i = 0; i < line1.length(); ++i)
        grid[10][line1Col + i] = line1[i];

    if (!line2.empty())
    {
        int line2Col = (COLUMNS - line2.length()) / 2;
        for (int i = 0; i < line2.length(); ++i)
            grid[12][line2Col + i] = line2[i];
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
