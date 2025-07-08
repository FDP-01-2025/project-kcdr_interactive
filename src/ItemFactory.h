#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include "gameItems.h"
#include "Inventory.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

class ItemFactory {
public:
    // ==================== INITIALIZATION ====================
    
    static void initializeRandomSeed() {
        srand(time(nullptr));  // Initializes the random number generator
    }
    
    // ==================== STARTER PACK ====================
    
    static void giveStarterItems(Inventory& inventory) {
        std::cout << "\n=== Receiving Starter Pack ===" << std::endl;
        
        // Give small potions
        int smallPotionsToGive = 2;  // Change this number to give more or fewer potions
        for (int i = 0; i < smallPotionsToGive; i++) {
            inventory.addHealingItem(GameItems::smallPotion);
        }
        
        // Give throwing knives
        int knivesToGive = 3;  // Change this number to give more or fewer knives
        for (int i = 0; i < knivesToGive; i++) {
            inventory.addDamageItem(GameItems::throwingKnife);
        }
        
        std::cout << "Starter pack received!" << std::endl;
        std::cout << "- " << smallPotionsToGive << " Small Health Potions" << std::endl;
        std::cout << "- " << knivesToGive << " Throwing Knives" << std::endl;
    }
    
    static void giveStarterGold(int& playerGold) {
        playerGold += 100;  // Initial gold to buy some things
        std::cout << "\n=== Starting Gold ===" << std::endl;
        std::cout << "You start your adventure with 100 gold coins!" << std::endl;
        std::cout << "Current Gold: " << playerGold << std::endl;
    }
    
    // ==================== COMPLETE PLAYER INITIALIZATION ====================
    
    static void initializeNewPlayer(Inventory& inventory, int& playerGold) {
        std::cout << "\n=== Initializing New Player ===" << std::endl;
        
        // Initialize gold to 0 first (clean slate)
        playerGold = 0;
        
        // Give starter items and gold
        giveStarterItems(inventory);
        giveStarterGold(playerGold);
        
        std::cout << "Player initialization complete!" << std::endl;
        std::cout << "===================================\n" << std::endl;
    }
    
    // ==================== REWARD PACKS ====================
    
    static void giveBattleReward(Inventory& inventory, int& playerGold) {
        std::cout << "\n=== Checking for battle rewards... ===" << std::endl;
        
        bool gotReward = false;
        
        // ==================== GOLD REWARDS ====================
        // 60% chance to get gold (more common than items)
        if (rand() % 100 < 60) {
            int goldAmount = 0;
            int goldRoll = rand() % 100;
            
            if (goldRoll < 30) {        // 30% - Little gold (3-7)
                goldAmount = 3 + rand() % 5;
                std::cout << "Found " << goldAmount << " gold coins!" << std::endl;
            } else if (goldRoll < 20) { // 20% - Moderate gold (8-15)
                goldAmount = 8 + rand() % 8;
                std::cout << "Nice! Found " << goldAmount << " gold coins!" << std::endl;
            } else if (goldRoll < 8) {  // 8% - Good gold (16-25)
                goldAmount = 16 + rand() % 10;
                std::cout << "Great! Found " << goldAmount << " gold coins!" << std::endl;
            } else {                    // 2% - Lots of gold (26-40)
                goldAmount = 26 + rand() % 15;
                std::cout << "JACKPOT! Found " << goldAmount << " gold coins!" << std::endl;
            }
            
            playerGold += goldAmount;
            gotReward = true;
        }
        
        // ==================== ITEM REWARDS ====================
        // 15% chance to get Small Health Potion
        if (rand() % 100 < 15) {
            inventory.addHealingItem(GameItems::smallPotion);
            std::cout << "Lucky! Found a Small Health Potion!" << std::endl;
            gotReward = true;
        }
        
        // 8% chance to get Bread
        if (rand() % 100 < 8) {
            inventory.addHealingItem(GameItems::bread);
            std::cout << "Found some Bread!" << std::endl;
            gotReward = true;
        }
        
        // 5% chance to get Throwing Knife
        if (rand() % 100 < 5) {
            inventory.addDamageItem(GameItems::throwingKnife);
            std::cout << "Found a Throwing Knife!" << std::endl;
            gotReward = true;
        }
        
        // 2% chance to get something special (Medium Potion or Shuriken)
        if (rand() % 100 < 2) {
            if (rand() % 2 == 0) {
                inventory.addHealingItem(GameItems::mediumPotion);
                std::cout << "Rare find! Medium Health Potion discovered!" << std::endl;
            } else {
                inventory.addDamageItem(GameItems::shuriken);
                std::cout << "Rare find! Shuriken discovered!" << std::endl;
            }
            gotReward = true;
        }
        
        // 1% chance to get something very rare
        if (rand() % 100 < 1) {
            inventory.addHealingItem(GameItems::largePotion);
            std::cout << "VERY RARE! Large Health Potion found!" << std::endl;
            gotReward = true;
        }
        
        if (!gotReward) {
            std::cout << "No rewards found this time. Better luck next battle!" << std::endl;
        }
        
        std::cout << "Current Gold: " << playerGold << std::endl;
        std::cout << "=== End of reward check ===" << std::endl;
    }
    
    // ==================== RANDOM DROPS ====================
    
    static void giveRandomDrop(Inventory& inventory) {
        int randomChoice = rand() % 4;
        std::cout << "\n=== Random Item Found! ===" << std::endl;
        
        switch (randomChoice) {
            case 0:
                inventory.addHealingItem(GameItems::apple);
                break;
            case 1:
                inventory.addHealingItem(GameItems::bread);
                break;
            case 2:
                inventory.addDamageItem(GameItems::shuriken);
                break;
        }
    }
};

#endif // ITEM_FACTORY_H
