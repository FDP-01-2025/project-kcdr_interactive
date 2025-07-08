#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include "Item.h"

class Inventory
{
private:
    // Fixed arrays instead of vectors
    static const int MAX_HEALING_ITEMS = 15;
    static const int MAX_DAMAGE_ITEMS = 8;

    HealingItem healingItems[MAX_HEALING_ITEMS];
    DamageItem damageItems[MAX_DAMAGE_ITEMS];

    int healingItemCount;
    int damageItemCount;

public:
    // Constructor - initializes counters
    Inventory()
    {
        healingItemCount = 0;
        damageItemCount = 0;
    }

    // ==================== METHODS TO ADD ITEMS ====================

    void addHealingItem(const HealingItem &item)
    {
        // Search if the item already exists to sum quantities
        for (int i = 0; i < healingItemCount; i++)
        {
            if (healingItems[i].getName() == item.getName())
            {
                healingItems[i].addQuantity(item.getQuantity());
                std::cout << "Added " << item.getQuantity() << " " << item.getName()
                          << ". Total: " << healingItems[i].getQuantity() << std::endl;
                return;
            }
        }
        // If it doesn't exist and there is space, add it as new
        if (healingItemCount < MAX_HEALING_ITEMS)
        {
            healingItems[healingItemCount] = item;
            std::cout << "Added new item: " << item.getName() << " (x" << item.getQuantity() << ")" << std::endl;
            healingItemCount++;
        }
        else
        {
            std::cout << "\n*** INVENTORY FULL ***" << std::endl;
            std::cout << "Cannot add " << item.getName() << " - Healing inventory is full!" << std::endl;
            std::cout << "Current healing items: " << healingItemCount << "/" << MAX_HEALING_ITEMS << std::endl;
            std::cout << "You need to use some healing items before picking up more." << std::endl;
        }
    }

    void addDamageItem(const DamageItem &item)
    {
        // Search if the item already exists to sum quantities
        for (int i = 0; i < damageItemCount; i++)
        {
            if (damageItems[i].getName() == item.getName())
            {
                damageItems[i].addQuantity(item.getQuantity());
                std::cout << "Added " << item.getQuantity() << " " << item.getName()
                          << ". Total: " << damageItems[i].getQuantity() << std::endl;
                return;
            }
        }
        // If it doesn't exist and there is space, add it as new
        if (damageItemCount < MAX_DAMAGE_ITEMS)
        {
            damageItems[damageItemCount] = item;
            std::cout << "Added new item: " << item.getName() << " (x" << item.getQuantity() << ")" << std::endl;
            damageItemCount++;
        }
        else
        {
            std::cout << "\n*** INVENTORY FULL ***" << std::endl;
            std::cout << "Cannot add " << item.getName() << " - Damage inventory is full!" << std::endl;
            std::cout << "Current damage items: " << damageItemCount << "/" << MAX_DAMAGE_ITEMS << std::endl;
            std::cout << "You need to use some damage items before picking up more." << std::endl;
        }
    }

    // ==================== METHODS TO SHOW INVENTORY ====================

    void showHealingItems() const
    {
        std::cout << "\n          ─── HEALING ITEMS ───" << std::endl;
        if (healingItemCount == 0)
        {
            std::cout << "          No healing items available." << std::endl;
            return;
        }

        for (int i = 0; i < healingItemCount; i++)
        {
            if (healingItems[i].isAvailable())
            {
                std::cout << "          " << i + 1 << ". " << healingItems[i].getName()
                          << " (+" << healingItems[i].getHealAmount()
                          << " HP) x" << healingItems[i].getQuantity() << std::endl;
            }
        }
    }

    void showDamageItems() const
    {
        std::cout << "\n          ─── DAMAGE ITEMS ───" << std::endl;
        if (damageItemCount == 0)
        {
            std::cout << "          No damage items available." << std::endl;
            return;
        }

        for (int i = 0; i < damageItemCount; i++)
        {
            if (damageItems[i].isAvailable())
            {
                std::cout << "          " << i + 1 << ". " << damageItems[i].getName()
                          << " (" << damageItems[i].getDamage()
                          << " DMG) x" << damageItems[i].getQuantity() << std::endl;
            }
        }
    }

    void showAllItems() const
    {
        showHealingItems();
        showDamageItems();
    }

    // ==================== METHODS TO USE ITEMS ====================

    bool useHealingItem(int index, Player &player)
    {
        if (index < 1 || index > healingItemCount)
        {
            std::cout << "Invalid healing item selection!" << std::endl;
            return false;
        }

        HealingItem &item = healingItems[index - 1];
        if (!item.isAvailable())
        {
            std::cout << "No " << item.getName() << " available!" << std::endl;
            return false;
        }

        item.use(player);
        return true;
    }

    bool useDamageItem(int index, Player &player, Enemy &target)
    {
        if (index < 1 || index > damageItemCount)
        {
            std::cout << "Invalid damage item selection!" << std::endl;
            return false;
        }

        DamageItem &item = damageItems[index - 1];
        if (!item.isAvailable())
        {
            std::cout << "No " << item.getName() << " available!" << std::endl;
            return false;
        }

        item.use(player, target);
        return true;
    }

    // ==================== GETTERS ====================

    // Returns the number of healing items
    int getHealingItemCount() const { return healingItemCount; }

    // Returns the number of damage items
    int getDamageItemCount() const { return damageItemCount; }

    // Returns a specific healing item by index
    const HealingItem &getHealingItem(int index) const { return healingItems[index]; }

    // Returns a specific damage item by index
    const DamageItem &getDamageItem(int index) const { return damageItems[index]; }

    // Completely clears the inventory (for loading saved games)
    void clearAllItems()
    {
        healingItemCount = 0;
        damageItemCount = 0;
        // No need to clear the arrays since the counter controls which elements are valid
    }

    bool hasHealingItems() const
    {
        for (int i = 0; i < healingItemCount; i++)
        {
            if (healingItems[i].isAvailable())
                return true;
        }
        return false;
    }

    bool hasDamageItems() const
    {
        for (int i = 0; i < damageItemCount; i++)
        {
            if (damageItems[i].isAvailable())
                return true;
        }
        return false;
    }

    // ==================== METHODS TO CHECK SPACE ====================

    // Checks if there is space for more healing items
    bool hasSpaceForHealingItems() const
    {
        return healingItemCount < MAX_HEALING_ITEMS;
    }

    // Checks if there is space for more damage items
    bool hasSpaceForDamageItems() const
    {
        return damageItemCount < MAX_DAMAGE_ITEMS;
    }

    // Checks if the healing inventory is full
    bool isHealingInventoryFull() const
    {
        return healingItemCount >= MAX_HEALING_ITEMS;
    }

    // Checks if the damage inventory is full
    bool isDamageInventoryFull() const
    {
        return damageItemCount >= MAX_DAMAGE_ITEMS;
    }

    // Shows the inventory status (used/total slots)
    void showInventoryStatus() const
    {
        std::cout << "\n=== INVENTORY STATUS ===" << std::endl;
        std::cout << "Healing Items: " << healingItemCount << "/" << MAX_HEALING_ITEMS;
        if (isHealingInventoryFull())
        {
            std::cout << " (FULL)";
        }
        std::cout << std::endl;

        std::cout << "Damage Items: " << damageItemCount << "/" << MAX_DAMAGE_ITEMS;
        if (isDamageInventoryFull())
        {
            std::cout << " (FULL)";
        }
        std::cout << std::endl;
    }
};

#endif // INVENTORY_H
