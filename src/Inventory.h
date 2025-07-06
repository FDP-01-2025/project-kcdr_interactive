#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include "Item.h"

class Inventory {
private:
    // Arrays fijos en lugar de vectores
    static const int MAX_HEALING_ITEMS = 20;
    static const int MAX_DAMAGE_ITEMS = 20;
    
    HealingItem healingItems[MAX_HEALING_ITEMS];
    DamageItem damageItems[MAX_DAMAGE_ITEMS];
    
    int healingItemCount;
    int damageItemCount;

public:
    // Constructor - inicializa contadores
    Inventory() {
        healingItemCount = 0;
        damageItemCount = 0;
    }
    
    // ==================== MÉTODOS PARA AÑADIR ITEMS ====================
    
    void addHealingItem(const HealingItem& item) {
        // Buscar si ya existe el item para sumar cantidades
        for (int i = 0; i < healingItemCount; i++) {
            if (healingItems[i].getName() == item.getName()) {
                healingItems[i].addQuantity(item.getQuantity());
                std::cout << "Added " << item.getQuantity() << " " << item.getName() 
                          << ". Total: " << healingItems[i].getQuantity() << std::endl;
                return;
            }
        }
        // Si no existe y hay espacio, añadirlo como nuevo
        if (healingItemCount < MAX_HEALING_ITEMS) {
            healingItems[healingItemCount] = item;
            std::cout << "Added new item: " << item.getName() << " (x" << item.getQuantity() << ")" << std::endl;
            healingItemCount++;
        } else {
            std::cout << "Healing inventory is full!" << std::endl;
        }
    }
    
    void addDamageItem(const DamageItem& item) {
        // Buscar si ya existe el item para sumar cantidades
        for (int i = 0; i < damageItemCount; i++) {
            if (damageItems[i].getName() == item.getName()) {
                damageItems[i].addQuantity(item.getQuantity());
                std::cout << "Added " << item.getQuantity() << " " << item.getName() 
                          << ". Total: " << damageItems[i].getQuantity() << std::endl;
                return;
            }
        }
        // Si no existe y hay espacio, añadirlo como nuevo
        if (damageItemCount < MAX_DAMAGE_ITEMS) {
            damageItems[damageItemCount] = item;
            std::cout << "Added new item: " << item.getName() << " (x" << item.getQuantity() << ")" << std::endl;
            damageItemCount++;
        } else {
            std::cout << "Damage inventory is full!" << std::endl;
        }
    }
    
    // ==================== MÉTODOS PARA MOSTRAR INVENTARIO ====================
    
    void showHealingItems() const {
        std::cout << "\n=== HEALING ITEMS ===" << std::endl;
        if (healingItemCount == 0) {
            std::cout << "No healing items available." << std::endl;
            return;
        }
        
        for (int i = 0; i < healingItemCount; i++) {
            if (healingItems[i].isAvailable()) {
                std::cout << i + 1 << ". " << healingItems[i].getName() 
                          << " (Heals: " << healingItems[i].getHealAmount() 
                          << " HP, Qty: " << healingItems[i].getQuantity() << ")" << std::endl;
            }
        }
    }
    
    void showDamageItems() const {
        std::cout << "\n=== DAMAGE ITEMS ===" << std::endl;
        if (damageItemCount == 0) {
            std::cout << "No damage items available." << std::endl;
            return;
        }
        
        for (int i = 0; i < damageItemCount; i++) {
            if (damageItems[i].isAvailable()) {
                std::cout << i + 1 << ". " << damageItems[i].getName() 
                          << " (Damage: " << damageItems[i].getDamage() 
                          << ", Qty: " << damageItems[i].getQuantity() << ")" << std::endl;
            }
        }
    }
    
    void showAllItems() const {
        showHealingItems();
        showDamageItems();
    }
    
    // ==================== MÉTODOS PARA USAR ITEMS ====================
    
    bool useHealingItem(int index, Player& player) {
        if (index < 1 || index > healingItemCount) {
            std::cout << "Invalid healing item selection!" << std::endl;
            return false;
        }
        
        HealingItem& item = healingItems[index - 1];
        if (!item.isAvailable()) {
            std::cout << "No " << item.getName() << " available!" << std::endl;
            return false;
        }
        
        item.use(player);
        return true;
    }
    
    bool useDamageItem(int index, Player& player, Enemy& target) {
        if (index < 1 || index > damageItemCount) {
            std::cout << "Invalid damage item selection!" << std::endl;
            return false;
        }
        
        DamageItem& item = damageItems[index - 1];
        if (!item.isAvailable()) {
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
    const HealingItem& getHealingItem(int index) const { return healingItems[index]; }
    
    // Devuelve un item de daño específico por índice
    const DamageItem& getDamageItem(int index) const { return damageItems[index]; }
    
    bool hasHealingItems() const {
        for (int i = 0; i < healingItemCount; i++) {
            if (healingItems[i].isAvailable()) return true;
        }
        return false;
    }
    
    bool hasDamageItems() const {
        for (int i = 0; i < damageItemCount; i++) {
            if (damageItems[i].isAvailable()) return true;
        }
        return false;
    }
};

#endif // INVENTORY_H
