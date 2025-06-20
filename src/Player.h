#ifndef PLAYER_H // Header guard: ensures this file is included only once per compilation
#define PLAYER_H

#include <string>   // Include support for the std::string data type
#include <iostream> // Include for console output (e.g., std::cout)

// Declaration of the Player class, which represents a playable character in the game
class Player
{
private:
    std::string name;  // Name of the player character (currently set to a default value)
    int health;        // Player's current health points
    int attack;        // Player's basic attack power
    int defense;       // Player's defense points which reduce incoming damage
    int specialAttack; // Player's special ability power (used in special attacks)

public:
    // Constructor for initializing a player object with health, attack, defense, and specialAttack values
    Player(int health, int attack, int defense, int specialAttack)
        : name("Player1"),  // Initializes the name to "Player1" by default
          health(health),   // Initializes health using the provided constructor argument
          attack(attack),   // Initializes attack power
          defense(defense), // Initializes defense points
          specialAttack(specialAttack)
    {
    } // Initializes special attack power

    // Method to display the player's current stats in the console
    void showStats() const
    {
        std::cout << "Player: " << name
                  << " | Health: " << health
                  << " | Attack: " << attack
                  << " | Defense: " << defense
                  << " | Special: " << specialAttack << std::endl;
    }

    // Method to apply damage to the player based on incoming attack value
    void receiveDamage(int damage)
    {
        int realDamage = damage - defense; // Calculate net damage after subtracting defense
        if (realDamage < 0)
            realDamage = 0; // If defense fully absorbs damage, clamp to 0

        if (realDamage == 0)
            std::cout << "The player's defense was enough. No damage taken." << std::endl;

        health -= realDamage; // Subtract effective damage from health
        if (health < 0)
            health = 0; // Prevent health from becoming negative
    }

    // Getter for player's current health
    int getHealth() const { return health; }

    // Getter for player's attack stat
    int getAttack() const { return attack; }

    // Getter for player's defense stat
    int getDefense() const { return defense; }

    // Getter for player's special attack stat
    int getSpecialAttack() const { return specialAttack; }

    // Getter for player's name
    std::string getName() const { return name; }
};

#endif // End of header guard
