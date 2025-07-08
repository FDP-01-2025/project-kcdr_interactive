#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Enemy.h"

// ==================== CLASS FOR HEALING ITEMS ====================
class HealingItem
{
private:
    std::string name;
    int healAmount;
    int quantity;

public:
    // Default constructor
    HealingItem() : name(""), healAmount(0), quantity(0) {}
    
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

// ==================== CLASS FOR DAMAGE ITEMS ====================
class DamageItem
{
private:
    std::string name;
    int damage;
    int quantity;

public:
    // Default constructor
    DamageItem() : name(""), damage(0), quantity(0) {}
    
    // Constructor for damage items
    DamageItem(std::string n, int dmg, int qty = 1)
    : name(n), damage(dmg), quantity(qty) {}

    // Function that applies damage to an enemy
    void use(Player& player, Enemy& target);
    
    // Getters to obtain item information
    std::string getName() const {return name;}
    int getQuantity() const {return quantity;}
    int getDamage() const {return damage;}
    
    // Method to check if items are available
    bool isAvailable() const {return quantity > 0;}
    
    // Method to add more items to the inventory
    void addQuantity(int amount) {quantity += amount;}
};

// ==================== IMPLEMENTATIONS ====================

// Implementation of the use function for HealingItem
inline void HealingItem::use(Player& player) {
    if (quantity > 0) {
        player.heal(healAmount);
        quantity--;
        std::cout << "Used " << name << ". Healed " << healAmount << " HP. Remaining: " << quantity << std::endl;
    } else {
        std::cout << "No " << name << " left!" << std::endl;
    }
}

// Implementation of the use function for DamageItem
inline void DamageItem::use(Player& player, Enemy& target) {
    if (quantity > 0) {
        target.receiveDamage(damage);
        quantity--;
        std::cout << player.getName() << " used " << name << " on " << target.getName() 
                  << " dealing " << damage << " damage! Remaining: " << quantity << std::endl;
    } else {
        std::cout << "No " << name << " left!" << std::endl;
    }
}

#endif // ITEM_H