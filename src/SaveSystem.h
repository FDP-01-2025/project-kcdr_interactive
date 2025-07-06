/*
 * ===============================================================================
 * SAVESYSTEM.H - Comprehensive Game Save/Load Management System
 * ===============================================================================
 * 
 * DESCRIPTION:
 * This file implements a complete save/load system for the RPG game, managing
 * player data, difficulty settings, map progress, and enemy tracking across
 * multiple save slots. It provides both file-based persistence and memory
 * management for game state.
 * 
 * KEY RESPONSIBILITIES:
 * - Multi-slot save game management (up to 5 slots)
 * - Complete game state persistence (player, difficulty, progress)
 * - File I/O operations for save data and metadata
 * - Real-time game state tracking during gameplay
 * - Save slot validation and management
 * - Map-specific progress tracking
 * 
 * ARCHITECTURAL NOTES:
 * - Uses both binary (.dat) and text (.txt) files for data storage
 * - Implements comprehensive GameData structure for all game information
 * - Provides automatic save slot management and selection
 * - Integrates seamlessly with Player and difficulty systems
 * 
 * DESIGN PATTERNS:
 * - Singleton pattern: Global state management through static variables
 * - Data Transfer Object: GameData struct encapsulates all save information
 * - Factory pattern: File naming and creation through helper functions
 * ===============================================================================
 */

#ifndef SAVE_H
#define SAVE_H

// ===============================================================================
// SYSTEM DEPENDENCIES AND INCLUDES
// ===============================================================================
#include "Player.h"                    // Player class for character data management
#include "configurationDifficulty.h"   // Difficulty settings and enemy scaling
#include <string>                      // String manipulation and storage
#include <fstream>                     // File input/output operations
#include <iostream>                    // Console output for debugging
#include <map>                         // STL map for save slot management
#include <ctime>                       // Time functions for save timestamps

// ===============================================================================
// FORWARD DECLARATIONS - AVOIDING CIRCULAR DEPENDENCIES
// ===============================================================================
// These declarations prevent circular dependency issues while allowing access
// to essential game components defined in other modules
extern Player playerSelected;          // Global reference to current active player
extern std::string selectedName;       // Currently selected character name
int getCurrentMapId();                 // Function to get current map identifier
void setCurrentMapId(int mapId);       // Function to set current map identifier

// ===============================================================================
// GAMEDATA STRUCTURE - COMPREHENSIVE SAVE DATA CONTAINER
// ===============================================================================
// This structure encapsulates all necessary information for a complete game save
// It serves as a Data Transfer Object (DTO) that contains player state, progress,
// difficulty settings, and metadata for persistence and restoration
struct GameData
{
    // ======== METADATA AND IDENTIFICATION ========
    std::string characterName;         // Player's chosen character name for identification
    std::string creationDate;          // Timestamp when save was created (for organization)
    std::string lastLocation;          // Human-readable location description for UI display
    
    // ======== CORE GAME STATE ========
    Player playerData;                 // Complete player object with all stats and progress
    configurationDifficulty difficultyConfig; // Game difficulty settings affecting enemy stats
    
    // ======== PROGRESS TRACKING ========
    int enemiesDefeated;               // Total number of enemies defeated across all gameplay
    int currentMapX;                   // Player's current X coordinate on the map
    int currentMapY;                   // Player's current Y coordinate on the map
    int currentMapEnemiesKilled;       // Number of enemies killed in the current map only
    int currentMapId;                  // Unique identifier for the current map/area
    std::map<int, int> enemiesPerMap;  // Map ID -> Enemy count mapping for each visited area
    bool exists;                       // Flag indicating whether this save slot contains valid data

    // ======== DEFAULT CONSTRUCTOR ========
    // Creates an empty save slot with default values
    // Used for initializing empty save slots and providing safe fallback state
    GameData() : playerData(0, 0, 0, 0), difficultyConfig(0, 0), 
                 enemiesDefeated(0), currentMapX(15), currentMapY(45), 
                 currentMapEnemiesKilled(0), currentMapId(0), exists(false) {}
    
    // ======== PARAMETERIZED CONSTRUCTOR ========
    // Creates a complete save data object with all necessary information
    // Used when creating new saves or updating existing ones with current game state
    GameData(const std::string& name, const std::string& date, const std::string& location,
             const Player& player, const configurationDifficulty& config, 
             int defeated, int mapX, int mapY, int mapEnemies) 
        : characterName(name), creationDate(date), lastLocation(location),
          playerData(player), difficultyConfig(config), enemiesDefeated(defeated),
          currentMapX(mapX), currentMapY(mapY), currentMapEnemiesKilled(mapEnemies), 
          currentMapId(0), exists(true) {
              // Copy the player's per-map enemy tracking data for complete state preservation
              enemiesPerMap = player.getEnemiesKilledPerMap();
          }
};

// ===============================================================================
// GLOBAL SAVE SYSTEM VARIABLES AND CONSTANTS
// ===============================================================================
// These static variables provide centralized management of the save system state
// and configuration. They implement a singleton-like pattern for global access.

// ======== SAVE DATA STORAGE ========
// Central repository for all save game data using string-based slot identification
// Maps save slot names ("Game1", "Game2", etc.) to their corresponding GameData
static std::map<std::string, GameData> gameSaves;

// ======== FILE NAMING CONSTANTS ========
// Standardized prefixes for consistent file naming across the save system
static const std::string SAVE_FILE_PREFIX = "savegame";    // Prefix for binary data files (.dat)
static const std::string SAVE_INFO_PREFIX = "saveinfo";    // Prefix for metadata text files (.txt)
static const int MAX_SAVE_SLOTS = 5;                       // Maximum number of save slots supported

// ======== CURRENT GAME STATE TRACKING ========
// Real-time tracking variables for the active game session
// These maintain current state between save operations
static int currentPlayerX = 15;                            // Player's current X coordinate (default spawn)
static int currentPlayerY = 45;                            // Player's current Y coordinate (default spawn)
static int totalEnemiesDefeated = 0;                       // Running total of all enemies defeated
static configurationDifficulty currentDifficulty(0, 0);   // Current difficulty settings (neutral default)

// ===============================================================================
// UTILITY FUNCTIONS FOR FILE MANAGEMENT
// ===============================================================================
// These helper functions provide consistent file naming and path generation
// following the established naming conventions for save system files

// ======== SAVE FILE NAME GENERATION ========
// Generates standardized binary save file names based on slot number
// Returns: "savegame[slotNumber].dat" (e.g., "savegame1.dat")
// Used for storing complete player and game state data
std::string getSaveFileName(int slotNumber)
{
    return SAVE_FILE_PREFIX + std::to_string(slotNumber) + ".dat";
}

// ======== METADATA FILE NAME GENERATION ========
// Generates standardized metadata file names based on slot number
// Returns: "saveinfo[slotNumber].txt" (e.g., "saveinfo1.txt")
// Used for storing human-readable save information and metadata
std::string getSaveInfoFileName(int slotNumber)
{
    return SAVE_INFO_PREFIX + std::to_string(slotNumber) + ".txt";
}

// ======== TIMESTAMP GENERATION ========
// Generates current date and time as a formatted string for save metadata
// Returns: Current system time as a string with newline characters removed
// Used for timestamping save files and providing creation date information
std::string getCurrentDateTime()
{
    time_t now = time(0);                     // Get current system time
    std::string timeStr = ctime(&now);        // Convert to string format
    
    // Remove trailing newline character that ctime() adds for cleaner output
    if (!timeStr.empty() && timeStr.back() == '\n')
    {
        timeStr.pop_back();
    }
    return timeStr;
}

// ===============================================================================
// CORE SAVE/LOAD FILE OPERATIONS
// ===============================================================================
// These functions handle the fundamental file I/O operations for game state
// persistence, managing both player data and difficulty configuration

// ======== SAVE GAME STATE TO FILE ========
// Writes complete game state (player stats + difficulty settings) to a binary file
// This is the low-level save operation that handles the actual file writing
// Parameters:
//   - player: Player object containing all character stats and progress
//   - config: Difficulty configuration affecting enemy stats
//   - filename: Target file path for the save data
void saveGameState(const Player &player, const configurationDifficulty &config, const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    { 
        // Write player stats in space-separated format for easy parsing
        file << player.getHealth() << ' ' << player.getAttack() << ' ' 
             << player.getDefense() << ' ' << player.getSpecialAttack() << '\n';
        
        // Write difficulty settings on second line
        file << config.enemyHealth << ' ' << config.enemyAttack << std::endl;
        file.close();
    }
}

// ======== LOAD GAME STATE FROM FILE ========
// Reads complete game state (player stats + difficulty settings) from a binary file
// This is the low-level load operation that reconstructs game objects from file data
// Parameters:
//   - player: Reference to Player object to be populated with loaded data
//   - config: Reference to difficulty configuration to be populated
//   - filename: Source file path containing the save data
void loadGameState(Player &player, configurationDifficulty &config, const std::string &filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        // Temporary variables for reading player stats
        int health, attack, defense, specialAttack;
        int enemyHealth, enemyAttack;

        // Read player stats from first line
        file >> health >> attack >> defense >> specialAttack;
        player = Player(health, attack, defense, specialAttack);

        // Read difficulty settings from second line
        file >> enemyHealth >> enemyAttack;
        config = configurationDifficulty(enemyHealth, enemyAttack);

        file.close();
    }
}

// ===============================================================================
// SAVE SYSTEM INITIALIZATION AND MANAGEMENT
// ===============================================================================
// These functions handle the initialization and high-level management of the
// save system, including loading existing saves and comprehensive data management

// ======== LOAD ALL EXISTING SAVES ========
// Scans all save slots and loads existing save data into memory
// This function initializes the save system by checking all possible save slots
// and loading any existing save files, populating the global gameSaves map
void loadAllExistingSaves()
{
    // Iterate through all possible save slots (1 to MAX_SAVE_SLOTS)
    for (int i = 1; i <= MAX_SAVE_SLOTS; i++)
    {
        std::string saveKey = "Game" + std::to_string(i);    // Generate save slot identifier
        std::string saveFile = getSaveFileName(i);           // Get binary save file path
        std::string infoFile = getSaveInfoFileName(i);       // Get metadata file path
        
        // Check if save file exists by attempting to open it
        std::ifstream file(saveFile);
        if (file.good())  // Save file exists, load the data
        {
            file.close();
            
            // Create temporary objects to load game state
            Player tempPlayer(0, 0, 0, 0);
            configurationDifficulty tempConfig;
            loadGameState(tempPlayer, tempConfig, saveFile);
            
            // Initialize default metadata values in case info file is missing/corrupted
            std::string characterName = "Unknown";
            std::string date = "Unknown Date";
            std::string location = "Unknown Location";
            int enemies = 0;
            int mapX = 15, mapY = 45;  // Default spawn coordinates
            
            // Attempt to load metadata from info file
            std::ifstream infoFileStream(infoFile);
            if (infoFileStream.good())
            {
                // Read metadata in order: name, date, location, then numeric data
                std::getline(infoFileStream, characterName);
                std::getline(infoFileStream, date);
                std::getline(infoFileStream, location);
                int mapEnemies = 0;
                infoFileStream >> enemies >> mapX >> mapY >> mapEnemies;
                infoFileStream.close();
                
                // Create complete GameData object with loaded information
                gameSaves[saveKey] = GameData(characterName, date, location, tempPlayer, tempConfig, enemies, mapX, mapY, mapEnemies);
            }
            else
            {
                // Info file missing, create GameData with default metadata
                gameSaves[saveKey] = GameData(characterName, date, location, tempPlayer, tempConfig, enemies, mapX, mapY, 0);
            }
        }
        else  // Save file doesn't exist, create empty slot
        {
            gameSaves[saveKey] = GameData();  // Empty save slot
        }
    }
}

// ======== SAVE COMPREHENSIVE GAME DATA ========
// Saves complete game data including both binary state and metadata to files
// This high-level save function handles both the game state file and metadata file
// Parameters:
//   - saveSlot: Save slot identifier (e.g., "Game1", "Game2")
//   - data: Complete GameData object containing all save information
void saveCompleteGameData(const std::string& saveSlot, const GameData& data)
{
    // Extract slot number from save slot string (e.g., "Game1" -> 1)
    int slotNumber = std::stoi(saveSlot.substr(4));
    std::string saveFile = getSaveFileName(slotNumber);     // Generate binary file path
    std::string infoFile = getSaveInfoFileName(slotNumber); // Generate metadata file path

    // Save binary game state (player stats + difficulty)
    saveGameState(data.playerData, data.difficultyConfig, saveFile);
    
    // Save metadata to text file for human readability and quick access
    std::ofstream info(infoFile);
    if (info.is_open())
    {
        info << data.characterName << "\n";     // Character name for identification
        info << data.creationDate << "\n";      // Save creation timestamp
        info << data.lastLocation << "\n";      // Last known location description
        // Save progress data: total enemies, coordinates, current map enemies
        info << data.enemiesDefeated << " " << data.currentMapX << " " 
             << data.currentMapY << " " << data.currentMapEnemiesKilled << "\n";
        info.close();
    }
    
    // Update in-memory save data for immediate access
    gameSaves[saveSlot] = data;
}

// ===============================================================================
// SAVE SLOT LOADING AND MANAGEMENT FUNCTIONS
// ===============================================================================
// These functions handle specific save slot operations including loading,
// finding available slots, and managing save slot information

// ======== LOAD SPECIFIC SAVE BY SLOT NUMBER ========
// Loads a specific save slot and applies its data to the current game state
// This function validates the save exists and then restores all game state
// Returns: true if save was loaded successfully, false if slot is empty or invalid
// Parameters:
//   - slotNumber: The save slot number to load (1-5)
bool loadSpecificSave(int slotNumber)
{
    std::string saveKey = "Game" + std::to_string(slotNumber);
    
    // Validate that the requested save slot contains data
    if (!gameSaves[saveKey].exists)
    {
        return false;  // Save slot is empty or invalid
    }

    // Create local copy of save data (avoiding pointer issues)
    GameData loadedGame = gameSaves[saveKey];
    
    // ======== RESTORE PLAYER STATE ========
    playerSelected = loadedGame.playerData;  // Restore complete player object
    
    // ======== RESTORE PROGRESSION DATA ========
    // Restore per-map enemy tracking data for accurate progression
    playerSelected.setEnemiesKilledPerMap(loadedGame.enemiesPerMap);
    // Restore current map enemy count for accurate local progress
    playerSelected.setEnemiesKilled(loadedGame.currentMapEnemiesKilled);
    
    // ======== RESTORE GAME METADATA ========
    selectedName = loadedGame.characterName;         // Character name
    currentPlayerX = loadedGame.currentMapX;         // Player X coordinate
    currentPlayerY = loadedGame.currentMapY;         // Player Y coordinate
    totalEnemiesDefeated = loadedGame.enemiesDefeated; // Total kill count
    currentDifficulty = loadedGame.difficultyConfig;   // Difficulty settings
    
    // ======== RESTORE MAP STATE ========
    // Set the current map to match the saved state
    setCurrentMapId(loadedGame.currentMapId);
    
    return true;  // Save loaded successfully
}

// ======== GET MOST RECENT SAVE ========
// Finds and returns the most recently used save slot
// Searches from highest slot number to lowest to find the last used save
// Returns: true if a save was found, false if no saves exist
// Parameters:
//   - outSave: Reference to GameData object that will receive the found save data
bool getMostRecentSave(GameData& outSave)
{
    // Search from highest slot number to lowest (reverse order)
    // This finds the most recently used slot in most cases
    for (int i = MAX_SAVE_SLOTS; i >= 1; i--)
    {
        std::string saveKey = "Game" + std::to_string(i);
        if (gameSaves[saveKey].exists)
        {
            outSave = gameSaves[saveKey];   // Copy save data to output parameter
            return true;                    // Found a valid save
        }
    }
    return false;  // No existing saves found
}

// ======== FIND EMPTY SAVE SLOT ========
// Locates the first available empty save slot for new save creation
// Searches from slot 1 to MAX_SAVE_SLOTS to find an unused slot
// Returns: Slot number (1-5) if available, MAX_SAVE_SLOTS+1 if all slots full
int findEmptySlot()
{
    // Search from first slot to last for an empty slot
    for (int i = 1; i <= MAX_SAVE_SLOTS; i++)
    {
        std::string saveKey = "Game" + std::to_string(i);
        if (!gameSaves[saveKey].exists)
        {
            return i;  // Found empty slot
        }
    }
    // All slots are occupied, return value greater than max to indicate this
    return MAX_SAVE_SLOTS + 1;
}

// ======== COUNT EXISTING SAVES ========
// Counts the total number of occupied save slots
// Useful for UI display and save management statistics
// Returns: Number of save slots that contain valid save data (0-5)
int countExistingSaves()
{
    int count = 0;
    
    // Iterate through all possible save slots and count existing ones
    for (int i = 1; i <= MAX_SAVE_SLOTS; i++)
    {
        std::string saveKey = "Game" + std::to_string(i);
        if (gameSaves[saveKey].exists) 
        {
            count++;
        }
    }
    return count;
}

// ===============================================================================
// REAL-TIME GAME STATE MANAGEMENT FUNCTIONS
// ===============================================================================
// These functions provide real-time tracking and updating of game state during
// active gameplay, ensuring accurate progress tracking between save operations

// ======== INCREMENT TOTAL ENEMY DEFEAT COUNT ========
// Increases the global counter for total enemies defeated across all gameplay
// Called whenever any enemy is defeated in combat to maintain accurate statistics
// Used for achievements, difficulty scaling, and save game metadata
void incrementEnemiesDefeated()
{
    totalEnemiesDefeated++;
}

// ======== UPDATE PLAYER MAP COORDINATES ========
// Updates the player's current position coordinates for save game tracking
// Called whenever the player moves to a new position on the map
// Parameters:
//   - x: New X coordinate on the map grid
//   - y: New Y coordinate on the map grid
void updatePlayerPosition(int x, int y)
{
    currentPlayerX = x;
    currentPlayerY = y;
}

// ======== SET CURRENT DIFFICULTY CONFIGURATION ========
// Updates the global difficulty settings that affect enemy stats and behavior
// Called when difficulty is changed through game menus or progression events
// Parameters:
//   - difficulty: New difficulty configuration object containing enemy modifiers
void setCurrentDifficulty(const configurationDifficulty& difficulty)
{
    currentDifficulty = difficulty;
}

// ======== GET CURRENT DIFFICULTY CONFIGURATION ========
// Retrieves the currently active difficulty settings for use by other systems
// Used by combat system and enemy spawning to apply appropriate stat modifiers
// Returns: Copy of current difficulty configuration object
configurationDifficulty getCurrentDifficulty()
{
    return currentDifficulty;
}

// ======== GET TOTAL ENEMY DEFEAT COUNT ========
// Returns the total number of enemies defeated across all gameplay sessions
// Used for statistics display, achievements, and progression tracking
// Returns: Integer count of total enemies defeated
int getCurrentEnemyCount()
{
    return totalEnemiesDefeated;
}

// ======== GENERATE LOCATION STRING FROM COORDINATES ========
// Converts player coordinates into human-readable location descriptions
// Used for save game metadata and UI location display
// Returns: String describing the current map area based on coordinates
// Location mapping based on coordinate ranges:
//   - Western Woods: X < 10
//   - Eastern Plains: X > 20  
//   - Northern Mountains: Y < 30
//   - Southern Desert: Y > 60
//   - Central Village: Default/middle area
std::string getCurrentLocationString()
{
    if (currentPlayerX < 10) return "Western Woods";
    else if (currentPlayerX > 20) return "Eastern Plains";
    else if (currentPlayerY < 30) return "Northern Mountains";
    else if (currentPlayerY > 60) return "Southern Desert";
    else return "Central Village";
}

// ===============================================================================
// SAVE SYSTEM ACCESS AND UTILITY FUNCTIONS
// ===============================================================================

// ======== GET SAVE DATA MAP REFERENCE ========
// Provides direct access to the global save games map for advanced operations
// Used by UI systems for displaying save slot information and management
// Returns: Reference to the global gameSaves map containing all save data
// WARNING: Direct modification of this map can corrupt save system state
std::map<std::string, GameData>& getGameSavesMap()
{
    return gameSaves;
}

// ======== SAVE CURRENT PROGRESS AUTOMATICALLY ========
// Performs an automatic save of current game state to the appropriate save slot
// This function finds the current character's save slot and updates it with
// the most recent game state, including position, progress, and statistics
// Parameters:
//   - location: Human-readable description of current location for metadata
void saveCurrentProgress(const std::string& location)
{
    // ======== FIND CURRENT CHARACTER'S SAVE SLOT ========
    // Search through all save slots to find the one belonging to current character
    std::string currentSaveSlot = "Game1";  // Default to first slot if not found
    for (int i = 1; i <= MAX_SAVE_SLOTS; i++)
    {
        std::string saveKey = "Game" + std::to_string(i);
        // Match save slot by character name to ensure correct slot is updated
        if (gameSaves[saveKey].exists && gameSaves[saveKey].characterName == selectedName)
        {
            currentSaveSlot = saveKey;
            break;  // Found the correct save slot for this character
        }
    }
    
    // ======== CREATE UPDATED SAVE DATA ========
    // Construct complete GameData object with current game state
    GameData updatedData(selectedName, getCurrentDateTime(), location,
                         playerSelected, currentDifficulty, 
                         totalEnemiesDefeated, currentPlayerX, currentPlayerY, 
                         playerSelected.getCurrentEnemiesKilled());
    
    // ======== INCLUDE MAP-SPECIFIC PROGRESS DATA ========
    // Ensure map progression and enemy tracking data is preserved
    updatedData.currentMapId = getCurrentMapId();                          // Current map identifier
    updatedData.enemiesPerMap = playerSelected.getEnemiesKilledPerMap();   // Per-map enemy tracking
    
    // ======== PERFORM THE SAVE OPERATION ========
    // Write updated data to both binary and metadata files
    saveCompleteGameData(currentSaveSlot, updatedData);
}

#endif