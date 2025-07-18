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
int playerGold = 0;  // Will be initialized by ItemFactory
Inventory playerInventory;

int main()
{
    // Initialize new player with starter items and gold
    ItemFactory::initializeNewPlayer(playerInventory, playerGold);
    
    GameMenu::displayTitleScreen();  // Epic title screen
    GameMenu::displayMainMenu();     // Complete main menu
    return 0;
}