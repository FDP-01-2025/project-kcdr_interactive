#ifndef ENEMY_H // ifndef to check if this file has already been included in another .h
#define ENEMY_H // if it hasn't been included anywhere else, this allows it to be used here

// DO NOT INCLUDE "using namespace std;" IN A HEADER FILE BECAUSE IT COULD CAUSE CONFLICTS WITH OTHER .cpp FILES OR NAME DECLARATIONS (GOOD PRACTICE)

#include <string> // to be able to use string data type

class Enemy
{
    // We declare everything private so modifications can only be made within this header file,
    // and not from main when it's included

private:
    std::string name; // Name of the enemy to identify what type of enemy it is
    int health;       // Health attribute representing the enemy's life points
    int attack;       // Attack attribute representing the enemy's attack power
    int defense;      // Defense attribute representing the enemy's defense capability

public:
    // We allow the constructor to be public so it can be used outside the class, for example, in main.cpp
    // Constructor: creates an enemy with health, attack, and defense
    Enemy(int health, int attack, int defense);

    // Utility methods: only used to read and display values, they return nothing (That's why we use void = empty)
    void showStats() const;
    void receiveDamage(int damage);
    // receiveDamage is not marked as const because we want this value to change —
    // depending on the player's attack, the enemy's health will decrease

    // Public "getter" functions to access private class data
    int getAttack() const;
    int getHealth() const;
    std::string getName() const;

    // This method subtracts the specified amount from the enemy's health.
    // It is used when the enemy receives damage from the player or other sources.
    void receiveDamage(int amount)
    {
        health -= amount;
    }
};

#endif
