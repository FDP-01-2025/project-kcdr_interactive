#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include "Item.h"

class Inventory
{
private:
    // Arrays fijos en lugar de vectores
    static const int MAX_HEALING_ITEMS = 15;
    static const int MAX_DAMAGE_ITEMS = 8;

    HealingItem healingItems[MAX_HEALING_ITEMS];
    DamageItem damageItems[MAX_DAMAGE_ITEMS];

    int healingItemCount;
    int damageItemCount;

public:
    // Constructor - inicializa contadores
    Inventory()
    {
        healingItemCount = 0;
        damageItemCount = 0;
    }

    // ==================== MÉTODOS PARA AÑADIR ITEMS ====================

    void addHealingItem(const HealingItem &item)
    {
        // Buscar si ya existe el item para sumar cantidades
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
        // Si no existe y hay espacio, añadirlo como nuevo
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
        // Buscar si ya existe el item para sumar cantidades
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
        // Si no existe y hay espacio, añadirlo como nuevo
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

    // ==================== MÉTODOS PARA MOSTRAR INVENTARIO ====================

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

    // ==================== MÉTODOS PARA USAR ITEMS ====================

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

    // Devuelve el número de items de curación
    int getHealingItemCount() const { return healingItemCount; }

    // Devuelve el número de items de daño
    int getDamageItemCount() const { return damageItemCount; }

    // Devuelve un item de curación específico por índice
    const HealingItem &getHealingItem(int index) const { return healingItems[index]; }

    // Devuelve un item de daño específico por índice
    const DamageItem &getDamageItem(int index) const { return damageItems[index]; }

    // Limpia completamente el inventario (para cargar partidas guardadas)
    void clearAllItems()
    {
        healingItemCount = 0;
        damageItemCount = 0;
        // No necesitamos limpiar los arrays ya que el contador controla qué elementos son válidos
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

    // ==================== MÉTODOS PARA VERIFICAR ESPACIO ====================

    // Verifica si hay espacio para más items de curación
    bool hasSpaceForHealingItems() const {
        return healingItemCount < MAX_HEALING_ITEMS;
    }
    
    // Verifica si hay espacio para más items de daño
    bool hasSpaceForDamageItems() const {
        return damageItemCount < MAX_DAMAGE_ITEMS;
    }
    
    // Verifica si el inventario de curación está lleno
    bool isHealingInventoryFull() const {
        return healingItemCount >= MAX_HEALING_ITEMS;
    }
    
    // Verifica si el inventario de daño está lleno
    bool isDamageInventoryFull() const {
        return damageItemCount >= MAX_DAMAGE_ITEMS;
    }
    
    // Muestra el estado del inventario (espacios usados/totales)
    void showInventoryStatus() const {
        std::cout << "\n=== INVENTORY STATUS ===" << std::endl;
        std::cout << "Healing Items: " << healingItemCount << "/" << MAX_HEALING_ITEMS;
        if (isHealingInventoryFull()) {
            std::cout << " (FULL)";
        }
        std::cout << std::endl;
        
        std::cout << "Damage Items: " << damageItemCount << "/" << MAX_DAMAGE_ITEMS;
        if (isDamageInventoryFull()) {
            std::cout << " (FULL)";
        }
        std::cout << std::endl;
    }
};

#endif // INVENTORY_H
