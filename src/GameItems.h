#ifndef GAME_ITEMS_H
#define GAME_ITEMS_H

#include "Item.h"

namespace GameItems {
    
    // ==================== ITEMS DE CURACIÓN ====================
    
    // Pociones básicas
    static HealingItem smallPotion("Small Health Potion", 25, 5);
    static HealingItem mediumPotion("Medium Health Potion", 50, 3);
    static HealingItem largePotion("Large Health Potion", 100, 1);
    
    // Comidas
    static HealingItem bread("Bread", 15, 10);
    static HealingItem apple("Red Apple", 10, 8);
    static HealingItem meat("Cooked Meat", 35, 4);
    
    // Items especiales de curación
    static HealingItem magicElixir("Magic Elixir", 150, 1);
    static HealingItem herbTea("Healing Herb Tea", 20, 6);
    
    // ==================== ITEMS DE DAÑO ====================
    
    // Proyectiles básicos
    static DamageItem throwingKnife("Throwing Knife", 15, 8);
    static DamageItem shuriken("Shuriken", 20, 6);
    static DamageItem javelin("Javelin", 35, 3);
    
    // Explosivos
    static DamageItem bomb("Explosive Bomb", 60, 2);
    static DamageItem grenade("Grenade", 45, 4);
    static DamageItem fireball("Fire Orb", 70, 1);
    
}

#endif // GAME_ITEMS_H
