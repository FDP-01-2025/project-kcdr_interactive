#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Enemy.h"

// ==================== CLASE PARA ITEMS DE CURACIÓN ====================
class HealingItem
{
private:
    std::string name;
    int healAmount;
    int quantity;

public:
    // Constructor para items de curación
    HealingItem(std::string n, int heal, int qty = 1)
    : name(n), healAmount(heal), quantity(qty) {}

    // Función que cura al jugador
    void use(Player& player);

    // Getters para obtener información del item
    std::string getName() const {return name;}
    int getQuantity() const {return quantity;}
    int getHealAmount() const {return healAmount;}
    
    // Método para verificar si hay items disponibles
    bool isAvailable() const {return quantity > 0;}
    
    // Método para añadir más items al inventario
    void addQuantity(int amount) {quantity += amount;}
};

// ==================== CLASE PARA ITEMS DE DAÑO ====================
class DamageItem
{
private:
    std::string name;
    int damage;
    int quantity;

public:
    // Constructor para items de daño
    DamageItem(std::string n, int dmg, int qty = 1)
    : name(n), damage(dmg), quantity(qty) {}

    // Función que aplica daño a un enemigo
    void use(Player& player, Enemy& target);
    
    // Getters para obtener información del item
    std::string getName() const {return name;}
    int getQuantity() const {return quantity;}
    int getDamage() const {return damage;}
    
    // Método para verificar si hay items disponibles
    bool isAvailable() const {return quantity > 0;}
    
    // Método para añadir más items al inventario
    void addQuantity(int amount) {quantity += amount;}
};

// ==================== IMPLEMENTACIONES ====================

// Implementación de la función use para HealingItem
inline void HealingItem::use(Player& player) {
    if (quantity > 0) {
        player.heal(healAmount);
        quantity--;
        std::cout << "Used " << name << ". Healed " << healAmount << " HP. Remaining: " << quantity << std::endl;
    } else {
        std::cout << "No " << name << " left!" << std::endl;
    }
}

// Implementación de la función use para DamageItem
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