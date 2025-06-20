#include "src/map.h"
#include "src/unique_character.h"
#include "src/enemy_draw.h"
#include "src/Enemy.h"
#include "src/CombatScreen.h"
#include "src/Player.h"

int main() {
    Map map;
    chooseCharacterAndSave(); // El personaje se selecciona y se guarda

    Player player(100, 15, 3, 25);  // Stats de ejemplo
    Enemy enemy1 = enemy[1];       // Slime

    drawCombatScreen(map, player, enemy1); // Mostrar combate

    return 0;
}
