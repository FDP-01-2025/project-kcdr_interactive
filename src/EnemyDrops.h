#ifndef ENEMY_DROPS_H
#define ENEMY_DROPS_H

#include "Enemy.h"
#include "Inventory.h"
#include "GameItems.h"

// ======== ENEMY DROP SYSTEM BY ZONES ========
// Zone-based drop system that matches the new enemy encounter zones:
// - Zone 0 (Town Center): Basic enemies (Slime, Goblin, Orc) - Low gold, basic items
// - Zone 1 (North District): Intermediate enemies (Wraith, Gremlin, Skeleton) - Medium gold, better items
// - Zone 2 (South District): Advanced enemies (Bat, Boar, Ghoul) - High gold, advanced items  
// - Zone 3 (East District): Elite enemies (Imp, Golem, Dragonling) - Very high gold, rare items

// Implementación de drops de enemigos
inline void Enemy::giveDropsToPlayer(Inventory& inventory, int& playerGold) const {
    std::cout << "\n=== " << name << " drops ===" << std::endl;
    
    // Oro siempre tiene probabilidad base
    int goldRoll = rand() % 100;
    if (goldRoll < 70) { // 70% de probabilidad de oro
        int goldAmount = 0;
        
        // Zona 0 (Town Center): Enemigos básicos - poco oro
        if (name == "Slime" || name == "Goblin" || name == "Orc") {
            goldAmount = 2 + rand() % 4; // 2-5 oro
        } 
        // Zona 1 (North District): Enemigos intermedios - oro medio
        else if (name == "Wraith" || name == "Gremlin" || name == "Skeleton") {
            goldAmount = 4 + rand() % 6; // 4-9 oro
        } 
        // Zona 2 (South District): Enemigos avanzados - oro alto
        else if (name == "Bat" || name == "Boar" || name == "Ghoul") {
            goldAmount = 6 + rand() % 8; // 6-13 oro
        } 
        // Zona 3 (East District): Enemigos élite - oro muy alto
        else if (name == "Imp" || name == "Golem" || name == "Dragonling") {
            goldAmount = 10 + rand() % 12; // 10-21 oro
        } 
        else {
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
    else if (name == "Orc") {
        // Orc: enemigo guerrero básico, drops armas y pociones
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
    // ======== ZONA 1 (NORTH DISTRICT): ENEMIGOS INTERMEDIOS ========
    else if (name == "Wraith") {
        // Wraith: espíritu etéreo, drops pociones especiales
        if (rand() % 100 < 20) { // 20% probabilidad
            std::cout << "Wraith dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
            gotItem = true;
        }
        if (rand() % 100 < 15) { // 15% probabilidad
            std::cout << "Wraith dropped healing herb tea!" << std::endl;
            inventory.addHealingItem(GameItems::herbTea);
            gotItem = true;
        }
        if (rand() % 100 < 10) { // 10% probabilidad
            std::cout << "Wraith dropped a shuriken!" << std::endl;
            inventory.addDamageItem(GameItems::shuriken);
            gotItem = true;
        }
    } 
    else if (name == "Gremlin") {
        // Gremlin: criatura traviesa, drops armas improvisadas
        if (rand() % 100 < 25) { // 25% probabilidad
            std::cout << "Gremlin dropped a throwing knife!" << std::endl;
            inventory.addDamageItem(GameItems::throwingKnife);
            gotItem = true;
        }
        if (rand() % 100 < 18) { // 18% probabilidad
            std::cout << "Gremlin dropped some bread!" << std::endl;
            inventory.addHealingItem(GameItems::bread);
            gotItem = true;
        }
        if (rand() % 100 < 12) { // 12% probabilidad
            std::cout << "Gremlin dropped a small health potion!" << std::endl;
            inventory.addHealingItem(GameItems::smallPotion);
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
    // ======== ZONA 2 (SOUTH DISTRICT): ENEMIGOS AVANZADOS ========
    else if (name == "Bat") {
        // Bat: criatura voladora, drops ágiles y rápidos
        if (rand() % 100 < 22) { // 22% probabilidad
            std::cout << "Bat dropped a shuriken!" << std::endl;
            inventory.addDamageItem(GameItems::shuriken);
            gotItem = true;
        }
        if (rand() % 100 < 18) { // 18% probabilidad
            std::cout << "Bat dropped an apple!" << std::endl;
            inventory.addHealingItem(GameItems::apple);
            gotItem = true;
        }
        if (rand() % 100 < 10) { // 10% probabilidad
            std::cout << "Bat dropped a throwing knife!" << std::endl;
            inventory.addDamageItem(GameItems::throwingKnife);
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
    // ======== ZONA 3 (EAST DISTRICT): ENEMIGOS ÉLITE ========
    else if (name == "Imp") {
        // Imp: demonio menor, drops mágicos
        if (rand() % 100 < 20) { // 20% probabilidad
            std::cout << "Imp dropped a fire orb!" << std::endl;
            inventory.addDamageItem(GameItems::fireball);
            gotItem = true;
        }
        if (rand() % 100 < 15) { // 15% probabilidad
            std::cout << "Imp dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
            gotItem = true;
        }
        if (rand() % 100 < 12) { // 12% probabilidad
            std::cout << "Imp dropped a grenade!" << std::endl;
            inventory.addDamageItem(GameItems::grenade);
            gotItem = true;
        }
    } 
    else if (name == "Golem") {
        // Golem: constructor de piedra, drops poderosos
        if (rand() % 100 < 18) { // 18% probabilidad
            std::cout << "Golem dropped a javelin!" << std::endl;
            inventory.addDamageItem(GameItems::javelin);
            gotItem = true;
        }
        if (rand() % 100 < 15) { // 15% probabilidad
            std::cout << "Golem dropped a grenade!" << std::endl;
            inventory.addDamageItem(GameItems::grenade);
            gotItem = true;
        }
        if (rand() % 100 < 12) { // 12% probabilidad
            std::cout << "Golem dropped healing herb tea!" << std::endl;
            inventory.addHealingItem(GameItems::herbTea);
            gotItem = true;
        }
        if (rand() % 100 < 8) { // 8% probabilidad
            std::cout << "Golem dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
            gotItem = true;
        }
    } 
    else if (name == "Dragonling") {
        // Dragonling: dragón joven, drops legendarios
        if (rand() % 100 < 25) { // 25% probabilidad alta
            std::cout << "Dragonling dropped a fire orb!" << std::endl;
            inventory.addDamageItem(GameItems::fireball);
            gotItem = true;
        }
        if (rand() % 100 < 20) { // 20% probabilidad
            std::cout << "Dragonling dropped a javelin!" << std::endl;
            inventory.addDamageItem(GameItems::javelin);
            gotItem = true;
        }
        if (rand() % 100 < 15) { // 15% probabilidad
            std::cout << "Dragonling dropped healing herb tea!" << std::endl;
            inventory.addHealingItem(GameItems::herbTea);
            gotItem = true;
        }
        if (rand() % 100 < 12) { // 12% probabilidad
            std::cout << "Dragonling dropped a grenade!" << std::endl;
            inventory.addDamageItem(GameItems::grenade);
            gotItem = true;
        }
        if (rand() % 100 < 5) { // 5% probabilidad (muy raro)
            std::cout << "Dragonling dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
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
