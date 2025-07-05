#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include "GameItems.h"
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
        inventory.addHealingItem(GameItems::smallPotion);
        inventory.addDamageItem(GameItems::throwingKnife);
        std::cout << "Starter pack received!" << std::endl;
    }
    
    static void giveStarterGold(int& playerGold) {
        playerGold += 50;  // Oro inicial para poder comprar algunas cosas
        std::cout << "\n=== Starting Gold ===" << std::endl;
        std::cout << "You start your adventure with 50 gold coins!" << std::endl;
        std::cout << "Current Gold: " << playerGold << std::endl;
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
    
    // ==================== SHOP ITEMS ====================
    
    static void showShopItems() {
        std::cout << "\n=== SHOP ITEMS ===" << std::endl;
        std::cout << "1. Small Health Potion (25 HP) - 10 Gold" << std::endl;
        std::cout << "2. Medium Health Potion (50 HP) - 25 Gold" << std::endl;
        std::cout << "3. Throwing Knife (15 DMG) - 15 Gold" << std::endl;
        std::cout << "4. Grenade (45 DMG) - 40 Gold" << std::endl;
        std::cout << "5. Magic Elixir (150 HP) - 100 Gold" << std::endl;
        std::cout << "6. Lightning Bolt (100 DMG) - 150 Gold" << std::endl;
    }
    
    static bool buyItem(int choice, Inventory& inventory, int& playerGold) {
        switch (choice) {
            case 1:
                if (playerGold >= 10) {
                    playerGold -= 10;
                    inventory.addHealingItem(GameItems::smallPotion);
                    return true;
                }
                break;
            case 2:
                if (playerGold >= 25) {
                    playerGold -= 25;
                    inventory.addHealingItem(GameItems::mediumPotion);
                    return true;
                }
                break;
            case 3:
                if (playerGold >= 15) {
                    playerGold -= 15;
                    inventory.addDamageItem(GameItems::throwingKnife);
                    return true;
                }
                break;
            case 4:
                if (playerGold >= 40) {
                    playerGold -= 40;
                    inventory.addDamageItem(GameItems::grenade);
                    return true;
                }
                break;
            case 5:
                if (playerGold >= 100) {
                    playerGold -= 100;
                    inventory.addHealingItem(GameItems::magicElixir);
                    return true;
                }
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
                return false;
        }
        std::cout << "Not enough gold!" << std::endl;
        return false;
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
