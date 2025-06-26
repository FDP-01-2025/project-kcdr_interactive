#include <iostream>
#include "src/map.h"
#include "src/unique_character.h"
#include "src/enemy_draw.h"
#include "src/Enemy.h"
#include "src/CombatScreen.h"
#include "src/Player.h"
#include "src/combat_system.h"  // Aquí está la lógica de combate

int main() {
    Map map;

    chooseCharacterAndSave(); // El personaje queda guardado en playerSelected

    Enemy enemy1 = enemy[11]; // Ejemplo: Slime

    bool playerAlive = Combat(playerSelected, enemy1, map);

    if (playerAlive) {
        std::cout << "You survived the battle! Continue exploring the map...\n";
        // Aquí la lógica para seguir recorriendo el mapa
    } else {
        std::cout << "Game Over. Try again.\n";
        // Aquí la lógica para reiniciar o terminar
    }

    return 0;
}
