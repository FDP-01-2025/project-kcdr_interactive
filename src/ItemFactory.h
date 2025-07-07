#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include "gameItems.h"
#include "Inventory.h"
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()

class ItemFactory {
public:
    // ==================== INICIALIZACIÓN ====================
    
    static void initializeRandomSeed() {
        srand(time(nullptr));  // Inicializa el generador de números aleatorios
    }
    
    // ==================== STARTER PACK ====================
    
    static void giveStarterItems(Inventory& inventory) {
        std::cout << "\n=== Receiving Starter Pack ===" << std::endl;
        
        // Dar pociones pequeñas 
        int smallPotionsToGive = 2;  // Cambiar este número para dar más o menos pociones
        for (int i = 0; i < smallPotionsToGive; i++) {
            inventory.addHealingItem(GameItems::smallPotion);
        }
        
        // Dar cuchillos arrojadizos 
        int knivesToGive = 3;  // Cambiar este número para dar más o menos cuchillos
        for (int i = 0; i < knivesToGive; i++) {
            inventory.addDamageItem(GameItems::throwingKnife);
        }
        
        std::cout << "Starter pack received!" << std::endl;
        std::cout << "- " << smallPotionsToGive << " Small Health Potions" << std::endl;
        std::cout << "- " << knivesToGive << " Throwing Knives" << std::endl;
    }
    
    static void giveStarterGold(int& playerGold) {
        playerGold += 100;  // Oro inicial para poder comprar algunas cosas
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
        
        // ==================== RECOMPENSAS DE ORO ====================
        // 60% de probabilidad de conseguir oro (más común que items)
        if (rand() % 100 < 60) {
            int goldAmount = 0;
            int goldRoll = rand() % 100;
            
            if (goldRoll < 30) {        // 30% - Poco oro (3-7)
                goldAmount = 3 + rand() % 5;
                std::cout << "Found " << goldAmount << " gold coins!" << std::endl;
            } else if (goldRoll < 20) { // 20% - Oro moderado (8-15)
                goldAmount = 8 + rand() % 8;
                std::cout << "Nice! Found " << goldAmount << " gold coins!" << std::endl;
            } else if (goldRoll < 8) {  // 8% - Buen oro (16-25)
                goldAmount = 16 + rand() % 10;
                std::cout << "Great! Found " << goldAmount << " gold coins!" << std::endl;
            } else {                    // 2% - Mucho oro (26-40)
                goldAmount = 26 + rand() % 15;
                std::cout << "JACKPOT! Found " << goldAmount << " gold coins!" << std::endl;
            }
            
            playerGold += goldAmount;
            gotReward = true;
        }
        
        // ==================== RECOMPENSAS DE ITEMS ====================
        // 15% de probabilidad de conseguir Small Health Potion
        if (rand() % 100 < 15) {
            inventory.addHealingItem(GameItems::smallPotion);
            std::cout << "Lucky! Found a Small Health Potion!" << std::endl;
            gotReward = true;
        }
        
        // 8% de probabilidad de conseguir Bread
        if (rand() % 100 < 8) {
            inventory.addHealingItem(GameItems::bread);
            std::cout << "Found some Bread!" << std::endl;
            gotReward = true;
        }
        
        // 5% de probabilidad de conseguir Throwing Knife
        if (rand() % 100 < 5) {
            inventory.addDamageItem(GameItems::throwingKnife);
            std::cout << "Found a Throwing Knife!" << std::endl;
            gotReward = true;
        }
        
        // 2% de probabilidad de conseguir algo especial (Medium Potion o Shuriken)
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
        
        // 1% de probabilidad de conseguir algo muy raro
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
