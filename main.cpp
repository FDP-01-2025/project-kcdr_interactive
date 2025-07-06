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
#include "src/Inventory.h"
#include "src/ItemFactory.h"
#include "src/EnemyDrops.h"  // Include enemy drops implementation

using namespace std;

// Global variables for player inventory and gold
int playerGold = 100;  // Starting gold
Inventory playerInventory;

int main()
{
    // Initialize player with starter items and additional gold
    ItemFactory::giveStarterItems(playerInventory);
    ItemFactory::giveStarterGold(playerGold);
    
    GameMenu::displayTitleScreen();  // Epic title screen
    GameMenu::displayMainMenu();     // Complete main menu
    return 0;
}