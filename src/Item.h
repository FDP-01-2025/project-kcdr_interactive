#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

class Player;
class Enemy;

//Clase para items de curacion
class healingItem
{
//Declaracion de variables privadas para items de curacion
private:
    std::string name;
    int healtAmount;
    int quantity;
public:
    //Renombrar las variables para poder usarla dentro del juego 
    healingItem(std::string n, int healt, int qty = 1)
    : name(n), healtAmount(healt), quantity(qty) {}

    //funcion que no retorna nada que recibe una referencia de la clase jugador
    void use(Player& player){
        if (quantity > 0)
        {
            player.heal(healtAmount)
        }
        
    }

    //Getter para poder tomar el nombre del obejto
    std::string getName() const {return name;}
    //Getter para poder tomar la cantidad del objeto
    int getQuantity() const {return quantity;}
};

//Clase para items de daño
class damageItem
{
private:
    std::string name;
    int damage;
    int quantity;

public:
    damageItem(std::string n, int dmg, int qty = 1)
    : name(n), damage(dmg), quantity(qty) {}

    void use(Player& player, Enemy& target);
    std::string getName() const {return name;}
    int getQuantity() const {return quantity;}
};


#endif