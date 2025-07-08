#ifndef GAME_ITEMS_H
#define GAME_ITEMS_H

#include "item.h"

namespace GameItems
{

    // ==================== HEALING ITEMS ====================

    // Basic potions
    static HealingItem smallPotion("Small Health Potion", 25, 1);
    static HealingItem mediumPotion("Medium Health Potion", 50, 1);
    static HealingItem largePotion("Large Health Potion", 100, 1);

    // Food
    static HealingItem bread("Bread", 15, 1);
    static HealingItem apple("Red Apple", 10, 1);
    static HealingItem meat("Cooked Meat", 35, 1);

    // Special healing items
    static HealingItem magicElixir("Magic Elixir", 150, 1);
    static HealingItem herbTea("Healing Herb Tea", 20, 1);

    // ==================== DAMAGE ITEMS ====================

    // Basic projectiles
    static DamageItem throwingKnife("Throwing Knife", 15, 1);
    static DamageItem shuriken("Shuriken", 20, 1);
    static DamageItem javelin("Javelin", 35, 1);

    // Explosives
    static DamageItem bomb("Explosive Bomb", 60, 1);
    static DamageItem grenade("Grenade", 45, 1);
    static DamageItem fireball("Fire Orb", 70, 1);
    static DamageItem lightningBolt("Lightning Bolt", 100, 1);

}

#endif // GAME_ITEMS_H
