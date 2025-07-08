#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

#include "SaveSystem.h"

// SaveManager now acts as a simple interface to SaveSystem functions
// No pointers, no vectors, no duplicate code
class SaveManager
{
public:
    // Load existing save data into map container
    static void loadExistingSaves()
    {
        loadAllExistingSaves();
    }
    
    // Save comprehensive game data
    static void saveGameData(const std::string& saveSlot, const GameData& data)
    {
        saveCompleteGameData(saveSlot, data);
    }
    
    // Save current game progress during gameplay
    static void saveCurrentProgress(const std::string& location)
    {
        ::saveCurrentProgress(location);
    }
    
    // Save progress after enemy defeat
    static void saveProgressAfterCombat(const std::string& location)
    {
        ::saveCurrentProgress(location);
    }
    
    // Create comprehensive timestamp
    static std::string getCurrentDateTime()
    {
        return ::getCurrentDateTime();
    }
    
    // Check how many saves exist
    static int countExistingSaves()
    {
        return ::countExistingSaves();
    }
    
    // Update enemy defeat counter
    static void incrementEnemiesDefeated()
    {
        ::incrementEnemiesDefeated();
    }
    
    // Update player position
    static void updatePlayerPosition(int x, int y)
    {
        ::updatePlayerPosition(x, y);
    }
    
    // Get current location string
    static std::string getCurrentLocationString()
    {
        return ::getCurrentLocationString();
    }
    
    // Get current enemy count
    static int getCurrentEnemyCount()
    {
        return ::getCurrentEnemyCount();
    }
    
    // Helper methods for multiple save slots
    static std::string getSaveFileName(int slotNumber)
    {
        return ::getSaveFileName(slotNumber);
    }
    
    static std::string getSaveInfoFileName(int slotNumber)
    {
        return ::getSaveInfoFileName(slotNumber);
    }
    
    static int findEmptySlot()
    {
        return ::findEmptySlot();
    }
    
    // Get/Set current difficulty
    static void setCurrentDifficulty(const configurationDifficulty& difficulty)
    {
        ::setCurrentDifficulty(difficulty);
    }
    
    static configurationDifficulty getCurrentDifficulty()
    {
        return ::getCurrentDifficulty();
    }
    
    // Get game saves map
    static std::map<std::string, GameData>& getGameSaves()
    {
        return getGameSavesMap();
    }
    
    // Load a specific save (no pointers)
    static bool loadSave(int slotNumber)
    {
        return loadSpecificSave(slotNumber);
    }
    
    // Get most recent save (no pointers, returns by copy)
    static bool getMostRecentSave(GameData& outSave)
    {
        return ::getMostRecentSave(outSave);
    }
    
    // Reset enemy counter when changing maps
    static void resetMapEnemyCounter()
    {
        playerSelected.resetEnemyCount();
    }
    
    // Get current map enemy counter
    static int getCurrentMapEnemyCount()
    {
        return playerSelected.getCurrentEnemiesKilled();
    }
    
    // Reset all global game state for new game
    static void resetGameState()
    {
        ::resetGlobalGameState();
    }
    
    // Get current player position
    static void getCurrentPlayerPosition(int& x, int& y)
    {
        ::getCurrentPlayerPosition(x, y);
    }
};

#endif // SAVE_MANAGER_H
