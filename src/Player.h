#ifndef PLAYER_H // ifndef to check if this file has already been included in another .h
#define PLAYER_H // if it hasn't been included anywhere else, this allows it to be used here

// DO NOT INCLUDE "using namespace std;" IN A HEADER FILE BECAUSE IT COULD CAUSE CONFLICTS WITH OTHER .cpp FILES OR NAME DECLARATIONS (GOOD PRACTICE)

#include <string> // to be able to use string data type

class Player
{
    // We declare everything private so modifications can only be made within this header file,
    // and not from main when it's included
private:
    std::string name;  // Name of the player, it will be a hardcoded name
    int health;        // Health attribute representing the player's life points
    int attack;        // Attack attribute representing the player's attack power
    int defense;       // Defense attribute representing the player's defense capability
    int specialAttack; // Special attack attribute representing the player's special attack

public:
    // We allow the constructor to be public so it can be used outside the class, for example, in main.cpp
    // Constructor: creates a player with health, attack, defense, and special attack
    Player(int health, int attack, int defense, int specialAttack);

    // What is const? This means it will not modify the object, it will only read its data

    // Utility methods: only used to read and display values, they return nothing (That's why we use void = empty)
    void showStats() const;
    void receiveDamage(int damage); // We declare a damage variable because it may vary

    // Public "getter" functions to access private class data
    int getAttack() const;
    int getHealth() const;
    int getSpecialAttack() const;
    int getDefense() const;
    std::string getName() const;

    // Method to heal the player (adds amount to health)
    void heal(int amount)
    {
        health += amount;
    }
};

#endif
