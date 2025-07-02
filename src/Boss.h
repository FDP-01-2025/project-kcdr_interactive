#ifndef BOSS_H // ifndef to check if this file has already been included in another .h
#define BOSS_H // if it hasn't been included anywhere else, this allows it to be used here

// DO NOT INCLUDE "using namespace std;" IN A HEADER FILE BECAUSE IT COULD CAUSE CONFLICTS WITH OTHER .cpp FILES OR NAME DECLARATIONS (GOOD PRACTICE)

#include <string> // to be able to use string data type

class Boss
{
private:
    std::string name;
    int health;           // Variable para manejar la vida del
    std::string asciiArt; // ASCII art string for visual representation of the enemy
    int attack;           // Variable para manejar el ataque del
    int defense;          // Variable para manejar la defensa del
    int specialAtack;     // Variable para manejar el ataque especial
public:
    // Constructor para mandar a llamar a mandar a crear el jefe con salud defensa y ataque especial
    Boss(const std::string &name, int health, int attack, int defense, int specialAtack, const std::string &art);

    // Getters para obtener un valor de una variable privada
    std::string getName() const { return name; }         // Obtener su nombre
    int getHealth() const { return health; }             // Obtener valor de la vida
    int getAttack() const { return attack; }             // Obtener cuanto ataque tendra
    int getDefense() const { return defense; }           // Obtener cuanta defensa tendra
    int getspecialAtack() const { return specialAtack; } // Obtener cuanto daño hara ataque especial
    // Getter: returns the ASCII art string for external use (e.g., to draw it)
    inline std::string Boss::getAsciiArt() const
    {
        return asciiArt;
    }

    // Setters para poder modificar un valor de una variable privada
    void setHealth(int newHealt) { health = newHealt; }

    // Actions para regresar acciones o comportamientos que el jefe puede realizar
    void takeDamage(int amount) // cantidad de vida que se le pondra quitar al jefe
    {
        health -= amount;
        if (health < 0)
        {
            health = 0;
        }
    }
    int performAttack() const { return attack; }             // ataque normal que podra hacer el jefe
    int performSpecialAtack() const { return specialAtack; } // ataque espeial que podra hacer el jefe
    bool isDefeated() const { return health <= 0; }          // Permite saber si el jefe ha sido derrotado
};

// ========== Boss creation ==========
inline Boss createBoss1() { return Boss("Jefe1", 200, 40, 20, 60); }
inline Boss createBoss2() { return Boss("Jefe2", 200, 40, 20, 60); }
inline Boss createBoss3() { return Boss("Jefe3", 200, 40, 20, 60); }
inline Boss createBoss4() { return Boss("Jefe4", 200, 40, 20, 60); }

#endif // End of header guard
