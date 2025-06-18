#ifndef BOSS_H // ifndef to check if this file has already been included in another .h
#define BOSS_H // if it hasn't been included anywhere else, this allows it to be used here

// DO NOT INCLUDE "using namespace std;" IN A HEADER FILE BECAUSE IT COULD CAUSE CONFLICTS WITH OTHER .cpp FILES OR NAME DECLARATIONS (GOOD PRACTICE)

#include <string> // to be able to use string data type

class Boss
{
private:
    std::string name;
    int health;       // Variable para manejar la vida del
    int attack;       // Variable para manejar el ataque del
    int defense;      // Variable para manejar la defensa del
    int specialAtack; // Variable para manejar el ataque especial
public:
    // Constructor para mandar a llamar a mandar a crear el jefe con salud defensa y ataque especial
    Boss(const std::string &name, int health, int attack, int defense, int specialAtack);

    // Getters para obtener un valor de una variable privada
    std::string getName() const; // Obtener su nombre
    int getHealth() const;       // Obtener valor de la vida
    int getAttack() const;       // Obtener cuanto ataque tendra
    int getDefense() const;      // Obtener cuanta defensa tendra
    int getspecialAtack() const; // Obtener cuanto daño hara ataque especial

    // Setters para poder modificar un valor de una variable privada
    void setHealth(int healt);

    // Actions para regresar acciones o comportamientos que el jefe puede realizar
    void takeDamage(int amount);     // cantidad de vida que se le pondra quitar al jefe
    int performAttack() const;       // ataque normal que podra hacer el jefe
    int performSpecialAtack() const; // ataque espeial que podra hacer el jefe
    bool isDefeated() const;         // Permite saber si el jefe ha sido derrotado
};

#endif