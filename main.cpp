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
    chooseCharacterAndSave();
    playGame();
    
    return 0;
}