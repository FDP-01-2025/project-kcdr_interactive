#include "src/map.h"
#include "src/unique_character.h"
#include "src/enemy_draw.h"
#include "src/Enemy.h"
#include "src/CombatScreen.h"
#include "src/Player.h"
#include "src/enemy_utils.h"
#include "src/configurationDifficulty.h"
#include "src/Boss.h"
#include "src/BossDraw.h"
#include "src/GameMenu.h"
#include "src/SaveSystem.h"

using namespace std;

int main()
{
    GameMenu::displayTitleScreen();  // Epic title screen
    GameMenu::displayMainMenu();     // Complete main menu
    return 0;
}