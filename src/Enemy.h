#ifndef ENEMY_H // Header guard: if ENEMY_H is not defined, define it now to avoid multiple inclusions
#define ENEMY_H // Defines ENEMY_H so that this file content is not included again elsewhere

// NOTE: Never use "using namespace std;" in a header file, as it can lead to name conflicts 
// across other translation units (good practice).

#include <string>   // Includes the string library to use std::string for storing text
#include <iostream> // Includes the iostream library for input and output operations
#include <cstdlib>  // For rand() function

// Forward declarations to avoid circular dependencies
class Inventory;

// Definition of the Enemy class
class Enemy {
private:
    // ======== PRIVATE ATTRIBUTES ========
    std::string name;     // Name of the enemy (used for display or identification)
    std::string asciiArt; // ASCII art string for visual representation of the enemy
    int health;           // Current life points or hit points (HP) of the enemy
    int maxHealth;        // Maximum life points of the enemy
    int attack;           // Offensive power — how much damage the enemy can deal
    int defense;          // Defensive strength — how much incoming damage is reduced

public:
    // ======== CONSTRUCTOR ========
    // Public constructor that allows instantiation of the Enemy class
    // It initializes all core attributes of the enemy: name, health, attack, defense, and art
    Enemy(const std::string &name, int health, int attack, int defense, const std::string &art);

    // ======== METHODS ========

    // Displays the current stats of the enemy in the console
    void showStats() const;

    // Applies damage to the enemy, reducing health based on defense
    void receiveDamage(int damage);
    // Note: This is not a const method because it modifies the health value

    // Gives drops to player inventory based on enemy type
    void giveDropsToPlayer(Inventory& inventory, int& playerGold) const;

    // ======== GETTERS (ACCESSORS) ========

    // Returns the attack value of the enemy
    int getAttack() const;

    // Returns the current health of the enemy
    int getHealth() const;

    // Returns the maximum health of the enemy
    int getMaxHealth() const;

    // Returns the current defense of the enemy
    int getDefense() const;

    // Returns the ASCII art as a string so it can be drawn externally (e.g., on a map)
    std::string getAsciiArt() const;

    // Displays the ASCII art directly in the console
    void showArt() const;

    // Returns the name of the enemy
    std::string getName() const;
};

// ======== METHOD IMPLEMENTATIONS ========
// Inline definitions for simplicity since this is a header file
// These should ideally be placed in a corresponding .cpp file in large projects

// Constructor: initializes all attributes using an initializer list
inline Enemy::Enemy(const std::string &name, int health, int attack, int defense, const std::string &art)
    : name(name), asciiArt(art), health(health), maxHealth(health), attack(attack), defense(defense) {}

// Prints the enemy's name, health, attack, and defense to the console
inline void Enemy::showStats() const {
    std::cout << "Name: " << name
              << "\nHP: " << health
              << "\nAttack: " << attack
              << "\nDefense: " << defense
              << std::endl;
}

// Applies damage to the enemy, reducing its health by (damage - defense)
// Ensures that health doesn't drop below 0
inline void Enemy::receiveDamage(int damage) {
    int netDamage = damage - defense; // Subtracts defense from incoming damage

    if (netDamage > 0) {              // Only apply damage if it's positive
        health -= netDamage;          // Subtract damage from health
        if (health < 0)               // Prevent negative health
            health = 0;
    }
}

// Getter: returns the attack value of the enemy
inline int Enemy::getAttack() const {
    return attack;
}

// Getter: returns the current health of the enemy
inline int Enemy::getHealth() const {
    return health;
}

// Getter: returns the maximum health of the enemy
inline int Enemy::getMaxHealth() const {
    return maxHealth;
}

inline int Enemy::getDefense() const{
    return defense;
}

// Outputs the ASCII art to the console
inline void Enemy::showArt() const {
    std::cout << asciiArt << std::endl;
}

// Getter: returns the name of the enemy
inline std::string Enemy::getName() const {
    return name;
}

// Getter: returns the ASCII art string for external use (e.g., to draw it)
inline std::string Enemy::getAsciiArt() const {
    return asciiArt;
}

// Declares an external array of 12 enemies that will be defined elsewhere (e.g., in a .cpp file)
// This allows all files including this header to access the shared enemy array
extern Enemy enemy[12];

#endif // End of the include guard
