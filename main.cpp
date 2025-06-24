#include "src/map.h"
#include "src/unique_character.h"
#include "src/enemy_draw.h"
#include "src/Enemy.h"
#include "src/CombatScreen.h"
#include "src/Player.h"
#include "src/enemy_utils.h"
#include "src/configurationDifficulty.h"
using namespace std;



int main()
{

configurationDifficulty config = selectDifficult();

applyDifficultyEnemies(config);


Map map;
    chooseCharacterAndSave(); // El personaje se selecciona y se guarda

    Player player(100, 15, 3, 25);  // Stats de ejemplo
    Enemy enemy1 = enemy[11];       // Slime

    drawCombatScreen(map, player, enemy1); // Mostrar combate

    return 0;
}