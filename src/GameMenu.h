/*
 * ===============================================================================
 * GAMEMENU.H - Enhanced Game Menu System and Interface Coordinator
 * ===============================================================================
 * 
 * DESCRIPTION:
 * This file contains the GameMenu class which serves as a high-level interface
 * coordinator for the game "Brothers of the Dawn: Fragments of the Alba".
 * It acts as a facade pattern implementation, providing simplified access to
 * complex subsystems including menu navigation, combat integration, and save management.
 * 
 * KEY RESPONSIBILITIES:
 * - Simplified interface for title screen and menu operations
 * - Combat system integration and progress tracking
 * - Save/load operations coordination
 * - Player position and enemy defeat counter management
 * - Map transition and enemy counter reset functionality
 * 
 * ARCHITECTURAL NOTES:
 * - Implements Facade Pattern: Simplifies complex subsystem interactions
 * - Static utility class: No instance creation required
 * - Bridge between combat system and save management
 * - Provides consistent API for game state operations
 * 
 * DESIGN PATTERNS:
 * - Facade Pattern: Hides complexity of underlying systems
 * - Adapter Pattern: Adapts different subsystem interfaces
 * - Delegation Pattern: Forwards calls to appropriate subsystems
 * ===============================================================================
 */

#ifndef GAME_MENU_H
#define GAME_MENU_H

// ===============================================================================
// INCLUDES AND DEPENDENCIES
// ===============================================================================
#include "TitleScreen.h"     // Title screen display and ASCII art management
#include "MenuSystem.h"      // Menu navigation and user input handling
#include "SaveManager.h"     // Save/load operations and game state persistence
#include "GameController.h"  // Main game flow control and state management

// ===============================================================================
// ENHANCED GAME MENU FACADE CLASS
// ===============================================================================
// This class provides a simplified, unified interface for all menu-related operations
// in "Brothers of the Dawn: Fragments of the Alba". It acts as a central coordinator
// that manages interactions between different game subsystems while maintaining
// a clean and easy-to-use API for other parts of the game.
class GameMenu
{
public:
    // ======== TITLE AND MENU DISPLAY METHODS ========
    // These methods handle the primary user interface screens and navigation
    
    // Displays the complete title sequence including ASCII art and game introduction
    // This creates the initial player experience and sets the atmospheric tone
    // Coordinates between TitleScreen components for seamless presentation
    static void displayTitleScreen();
    
    // Displays the main menu interface and handles all user navigation choices
    // Acts as the central hub for accessing all game features (new game, load, exit)
    // Delegates to GameController for actual menu logic and flow control
    static void displayMainMenu();
    
    // Displays the death screen interface with recovery and exit options
    // Provides player choice between checkpoint restoration and menu return
    // Manages the player death recovery workflow through GameController
    static void displayDeathScreen();
    
    // ======== COMBAT SYSTEM INTEGRATION METHODS ========
    // These methods provide the interface between combat events and game state management
    // They ensure proper tracking of player progress and combat statistics
    
    // Increments the global enemy defeat counter after successful combat
    // Updates both per-map and total enemy kill statistics
    // Triggers save system updates to maintain progress persistence
    static void incrementEnemiesDefeated();
    
    // Saves complete game progress after combat events at specified locations
    // Updates player position, enemy counts, and triggers automatic save operations
    // Ensures that combat progress is immediately preserved to prevent data loss
    static void saveProgressAfterCombat(const std::string& location);
    
    // Retrieves the current total number of enemies defeated by the player
    // Used for progression tracking, achievements, and game balance calculations
    // Returns the cumulative enemy defeat count across all gameplay sessions
    static int getCurrentEnemyCount();
    
    // Updates the player's current position coordinates in the game world
    // Maintains accurate location tracking for save/load operations and map transitions
    // Coordinates: x (horizontal position), y (vertical position)
    static void updatePlayerPosition(int x, int y);
    
    // ======== MAP MANAGEMENT AND TRANSITION METHODS ========
    // These methods handle map-specific enemy tracking and transitions between areas
    // They maintain per-map statistics and handle area reset functionality
    
    // Resets the enemy counter for the current map to zero
    // Used when transitioning to new areas or when maps need to be refreshed
    // Maintains separate tracking for each individual map area
    static void resetMapEnemyCounter();
    
    // Retrieves the number of enemies defeated on the current map only
    // Used for map-specific progression tracking and area completion detection
    // Differs from total count by tracking only current area progress
    static int getCurrentMapEnemyCount();
};

// ===============================================================================
// METHOD IMPLEMENTATIONS - FACADE PATTERN DELEGATION
// ===============================================================================
// All methods in this class follow the Facade pattern by providing simplified
// interfaces that delegate to more complex underlying systems. This approach
// maintains clean separation of concerns while offering easy-to-use APIs.

// ======== TITLE SCREEN DISPLAY COORDINATION ========
// This method orchestrates the complete title sequence presentation
// It ensures proper timing and order of title elements for optimal user experience
void GameMenu::displayTitleScreen()
{
    // ======== STEP 1: ASCII ART TITLE DISPLAY ========
    // Display the main game title with ASCII art branding
    // This creates the initial visual impact and establishes game identity
    TitleScreen::displayGameTitle();
    
    // ======== STEP 2: ATMOSPHERIC INTRODUCTION ========
    // Show the game's introduction text and story setup
    // This provides context and draws players into the game world
    TitleScreen::displayIntroduction();
}

// ======== MAIN MENU NAVIGATION DELEGATION ========
// This method provides a simplified interface to the main menu system
// It delegates all complex menu logic to the GameController while maintaining clean API
void GameMenu::displayMainMenu()
{
    // ======== DELEGATE TO GAME CONTROLLER ========
    // Transfer control to the main menu controller which handles:
    // - Menu display and formatting
    // - User input validation and processing
    // - Navigation to new game, load game, or exit functions
    // - Error handling and user feedback
    GameController::runMainMenu();
}

// ======== DEATH SCREEN MANAGEMENT DELEGATION ========
// This method provides simplified access to death recovery functionality
// It maintains the facade pattern by hiding complex death handling logic
void GameMenu::displayDeathScreen()
{
    // ======== DELEGATE TO GAME CONTROLLER ========
    // Transfer control to the death screen handler which manages:
    // - Death screen display with thematic messaging
    // - User choice processing (checkpoint restore vs. main menu)
    // - Save game validation and restoration
    // - Error handling for missing save files
    GameController::handleDeathScreen();
}

// ======== COMBAT INTEGRATION - ENEMY DEFEAT TRACKING ========
// This method provides a clean interface for updating enemy defeat statistics
// It ensures proper synchronization between combat events and save data
void GameMenu::incrementEnemiesDefeated()
{
    // ======== DELEGATE TO SAVE MANAGER ========
    // Update enemy defeat counters through the save management system
    // This ensures that combat progress is immediately reflected in:
    // - Per-map enemy defeat counters
    // - Total game-wide enemy defeat statistics
    // - Player progression tracking systems
    SaveManager::incrementEnemiesDefeated();
}

// ======== COMBAT INTEGRATION - PROGRESS PERSISTENCE ========
// This method ensures that combat victories are immediately saved to prevent progress loss
// It coordinates between combat events and the save system for data consistency
void GameMenu::saveProgressAfterCombat(const std::string& location)
{
    // ======== DELEGATE TO SAVE MANAGER ========
    // Trigger automatic save operation after combat with location context
    // This operation includes:
    // - Updated enemy defeat counts
    // - Current player position and status
    // - Timestamp of the save operation
    // - Location-specific progress markers
    SaveManager::saveProgressAfterCombat(location);
}

// ======== COMBAT STATISTICS - GLOBAL ENEMY COUNT RETRIEVAL ========
// This method provides access to the total number of enemies defeated by the player
// Used for progression tracking, achievements, and game balance calculations
int GameMenu::getCurrentEnemyCount()
{
    // ======== DELEGATE TO SAVE MANAGER ========
    // Retrieve the cumulative enemy defeat count from the save system
    // This count represents total enemies defeated across all gameplay sessions
    // Used for: progression gates, difficulty scaling, achievement tracking
    return SaveManager::getCurrentEnemyCount();
}

// ======== POSITION MANAGEMENT - PLAYER LOCATION TRACKING ========
// This method maintains accurate player position data for save/load operations
// It ensures that player location is always current for proper game state management
void GameMenu::updatePlayerPosition(int x, int y)
{
    // ======== DELEGATE TO SAVE MANAGER ========
    // Update player coordinates in the save system for:
    // - Accurate position restoration on game load
    // - Map transition tracking and validation
    // - Location-based save game organization
    // Parameters: x (horizontal position), y (vertical position)
    SaveManager::updatePlayerPosition(x, y);
}

// ======== MAP MANAGEMENT - AREA TRANSITION RESET ========
// This method resets map-specific enemy counters when transitioning between areas
// It maintains separate progress tracking for each individual map region
void GameMenu::resetMapEnemyCounter()
{
    // ======== DELEGATE TO SAVE MANAGER ========
    // Reset the current map's enemy defeat counter to zero
    // This operation is used for:
    // - Map transitions and area changes
    // - New area initialization
    // - Map refresh and reset operations
    // Note: This only affects current map, not global enemy count
    SaveManager::resetMapEnemyCounter();
}

// ======== MAP STATISTICS - CURRENT AREA PROGRESS RETRIEVAL ========
// This method provides access to map-specific enemy defeat progress
// Used for area completion tracking and map-specific achievements
int GameMenu::getCurrentMapEnemyCount()
{
    // ======== DELEGATE TO SAVE MANAGER ========
    // Retrieve enemy defeat count for the current map only
    // This differs from global count by tracking only current area progress
    // Used for: map completion detection, area-specific rewards, progress gates
    return SaveManager::getCurrentMapEnemyCount();
}

#endif // GAME_MENU_H
