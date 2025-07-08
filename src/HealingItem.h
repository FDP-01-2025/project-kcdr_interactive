#ifndef HEALING_ITEM_H
#define HEALING_ITEM_H

#include <iostream>
#include <string>
#include "Player.h"

// Class for healing items
class HealingItem
{
// Declaration of private variables for healing items
private:
    std::string name;
    int healAmount;
    int quantity;

public:
    // Constructor for healing items
    HealingItem(std::string n, int heal, int qty = 1)
    : name(n), healAmount(heal), quantity(qty) {}

    // Function that heals the player
    void use(Player& player);

    // Getters to obtain item information
    std::string getName() const {return name;}
    int getQuantity() const {return quantity;}
    int getHealAmount() const {return healAmount;}
    
    // Method to check if items are available
    bool isAvailable() const {return quantity > 0;}
    
    // Method to add more items to the inventory
    void addQuantity(int amount) {quantity += amount;}
};

// Implementation of the use function
inline void HealingItem::use(Player& player) {
    if (quantity > 0) {
        player.heal(healAmount);
        quantity--;
        std::cout << "Used " << name << ". Healed " << healAmount << " HP. Remaining: " << quantity << std::endl;
    } else {
        std::cout << "No " << name << " left!" << std::endl;
    }
}

#endif // HEALING_ITEM_H
