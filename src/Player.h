#ifndef PLAYER_H // Header guard: prevents multiple inclusions of this file during compilation
#define PLAYER_H

// ======== REQUIRED SYSTEM LIBRARIES ========
// These standard C++ libraries provide essential functionality for the Player class
#include <string>   // For std::string data type - used for player name storage
#include <iostream> // For console input/output operations (std::cout for displaying messages)
#include <map>      // For std::map container - used to track enemy defeats per map area

// ======== PLAYER CHARACTER CLASS DEFINITION ========
// This class represents the main playable character and manages all player-related data
// It handles stats, combat mechanics, progression tracking, and map-based enemy counters
class Player
{
private:
    // ======== CORE CHARACTER ATTRIBUTES ========
    // These variables store the fundamental characteristics that define the player character
    
    std::string name;  // Player's chosen name - displayed in UI and combat messages
    int health;        // Current health points - when this reaches 0, the player dies
    int attack;        // Base attack power - determines damage dealt to enemies in combat
    int maxHealth;     // Maximum possible health points - used for healing calculations and display
    int defense;       // Defensive capability - reduces incoming damage through mitigation formula
    int specialAttack; // Special ability power - used for powerful special attacks in combat
    
    // ======== PROGRESSION TRACKING SYSTEM ========
    // These variables manage the player's progress through different map areas
    
    int enemiesKilled; // Current map's enemy defeat counter - tracks progress in active area
    std::map<int, int> enemiesKilledPerMap; // Per-map enemy counters (map_id -> enemy_count)
                                           // Allows tracking progress across multiple areas independently

public:
    // ======== PLAYER CHARACTER CONSTRUCTOR ========
    // Initializes a new player character with specified combat statistics
    // This constructor sets up all the basic attributes needed for gameplay
    // Parameters: health - starting/maximum HP, attack - base damage, defense - damage reduction, specialAttack - special ability power
    Player(int health, int attack, int defense, int specialAttack)
        : name("Player"),                    // Default name - will be customized later via setName()
          health(health),                    // Set current health to the provided starting value
          attack(attack),                    // Set base attack power for combat calculations
          defense(defense),                  // Set defensive capability for damage mitigation
          specialAttack(specialAttack),      // Set special attack power for powerful abilities
          maxHealth(health),                 // Set maximum health equal to starting health
          enemiesKilled(0)                   // Initialize enemy counter to 0 (no enemies defeated yet)
    {
        // Constructor body is empty - all initialization is handled in the member initializer list above
    }

    // ======== PLAYER NAME CUSTOMIZATION ========
    // Method to set a custom name for the player character
    // This allows personalization and is typically called during character creation
    // Parameter: playerName - the desired name string for this player character
    void setName(const std::string& playerName) {
        name = playerName;  // Store the provided name, replacing the default "Player"
    }

    // ======== HEALTH RESTORATION SYSTEM ========
    // Method to restore the player's health points, typically used at save points or with healing items
    // Implements intelligent healing that prevents exceeding maximum health capacity
    // Parameter: amount - number of health points to restore
    void heal(int amount){
        // ======== HEALTH CALCULATION ========
        // Add the healing amount to current health
        health += amount;
        
        // ======== MAXIMUM HEALTH ENFORCEMENT ========
        // Prevent health from exceeding the maximum allowed value
        // This maintains game balance and prevents exploitation
        if (health > maxHealth)
        {
            health = maxHealth;  // Cap health at maximum value
        }
        
        // ======== HEALING FEEDBACK ========
        // Provide clear information to the player about the healing effect
        std::cout << "You cured " << amount << "HP. Current life: " << health << "/" << maxHealth << std::endl;
    }

    // ======== PLAYER STATUS DISPLAY SYSTEM ========
    // Method to display comprehensive player statistics in a formatted, readable way
    // This is used in menus, debug screens, and status checks throughout the game
    void showStats() const
    {
        // ======== FORMATTED STATUS OUTPUT ========
        // Display all important player information in a single, organized line
        // Format: "Player: [name] | Health: [current] | Attack: [value] | Defense: [value] | Special: [value] | Enemies Killed: [count]"
        std::cout << "Player: " << name                    // Player's custom name
                  << " | Health: " << health               // Current health points
                  << " | Attack: " << attack               // Base attack power
                  << " | Defense: " << defense             // Defensive capability
                  << " | Special: " << specialAttack       // Special attack power
                  << " | Enemies Killed: " << enemiesKilled << std::endl;  // Current map progress
    }

    // ======== DAMAGE RECEPTION AND MITIGATION SYSTEM ========
    // Method to handle incoming damage with defense-based mitigation calculations
    // This implements the core defensive mechanics that make defense stats meaningful
    // Parameter: damage - raw damage amount before any defensive calculations
    void receiveDamage(int damage)
    {
        // ======== INVALID DAMAGE PROTECTION ========
        // Prevent processing of zero or negative damage values
        if (damage <= 0)
            return;

        // ======== PROPORTIONAL DEFENSE MITIGATION ========
        // Calculate reduced damage using a proportional formula that scales with defense
        // Formula: mitigated_damage = original_damage * 100 / (100 + defense)
        // This means higher defense provides diminishing returns, preventing invincibility
        // Example: 10 defense = ~9% damage reduction, 50 defense = ~33% reduction, 100 defense = 50% reduction
        int mitigatedDamage = (damage * 100) / (100 + defense);

        // ======== HEALTH REDUCTION ========
        // Apply the calculated damage to the player's current health
        health -= mitigatedDamage;

        // ======== DAMAGE FEEDBACK ========
        // Inform the player about the actual damage taken after defensive mitigation
        std::cout << "Player received " << mitigatedDamage << " damage after mitigation." << std::endl;

        // ======== DEATH PREVENTION ========
        // Ensure health never goes below 0 for clean death handling
        if (health < 0)
            health = 0;
    }

    // ======== BASIC ATTRIBUTE GETTER METHODS ========
    // These methods provide safe read-only access to player statistics
    // They follow the encapsulation principle by keeping data private while allowing controlled access
    
    // Returns current health points - used for combat calculations and UI display
    int getHealth() const { return health; }

    // Returns maximum possible health - used for healing limits and health bar displays
    int getMaxHealth() const { return maxHealth; }

    // Returns base attack power - used in combat damage calculations
    int getAttack() const { return attack; }

    // Returns defensive capability - used in damage mitigation calculations
    int getDefense() const { return defense; }

    // Returns special attack power - used for special ability damage calculations
    int getSpecialAttack() const { return specialAttack; }

    // Returns player's current name - used for display in UI and combat messages
    std::string getName() const { return name; }

    // ======== ENEMY DEFEAT TRACKING SYSTEM ========
    // These methods manage the progression system that tracks enemy defeats per map area
    
    // Returns the current map's enemy defeat count - used to check progression requirements
    int getEnemiesKilled() const {return enemiesKilled;}

    // Increments the enemy defeat counter when the player wins a battle
    // Called automatically after successful combat encounters
    void addEnemyKill() {enemiesKilled++;}

    // Checks if the player has defeated enough enemies to advance to new map areas
    // Returns true if the player has defeated 5 or more enemies in the current area
    bool canAdvanceToNextMap(){return enemiesKilled >= 5;}

    // ======== MAP TRANSITION AND PROGRESS MANAGEMENT ========
    // This method handles the complex logic of switching between different map areas
    // while preserving individual progress counters for each area
    // Parameters: currentMapId - ID of the map being left, newMapId - ID of the destination map
    void changeToMap(int currentMapId, int newMapId) {
        // ======== SAVE CURRENT PROGRESS ========
        // Store the current map's enemy defeat count in the per-map tracking system
        // This ensures progress isn't lost when leaving an area
        enemiesKilledPerMap[currentMapId] = enemiesKilled;
        
        // ======== LOAD DESTINATION PROGRESS ========
        // Retrieve the enemy defeat count for the destination map
        // If this is the first visit to the map, the count will default to 0
        enemiesKilled = enemiesKilledPerMap[newMapId];
    }
    
    // ======== SAVE/LOAD SYSTEM SUPPORT METHODS ========
    // These methods provide the interface needed for game save and load functionality
    // They allow external systems to preserve and restore player progress
    
    // Resets the current map's enemy counter to 0 - used for compatibility with older systems
    void resetEnemyCount() {enemiesKilled = 0;}
    
    // Directly sets the enemy defeat count - used when loading saved game data
    // Parameter: count - the saved enemy defeat count to restore
    void setEnemiesKilled(int count) {enemiesKilled = count;}
    
    // Returns the current enemy defeat count - used when saving game progress
    int getCurrentEnemiesKilled() const {return enemiesKilled;}
    
    // Returns the complete map-to-counter data structure - used for comprehensive save operations
    std::map<int, int> getEnemiesKilledPerMap() const {return enemiesKilledPerMap;}
    
    // Restores the complete map-to-counter data structure - used when loading saved games
    // Parameter: mapCounters - the saved per-map enemy defeat data to restore
    void setEnemiesKilledPerMap(const std::map<int, int>& mapCounters) {enemiesKilledPerMap = mapCounters;}
};

#endif // End of header guard - matches the #ifndef at the beginning of the file
