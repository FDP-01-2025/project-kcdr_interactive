#ifndef DAMAGE_ITEM_H
#define DAMAGE_ITEM_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Enemy.h"

// Class for damage items
class DamageItem
{
private:
    std::string name;
    int damage;
    int quantity;

public:
    // Constructor for damage items
    DamageItem(std::string n, int dmg, int qty = 1)
        : name(n), damage(dmg), quantity(qty) {}

    // Function that applies damage to an enemy
    void use(Player &player, Enemy &target);

    // Getters to obtain item information
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    int getDamage() const { return damage; }

    // Method to check if items are available
    bool isAvailable() const { return quantity > 0; }

    // Method to add more items to the inventory
    void addQuantity(int amount) { quantity += amount; }
};

// Implementation of the use function
inline void DamageItem::use(Player &player, Enemy &target)
{
    if (quantity > 0)
    {
        target.receiveDamage(damage);
        quantity--;
        std::cout << player.getName() << " used " << name << " on " << target.getName()
                  << " dealing " << damage << " damage! Remaining: " << quantity << std::endl;
    }
    else
    {
        std::cout << "No " << name << " left!" << std::endl;
    }
}

#endif // DAMAGE_ITEM_H
