#ifndef PLAYER_H // Header guard: ensures this file is included only once per compilation
#define PLAYER_H

#include <string>   // Include support for the std::string data type
#include <iostream> // Include for console output (e.g., std::cout)
#include <map>      // Include for std::map to handle per-map enemy counters

// Declaration of the Player class, which represents a playable character in the game
class Player
{
private:
    std::string name;  // Name of the player character (currently set to a default value)
    int health;        // Player's current health points
    int attack;        // Player's basic attack power
    int maxHealth;     // Variable para saber hasta cuanto es la vida maxima de un jugador
    int defense;       // Player's defense points which reduce incoming damage
    int specialAttack; // Player's special ability power (used in special attacks)
    int enemiesKilled; // Current map enemy counter (for backward compatibility)
    std::map<int, int> enemiesKilledPerMap; // Counter per map (map_id -> enemy_count)
public:
    // Constructor for initializing a player object with health, attack, defense, and specialAttack values
    Player(int health, int attack, int defense, int specialAttack)
        : name("Player"),  // Will be updated by setName
          health(health),   // Initializes health using the provided constructor argument
          attack(attack),   // Initializes attack power
          defense(defense), // Initializes defense points
          specialAttack(specialAttack),
          maxHealth(health),
          enemiesKilled(0)
    {
    } // Initializes special attack power

    // Method to set the player's name
    void setName(const std::string& playerName) {
        name = playerName;
    }

    //Funcion para saber donde se va curar el personaje
    void heal(int amount){
        //Si vida es mas o es igual al porcentaje maximo 
        health += amount;
        //Si vida es mayor a vida maxima vida sera igual a la vida maxima que tendra el player
        if (health > maxHealth)
        {
            health = maxHealth;
        }
        std::cout << "You cured " << amount << "HP. Current life: " << health << "/" << maxHealth << std::endl;
    }

    // Method to display the player's current stats in the console
    void showStats() const
    {
        std::cout << "Player: " << name
                  << " | Health: " << health
                  << " | Attack: " << attack
                  << " | Defense: " << defense
                  << " | Special: " << specialAttack 
                  << " | Enemies Killed: " << enemiesKilled << std::endl;

    }

    // Method to apply damage to the player based on incoming attack value
    void receiveDamage(int damage)
{
    if (damage <= 0)
        return;

    // Proportional mitigation based on defense:  
    // Reduced damage = damage * 100/(100 + defense)
    int mitigatedDamage = (damage * 100) / (100 + defense);

    health -= mitigatedDamage;

    std::cout << "Player received " << mitigatedDamage << " damage after mitigation." << std::endl;

    if (health < 0)
        health = 0;
}

    // Getter for player's current health
    int getHealth() const { return health; }

    // Getter for player's attack stat
    int getAttack() const { return attack; }

    // Getter for player's defense stat
    int getDefense() const { return defense; }

    // Getter for player's special attack stat
    int getSpecialAttack() const { return specialAttack; }

    // Getter for player's name
    std::string getName() const { return name; }

    //Getter para obtener el contador del mapa actual
    int getEnemiesKilled() const {return enemiesKilled;}

    //Se manda a llamar cada vez que el jugador derrota a un enemigo
    void addEnemyKill() {enemiesKilled++;}

    //Metodo para verificar si puede avanzar al siguiente mapa
    bool canAdvanceToNextMap(){return enemiesKilled >= 5;}

    //Metodo para cambiar de mapa (guarda contador actual y carga el del nuevo mapa)
    void changeToMap(int currentMapId, int newMapId) {
        // Guardar contador del mapa actual
        enemiesKilledPerMap[currentMapId] = enemiesKilled;
        // Cargar contador del nuevo mapa (0 si es la primera vez)
        enemiesKilled = enemiesKilledPerMap[newMapId];
    }
    
    //Metodo para reiniciar el contador al ingresar a un nuevo mapa (solo para compatibilidad)
    void resetEnemyCount() {enemiesKilled = 0;}
    
    //Metodo para establecer el contador de enemigos (usado al cargar partida)
    void setEnemiesKilled(int count) {enemiesKilled = count;}
    
    //Metodo para obtener el contador actual (usado al guardar partida)
    int getCurrentEnemiesKilled() const {return enemiesKilled;}
    
    //Metodo para obtener todos los contadores por mapa
    std::map<int, int> getEnemiesKilledPerMap() const {return enemiesKilledPerMap;}
    
    //Metodo para establecer todos los contadores por mapa (usado al cargar partida)
    void setEnemiesKilledPerMap(const std::map<int, int>& mapCounters) {enemiesKilledPerMap = mapCounters;}
};

#endif // End of header guard
