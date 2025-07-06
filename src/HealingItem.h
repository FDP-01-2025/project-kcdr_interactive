#ifndef HEALING_ITEM_H
#define HEALING_ITEM_H

#include <iostream>
#include <string>
#include "Player.h"

//Clase para items de curacion
class HealingItem
{
//Declaracion de variables privadas para items de curacion
private:
    std::string name;
    int healAmount;
    int quantity;

public:
    //Constructor para items de curacion
    HealingItem(std::string n, int heal, int qty = 1)
    : name(n), healAmount(heal), quantity(qty) {}

    //Funcion que cura al jugador
    void use(Player& player);

    //Getters para obtener información del item
    std::string getName() const {return name;}
    int getQuantity() const {return quantity;}
    int getHealAmount() const {return healAmount;}
    
    //Metodo para verificar si hay items disponibles
    bool isAvailable() const {return quantity > 0;}
    
    //Metodo para añadir más items al inventario
    void addQuantity(int amount) {quantity += amount;}
};

// Implementacion de la funcion use
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
