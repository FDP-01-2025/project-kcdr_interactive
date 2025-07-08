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

// Enemy drop implementation
inline void Enemy::giveDropsToPlayer(Inventory &inventory, int &playerGold) const
{
    std::cout << "\n=== " << name << " drops ===" << std::endl;

    // Gold always has a base probability
    int goldRoll = rand() % 100;
    if (goldRoll < 70)
    { // 70% chance for gold
        int goldAmount = 0;

        // Zone 0 (Town Center): Basic enemies - low gold
        if (name == "Slime" || name == "Goblin" || name == "Orc")
        {
            goldAmount = 2 + rand() % 4; // 2-5 gold
        }
        // Zone 1 (North District): Intermediate enemies - medium gold
        else if (name == "Wraith" || name == "Gremlin" || name == "Skeleton")
        {
            goldAmount = 4 + rand() % 6; // 4-9 gold
        }
        // Zone 2 (South District): Advanced enemies - high gold
        else if (name == "Bat" || name == "Boar" || name == "Ghoul")
        {
            goldAmount = 6 + rand() % 8; // 6-13 gold
        }
        // Zone 3 (East District): Elite enemies - very high gold
        else if (name == "Imp" || name == "Golem" || name == "Dragonling")
        {
            goldAmount = 10 + rand() % 12; // 10-21 gold
        }
        else
        {
            goldAmount = 3 + rand() % 5; // 3-7 gold by default
        }

        playerGold += goldAmount;
        std::cout << "Found " << goldAmount << " gold coins!" << std::endl;
    }

    // Specific drop system by enemy
    bool gotItem = false;

    if (name == "Slime")
    {
        // Slime: basic enemy, basic drops
        if (rand() % 100 < 20)
        { // 20% chance
            std::cout << "Slime dropped an apple!" << std::endl;
            inventory.addHealingItem(GameItems::apple);
            gotItem = true;
        }
    }
    else if (name == "Goblin")
    {
        // Goblin: drops food and basic items
        if (rand() % 100 < 25)
        { // 25% chance
            std::cout << "Goblin dropped some bread!" << std::endl;
            inventory.addHealingItem(GameItems::bread);
            gotItem = true;
        }
        if (rand() % 100 < 15)
        { // 15% chance
            std::cout << "Goblin dropped a small health potion!" << std::endl;
            inventory.addHealingItem(GameItems::smallPotion);
            gotItem = true;
        }
    }
    else if (name == "Orc")
    {
        // Orc: basic warrior enemy, drops weapons and potions
        if (rand() % 100 < 18)
        { // 18% chance
            std::cout << "Orc dropped a throwing knife!" << std::endl;
            inventory.addDamageItem(GameItems::throwingKnife);
            gotItem = true;
        }
        if (rand() % 100 < 15)
        { // 15% chance
            std::cout << "Orc dropped a small health potion!" << std::endl;
            inventory.addHealingItem(GameItems::smallPotion);
            gotItem = true;
        }
        if (rand() % 100 < 8)
        { // 8% chance
            std::cout << "Orc dropped a shuriken!" << std::endl;
            inventory.addDamageItem(GameItems::shuriken);
            gotItem = true;
        }
    }
    // ======== ZONE 1 (NORTH DISTRICT): INTERMEDIATE ENEMIES ========
    else if (name == "Wraith")
    {
        // Wraith: ethereal spirit, drops special potions
        if (rand() % 100 < 20)
        { // 20% chance
            std::cout << "Wraith dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
            gotItem = true;
        }
        if (rand() % 100 < 15)
        { // 15% chance
            std::cout << "Wraith dropped healing herb tea!" << std::endl;
            inventory.addHealingItem(GameItems::herbTea);
            gotItem = true;
        }
        if (rand() % 100 < 10)
        { // 10% chance
            std::cout << "Wraith dropped a shuriken!" << std::endl;
            inventory.addDamageItem(GameItems::shuriken);
            gotItem = true;
        }
    }
    else if (name == "Gremlin")
    {
        // Gremlin: mischievous creature, drops improvised weapons
        if (rand() % 100 < 25)
        { // 25% chance
            std::cout << "Gremlin dropped a throwing knife!" << std::endl;
            inventory.addDamageItem(GameItems::throwingKnife);
            gotItem = true;
        }
        if (rand() % 100 < 18)
        { // 18% chance
            std::cout << "Gremlin dropped some bread!" << std::endl;
            inventory.addHealingItem(GameItems::bread);
            gotItem = true;
        }
        if (rand() % 100 < 12)
        { // 12% chance
            std::cout << "Gremlin dropped a small health potion!" << std::endl;
            inventory.addHealingItem(GameItems::smallPotion);
            gotItem = true;
        }
    }
    else if (name == "Skeleton")
    {
        // Skeleton: undead, drops improved potions and weapons
        if (rand() % 100 < 12)
        { // 12% chance
            std::cout << "Skeleton dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
            gotItem = true;
        }
        if (rand() % 100 < 15)
        { // 15% chance
            std::cout << "Skeleton dropped a shuriken!" << std::endl;
            inventory.addDamageItem(GameItems::shuriken);
            gotItem = true;
        }
        if (rand() % 100 < 5)
        { // 5% chance (rare)
            std::cout << "Skeleton dropped healing herb tea!" << std::endl;
            inventory.addHealingItem(GameItems::herbTea);
            gotItem = true;
        }
    }
    // ======== ZONE 2 (SOUTH DISTRICT): ADVANCED ENEMIES ========
    else if (name == "Bat")
    {
        // Bat: flying creature, agile and fast drops
        if (rand() % 100 < 22)
        { // 22% chance
            std::cout << "Bat dropped a shuriken!" << std::endl;
            inventory.addDamageItem(GameItems::shuriken);
            gotItem = true;
        }
        if (rand() % 100 < 18)
        { // 18% chance
            std::cout << "Bat dropped an apple!" << std::endl;
            inventory.addHealingItem(GameItems::apple);
            gotItem = true;
        }
        if (rand() % 100 < 10)
        { // 10% chance
            std::cout << "Bat dropped a throwing knife!" << std::endl;
            inventory.addDamageItem(GameItems::throwingKnife);
            gotItem = true;
        }
    }
    else if (name == "Boar")
    {
        // Boar: beast, drops a lot of food
        if (rand() % 100 < 35)
        { // 35% high chance
            std::cout << "Boar dropped cooked meat!" << std::endl;
            inventory.addHealingItem(GameItems::meat);
            gotItem = true;
        }
        if (rand() % 100 < 20)
        { // 20% chance
            std::cout << "Boar dropped a small health potion!" << std::endl;
            inventory.addHealingItem(GameItems::smallPotion);
            gotItem = true;
        }
        if (rand() % 100 < 10)
        { // 10% chance
            std::cout << "Boar dropped bread!" << std::endl;
            inventory.addHealingItem(GameItems::bread);
            gotItem = true;
        }
    }
    else if (name == "Ghoul")
    {
        // Ghoul: strong enemy, drops powerful weapons
        if (rand() % 100 < 15)
        { // 15% chance
            std::cout << "Ghoul dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
            gotItem = true;
        }
        if (rand() % 100 < 12)
        { // 12% chance
            std::cout << "Ghoul dropped a grenade!" << std::endl;
            inventory.addDamageItem(GameItems::grenade);
            gotItem = true;
        }
        if (rand() % 100 < 8)
        { // 8% chance
            std::cout << "Ghoul dropped a javelin!" << std::endl;
            inventory.addDamageItem(GameItems::javelin);
            gotItem = true;
        }
        if (rand() % 100 < 3)
        { // 3% chance (very rare)
            std::cout << "Ghoul dropped a fire orb!" << std::endl;
            inventory.addDamageItem(GameItems::fireball);
            gotItem = true;
        }
    }
    // ======== ZONE 3 (EAST DISTRICT): ELITE ENEMIES ========
    else if (name == "Imp")
    {
        // Imp: minor demon, magic drops
        if (rand() % 100 < 20)
        { // 20% chance
            std::cout << "Imp dropped a fire orb!" << std::endl;
            inventory.addDamageItem(GameItems::fireball);
            gotItem = true;
        }
        if (rand() % 100 < 15)
        { // 15% chance
            std::cout << "Imp dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
            gotItem = true;
        }
        if (rand() % 100 < 12)
        { // 12% chance
            std::cout << "Imp dropped a grenade!" << std::endl;
            inventory.addDamageItem(GameItems::grenade);
            gotItem = true;
        }
    }
    else if (name == "Golem")
    {
        // Golem: stone builder, powerful drops
        if (rand() % 100 < 18)
        { // 18% chance
            std::cout << "Golem dropped a javelin!" << std::endl;
            inventory.addDamageItem(GameItems::javelin);
            gotItem = true;
        }
        if (rand() % 100 < 15)
        { // 15% chance
            std::cout << "Golem dropped a grenade!" << std::endl;
            inventory.addDamageItem(GameItems::grenade);
            gotItem = true;
        }
        if (rand() % 100 < 12)
        { // 12% chance
            std::cout << "Golem dropped healing herb tea!" << std::endl;
            inventory.addHealingItem(GameItems::herbTea);
            gotItem = true;
        }
        if (rand() % 100 < 8)
        { // 8% chance
            std::cout << "Golem dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
            gotItem = true;
        }
    }
    else if (name == "Dragonling")
    {
        // Dragonling: young dragon, legendary drops
        if (rand() % 100 < 25)
        { // 25% high chance
            std::cout << "Dragonling dropped a fire orb!" << std::endl;
            inventory.addDamageItem(GameItems::fireball);
            gotItem = true;
        }
        if (rand() % 100 < 20)
        { // 20% chance
            std::cout << "Dragonling dropped a javelin!" << std::endl;
            inventory.addDamageItem(GameItems::javelin);
            gotItem = true;
        }
        if (rand() % 100 < 15)
        { // 15% chance
            std::cout << "Dragonling dropped healing herb tea!" << std::endl;
            inventory.addHealingItem(GameItems::herbTea);
            gotItem = true;
        }
        if (rand() % 100 < 12)
        { // 12% chance
            std::cout << "Dragonling dropped a grenade!" << std::endl;
            inventory.addDamageItem(GameItems::grenade);
            gotItem = true;
        }
        if (rand() % 100 < 5)
        { // 5% chance (very rare)
            std::cout << "Dragonling dropped a medium health potion!" << std::endl;
            inventory.addHealingItem(GameItems::mediumPotion);
            gotItem = true;
        }
    }
    // Continue for other enemies...

    if (!gotItem)
    {
        std::cout << "No items dropped this time." << std::endl;
    }

    std::cout << "Current Gold: " << playerGold << std::endl;
    std::cout << "=== End of drops ===" << std::endl;
}

#endif // ENEMY_DROPS_H
