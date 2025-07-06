#ifndef DAMAGE_ITEM_H
#define DAMAGE_ITEM_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Enemy.h"

//Clase para items de daño
class DamageItem
{
private:
    std::string name;
    int damage;
    int quantity;

public:
    //Constructor para items de daño
    DamageItem(std::string n, int dmg, int qty = 1)
    : name(n), damage(dmg), quantity(qty) {}

    //Funcion que aplica daño a un enemigo
    void use(Player& player, Enemy& target);
    
    //Getters para obtener información del item
    std::string getName() const {return name;}
    int getQuantity() const {return quantity;}
    int getDamage() const {return damage;}
    
    //Metodo para verificar si hay items disponibles
    bool isAvailable() const {return quantity > 0;}
    
    //Metodo para añadir más items al inventario
    void addQuantity(int amount) {quantity += amount;}
};

// Implementacion de la funcion use
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

#endif // DAMAGE_ITEM_H
