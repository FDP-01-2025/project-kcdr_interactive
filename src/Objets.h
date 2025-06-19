#ifndef OBJETS_H
#define OBJETS_H

#include <iostream>
#include "../src/Enemy.h"
#include "../src/Player.h"

// Main class Objects
class Objects
{
public:
    // Variable for healing object (you can change the value depending on the potion type)
    int healing;

    // Variable for bomb (fixed damage of 25)
    int bomb;

    // Variables for keys for each boss
    bool keyBoss1;
    bool keyBoss2;
    bool keyBoss3;

    // Constructor: initializes default values
    Objects()
        : healing(0), bomb(25), keyBoss1(false), keyBoss2(false), keyBoss3(false) {}

    // Methods to use the objects 

    // Heal the player using the healing item
    void useHealing(Player &player)
    {
        player.heal(healing);
        std::cout << "You have healed " << healing << " health points." << std::endl;
        healing = 0; // The healing is consumed
    }

     // Use bomb on enemy
    void useBomb(Enemy &enemy)
    {
        enemy.receiveDamage(bomb);
        std::cout << "You used a bomb and dealt " << bomb << " points of damage to the enemy!" << std::endl;
    }

    void obtainKey(int boss)
    {
        if (boss == 1)
            keyBoss1 = true;
        else if (boss == 2)
            keyBoss2 = true;
        else if (boss == 3)
            keyBoss3 = true;
    }

    bool hasKey(int boss) const
    {
        if (boss == 1)
            return keyBoss1;
        else if (boss == 2)
            return keyBoss2;
        else if (boss == 3)
            return keyBoss3;
        return false;
    }
};

#endif