#ifndef SAVE_H
#define SAVE_H
#include "Player.h"
#include "configurationDifficulty.h"
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <ctime>

// Forward declarations (avoid circular dependency)
extern Player playerSelected;
extern std::string selectedName;
int getCurrentMapId();
void setCurrentMapId(int mapId);

// Extended structure to hold comprehensive game data
struct GameData
{
    std::string characterName;
    std::string creationDate;
    std::string lastLocation;
    Player playerData;
    configurationDifficulty difficultyConfig;
    int enemiesDefeated;
    int currentMapX;
    int currentMapY;
    int currentMapEnemiesKilled; // Contador de enemigos en el mapa actual
    int currentMapId; // ID del mapa actual
    std::map<int, int> enemiesPerMap; // Contadores por mapa
    bool exists;

    // Default constructor
    GameData() : playerData(0, 0, 0, 0), difficultyConfig(0, 0), 
                 enemiesDefeated(0), currentMapX(15), currentMapY(45), 
                 currentMapEnemiesKilled(0), currentMapId(0), exists(false) {}
    
    // Parameterized constructor
    GameData(const std::string& name, const std::string& date, const std::string& location,
             const Player& player, const configurationDifficulty& config, 
             int defeated, int mapX, int mapY, int mapEnemies) 
        : characterName(name), creationDate(date), lastLocation(location),
          playerData(player), difficultyConfig(config), enemiesDefeated(defeated),
          currentMapX(mapX), currentMapY(mapY), currentMapEnemiesKilled(mapEnemies), 
          currentMapId(0), exists(true) {
              enemiesPerMap = player.getEnemiesKilledPerMap();
          }
};

// Global save data storage (no pointers, no vectors)
static std::map<std::string, GameData> gameSaves;
static const std::string SAVE_FILE_PREFIX = "savegame";
static const std::string SAVE_INFO_PREFIX = "saveinfo";
static const int MAX_SAVE_SLOTS = 5;
static int currentPlayerX = 15;
static int currentPlayerY = 45;
static int totalEnemiesDefeated = 0;
static configurationDifficulty currentDifficulty(0, 0);

// Helper functions for file names
std::string getSaveFileName(int slotNumber)
{
    return SAVE_FILE_PREFIX + std::to_string(slotNumber) + ".dat";
}

std::string getSaveInfoFileName(int slotNumber)
{
    return SAVE_INFO_PREFIX + std::to_string(slotNumber) + ".txt";
}

// Get current date and time
std::string getCurrentDateTime()
{
    time_t now = time(0);
    char* timeStr = ctime(&now);
    std::string result(timeStr);
    if (!result.empty() && result.back() == '\n')
    {
        result.pop_back();
    }
    return result;
}

// Saves the complete game state (player + difficulty) to a file
void saveGameState(const Player &player, const configurationDifficulty &config, const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    { 
        file << player.getHealth() << ' ' << player.getAttack() << ' ' << player.getDefense() << ' ' << player.getSpecialAttack() << '\n';
        file << config.enemyHealth << ' ' << config.enemyAttack << std::endl;
        file.close();
    }
}

// Loads the complete game state (player + difficulty) from a file
void loadGameState(Player &player, configurationDifficulty &config, const std::string &filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        int health, attack, defense, specialAttack;
        int enemyHealth, enemyAttack;

        file >> health >> attack >> defense >> specialAttack;
        player = Player(health, attack, defense, specialAttack);

        file >> enemyHealth >> enemyAttack;
        config = configurationDifficulty(enemyHealth, enemyAttack);

        file.close();
    }
}

// Load all existing saves into the map
void loadAllExistingSaves()
{
    for (int i = 1; i <= MAX_SAVE_SLOTS; i++)
    {
        std::string saveKey = "Game" + std::to_string(i);
        std::string saveFile = getSaveFileName(i);
        std::string infoFile = getSaveInfoFileName(i);
        
        std::ifstream file(saveFile);
        if (file.good())
        {
            file.close();
            Player tempPlayer(0, 0, 0, 0);
            configurationDifficulty tempConfig;
            loadGameState(tempPlayer, tempConfig, saveFile);
            
            std::string characterName = "Unknown";
            std::string date = "Unknown Date";
            std::string location = "Unknown Location";
            int enemies = 0;
            int mapX = 15, mapY = 45;
            
            std::ifstream infoFileStream(infoFile);
            if (infoFileStream.good())
            {
                std::getline(infoFileStream, characterName);
                std::getline(infoFileStream, date);
                std::getline(infoFileStream, location);
                int mapEnemies = 0;
                infoFileStream >> enemies >> mapX >> mapY >> mapEnemies;
                infoFileStream.close();
                
                gameSaves[saveKey] = GameData(characterName, date, location, tempPlayer, tempConfig, enemies, mapX, mapY, mapEnemies);
            }
            else
            {
                gameSaves[saveKey] = GameData(characterName, date, location, tempPlayer, tempConfig, enemies, mapX, mapY, 0);
            }
        }
        else
        {
            gameSaves[saveKey] = GameData();
        }
    }
}

// Save comprehensive game data to slot
void saveCompleteGameData(const std::string& saveSlot, const GameData& data)
{
    int slotNumber = std::stoi(saveSlot.substr(4));
    std::string saveFile = getSaveFileName(slotNumber);
    std::string infoFile = getSaveInfoFileName(slotNumber);

    saveGameState(data.playerData, data.difficultyConfig, saveFile);
    
    std::ofstream info(infoFile);
    if (info.is_open())
    {
        info << data.characterName << "\n";
        info << data.creationDate << "\n";
        info << data.lastLocation << "\n";
        info << data.enemiesDefeated << " " << data.currentMapX << " " << data.currentMapY << " " << data.currentMapEnemiesKilled << "\n";
        info.close();
    }
    
    gameSaves[saveSlot] = data;
}

// Load a specific save by slot number (no pointers, returns bool for success)
bool loadSpecificSave(int slotNumber)
{
    std::string saveKey = "Game" + std::to_string(slotNumber);
    
    if (!gameSaves[saveKey].exists)
    {
        return false;
    }

    GameData loadedGame = gameSaves[saveKey]; // Copy, no pointer
    
    playerSelected = loadedGame.playerData;
    // Restaurar los contadores por mapa
    playerSelected.setEnemiesKilledPerMap(loadedGame.enemiesPerMap);
    // Restaurar el contador del mapa actual
    playerSelected.setEnemiesKilled(loadedGame.currentMapEnemiesKilled);
    selectedName = loadedGame.characterName;
    currentPlayerX = loadedGame.currentMapX;
    currentPlayerY = loadedGame.currentMapY;
    totalEnemiesDefeated = loadedGame.enemiesDefeated;
    currentDifficulty = loadedGame.difficultyConfig;
    
    // Restaurar el mapa actual
    setCurrentMapId(loadedGame.currentMapId);
    
    return true;
}

// Get most recent save (no pointers, returns by reference)
bool getMostRecentSave(GameData& outSave)
{
    for (int i = MAX_SAVE_SLOTS; i >= 1; i--)
    {
        std::string saveKey = "Game" + std::to_string(i);
        if (gameSaves[saveKey].exists)
        {
            outSave = gameSaves[saveKey]; // Copy, no pointer
            return true;
        }
    }
    return false;
}

// Find empty slot
int findEmptySlot()
{
    for (int i = 1; i <= MAX_SAVE_SLOTS; i++)
    {
        std::string saveKey = "Game" + std::to_string(i);
        if (!gameSaves[saveKey].exists)
        {
            return i;
        }
    }
    return MAX_SAVE_SLOTS + 1;
}

// Count existing saves
int countExistingSaves()
{
    int count = 0;
    for (int i = 1; i <= MAX_SAVE_SLOTS; i++)
    {
        std::string saveKey = "Game" + std::to_string(i);
        if (gameSaves[saveKey].exists) count++;
    }
    return count;
}

// Game state management functions
void incrementEnemiesDefeated()
{
    totalEnemiesDefeated++;
}

void updatePlayerPosition(int x, int y)
{
    currentPlayerX = x;
    currentPlayerY = y;
}

void setCurrentDifficulty(const configurationDifficulty& difficulty)
{
    currentDifficulty = difficulty;
}

configurationDifficulty getCurrentDifficulty()
{
    return currentDifficulty;
}

int getCurrentEnemyCount()
{
    return totalEnemiesDefeated;
}

std::string getCurrentLocationString()
{
    if (currentPlayerX < 10) return "Western Woods";
    else if (currentPlayerX > 20) return "Eastern Plains";
    else if (currentPlayerY < 30) return "Northern Mountains";
    else if (currentPlayerY > 60) return "Southern Desert";
    else return "Central Village";
}

// Get access to saves map
std::map<std::string, GameData>& getGameSavesMap()
{
    return gameSaves;
}

// Save current progress during gameplay
void saveCurrentProgress(const std::string& location)
{
    std::string currentSaveSlot = "Game1";
    for (int i = 1; i <= MAX_SAVE_SLOTS; i++)
    {
        std::string saveKey = "Game" + std::to_string(i);
        if (gameSaves[saveKey].exists && gameSaves[saveKey].characterName == selectedName)
        {
            currentSaveSlot = saveKey;
            break;
        }
    }
    
    GameData updatedData(selectedName, getCurrentDateTime(), location,
                         playerSelected, currentDifficulty, 
                         totalEnemiesDefeated, currentPlayerX, currentPlayerY, 
                         playerSelected.getCurrentEnemiesKilled());
    
    // Establecer el mapa actual en los datos de guardado
    updatedData.currentMapId = getCurrentMapId();
    updatedData.enemiesPerMap = playerSelected.getEnemiesKilledPerMap();
    
    saveCompleteGameData(currentSaveSlot, updatedData);
}

#endif