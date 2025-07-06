#ifndef BOSS_H // Header guard to prevent multiple inclusions of this file
#define BOSS_H // Define BOSS_H macro if not already defined

// DO NOT INCLUDE "using namespace std;" IN HEADER FILES TO AVOID NAMESPACE CONFLICTS (BEST PRACTICE)

#include <string> // Include string library for std::string data type

// Forward declaration to avoid circular dependency with BossDraw.h
std::string getBossAsciiArt(const std::string& bossName);

class Boss
{
private:
    std::string name;        // Boss name identifier
    int health;              // Current health points of the boss
    int maxHealth;           // Maximum health points of the boss
    std::string asciiArt;    // ASCII art string for visual representation of the boss
    int attack;              // Base attack damage value
    int defense;             // Defense points to reduce incoming damage
    int specialAttack;       // Special attack damage value (higher than normal attack)
public:
    // Constructor to create a boss with specified stats and ASCII art
    Boss(const std::string &name, int health, int attack, int defense, int specialAttack, const std::string &art);

    // Getter methods to access private member variables
    std::string getName() const { return name; }            // Get boss name
    int getHealth() const { return health; }                // Get current health value
    int getMaxHealth() const { return maxHealth; }          // Get maximum health value
    int getAttack() const { return attack; }                // Get base attack damage
    int getDefense() const { return defense; }              // Get defense points
    int getSpecialAttack() const { return specialAttack; }  // Get special attack damage
    
    // Getter method: returns the ASCII art string for external use (e.g., for drawing)
    inline std::string getAsciiArt() const
    {
        return asciiArt;
    }

    // Setter methods to modify private member variables
    void setHealth(int newHealth) { health = newHealth; }   // Update boss health

    // Action methods that define boss behaviors and abilities
    void takeDamage(int amount) // Reduce boss health by specified damage amount
    {
        health -= amount;       // Subtract damage from current health
        if (health < 0)         // Ensure health doesn't go below zero
        {
            health = 0;
        }
    }
    int performAttack() const { return attack; }                // Execute normal attack and return damage
    int performSpecialAttack() const { return specialAttack; }  // Execute special attack and return damage
    bool isDefeated() const { return health <= 0; }             // Check if boss has been defeated (health <= 0)
};

// ========== Constructor Implementation ==========
// Initialize all member variables using the constructor parameter list for efficiency
inline Boss::Boss(const std::string &name, int health, int attack, int defense, int specialAttack, const std::string &art)
    : name(name), health(health), maxHealth(health), attack(attack), defense(defense), specialAttack(specialAttack), asciiArt(art) {
}

// ========== Boss Creation Functions ==========
// Include BossDraw.h here to avoid circular dependency issues
#include "BossDraw.h"

// Factory functions to create specific boss instances with predefined stats and ASCII art
inline Boss createBoss1() { return Boss("Queen of Shadows", 200, 40, 20, 60, getBossAsciiArt("Queen of Shadows")); }
inline Boss createBoss2() { return Boss("Arcane Sovereign", 200, 40, 20, 60, getBossAsciiArt("Arcane Sovereign")); }
inline Boss createBoss3() { return Boss("Crystal Queen", 200, 40, 20, 60, getBossAsciiArt("Crystal Queen")); }
inline Boss createBoss4() { return Boss("Void Sovereign", 200, 40, 20, 60, getBossAsciiArt("Void Sovereign")); }

#endif // End of header guard
