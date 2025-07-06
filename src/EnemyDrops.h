#ifndef ENEMY_DROPS_H
#define ENEMY_DROPS_H

#include "Enemy.h"
#include "Inventory.h"
#include "GameItems.h"

// Implementación de drops de enemigos
inline void Enemy::giveDropsToPlayer(Inventory& inventory, int& playerGold) const {
    std::cout << "\n=== " << name << " drops ===" << std::endl;
    
    // Oro siempre tiene probabilidad base
    int goldRoll = rand() % 100;
    if (goldRoll < 70) { // 70% de probabilidad de oro
        int goldAmount = 0;
        if (name == "Wolf" || name == "Goblin" || name == "Slime") {
            goldAmount = 2 + rand() % 4; // 2-5 oro (enemigos débiles)
        } else if (name == "Orc" || name == "Skeleton") {
            goldAmount = 4 + rand() % 6; // 4-9 oro (enemigos medios)
        } else if (name == "Boar" || name == "Ghoul") {
            goldAmount = 6 + rand() % 8; // 6-13 oro (enemigos fuertes)
        } else {
            goldAmount = 3 + rand() % 5; // 3-7 oro por defecto
        }
        
        playerGold += goldAmount;
        std::cout << "Found " << goldAmount << " gold coins!" << std::endl;
    }
    
    // Sistema de drops específicos por enemigo
    bool gotItem = false;
    
    if (name == "Slime") {
        // Slime: enemigo básico, drops básicos
        if (rand() % 100 < 20) { // 20% probabilidad
            std::cout << "Slime dropped an apple!" << std::endl;
            inventory.addHealingItem(GameItems::apple);
            gotItem = true;
        }
    } 
    else if (name == "Goblin") {
        // Goblin: drops comida y objetos básicos
        if (rand() % 100 < 25) { // 25% probabilidad
            std::cout << "Goblin dropped some bread!" << std::endl;
            inventory.addHealingItem(GameItems::bread);
            gotItem = true;
        }
        if (rand() % 100 < 15) { // 15% probabilidad
            std::cout << "Goblin dropped a small health potion!" << std::endl;
            inventory.addHealingItem(GameItems::smallPotion);
            gotItem = true;
        }
    } 
    else if (name == "Wolf") {
        // Wolf: drops carne y armas básicas
        if (rand() % 100 < 30) { // 30% probabilidad
            std::cout << "Wolf dropped cooked meat!" << std::endl;
            inventory.addHealingItem(GameItems::meat);
            gotItem = true;
        }
        if (rand() % 100 < 12) { // 12% probabilidad
            std::cout << "Wolf dropped a throwing knife!" << std::endl;
            inventory.addDamageItem(GameItems::throwingKnife);
            gotItem = true;
        }
    } 
    else if (name == "Orc") {
        // Orc: enemigo guerrero, drops armas y pociones
        if (rand() % 100 < 18) { // 18% probabilidad
            std::cout << "Orc dropped a throwing knife!" << std::endl;
            inventory.addDamageItem(GameItems::throwingKnife);
            gotItem = true;
        }
        if (rand() % 100 < 15) { // 15% probabilidad
            std::cout << "Orc dropped a small health potion!" << std::endl;
            inventory.addHealingItem(GameItems::smallPotion);
            gotItem = true;
        }
        if (rand() % 100 < 8) { // 8% probabilidad
            std::cout << "Orc dropped a shuriken!" << std::endl;
            inventory.addDamageItem(GameItems::shuriken);
            gotItem = true;
        }
    } 
    else if (name == "Skeleton") {
        // Skeleton: no-muerto, drops pociones y armas mejoradas
        if (rand() % 100 < 12) { // 12% probabilidad
            std::cout << "Skeleton dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
            gotItem = true;
        }
        if (rand() % 100 < 15) { // 15% probabilidad
            std::cout << "Skeleton dropped a shuriken!" << std::endl;
            inventory.addDamageItem(GameItems::shuriken);
            gotItem = true;
        }
        if (rand() % 100 < 5) { // 5% probabilidad (raro)
            std::cout << "Skeleton dropped healing herb tea!" << std::endl;
            inventory.addHealingItem(GameItems::herbTea);
            gotItem = true;
        }
    } 
    else if (name == "Boar") {
        // Boar: bestia, drops mucha comida
        if (rand() % 100 < 35) { // 35% probabilidad alta
            std::cout << "Boar dropped cooked meat!" << std::endl;
            inventory.addHealingItem(GameItems::meat);
            gotItem = true;
        }
        if (rand() % 100 < 20) { // 20% probabilidad
            std::cout << "Boar dropped a small health potion!" << std::endl;
            inventory.addHealingItem(GameItems::smallPotion);
            gotItem = true;
        }
        if (rand() % 100 < 10) { // 10% probabilidad
            std::cout << "Boar dropped bread!" << std::endl;
            inventory.addHealingItem(GameItems::bread);
            gotItem = true;
        }
    } 
    else if (name == "Ghoul") {
        // Ghoul: enemigo fuerte, drops armas poderosas
        if (rand() % 100 < 15) { // 15% probabilidad
            std::cout << "Ghoul dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
            gotItem = true;
        }
        if (rand() % 100 < 12) { // 12% probabilidad
            std::cout << "Ghoul dropped a grenade!" << std::endl;
            inventory.addDamageItem(GameItems::grenade);
            gotItem = true;
        }
        if (rand() % 100 < 8) { // 8% probabilidad
            std::cout << "Ghoul dropped a javelin!" << std::endl;
            inventory.addDamageItem(GameItems::javelin);
            gotItem = true;
        }
        if (rand() % 100 < 3) { // 3% probabilidad (muy raro)
            std::cout << "Ghoul dropped a fire orb!" << std::endl;
            inventory.addDamageItem(GameItems::fireball);
            gotItem = true;
        }
    }
    // Continúa para otros enemigos...
    
    if (!gotItem) {
        std::cout << "No items dropped this time." << std::endl;
    }
    
    std::cout << "Current Gold: " << playerGold << std::endl;
    std::cout << "=== End of drops ===" << std::endl;
}

#endif // ENEMY_DROPS_H
