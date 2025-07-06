#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <iostream>
#include "Item.h"

class Inventory {
private:
    std::vector<HealingItem> healingItems;
    std::vector<DamageItem> damageItems;

public:
    // ==================== MÉTODOS PARA AÑADIR ITEMS ====================
    
    void addHealingItem(const HealingItem& item) {
        // Buscar si ya existe el item para sumar cantidades
        for (auto& existingItem : healingItems) {
            if (existingItem.getName() == item.getName()) {
                existingItem.addQuantity(item.getQuantity());
                std::cout << "Added " << item.getQuantity() << " " << item.getName() 
                          << ". Total: " << existingItem.getQuantity() << std::endl;
                return;
            }
        }
        // Si no existe, añadirlo como nuevo
        healingItems.push_back(item);
        std::cout << "Added new item: " << item.getName() << " (x" << item.getQuantity() << ")" << std::endl;
    }
    
    void addDamageItem(const DamageItem& item) {
        // Buscar si ya existe el item para sumar cantidades
        for (auto& existingItem : damageItems) {
            if (existingItem.getName() == item.getName()) {
                existingItem.addQuantity(item.getQuantity());
                std::cout << "Added " << item.getQuantity() << " " << item.getName() 
                          << ". Total: " << existingItem.getQuantity() << std::endl;
                return;
            }
        }
        // Si no existe, añadirlo como nuevo
        damageItems.push_back(item);
        std::cout << "Added new item: " << item.getName() << " (x" << item.getQuantity() << ")" << std::endl;
    }
    
    // ==================== MÉTODOS PARA MOSTRAR INVENTARIO ====================
    
    void showHealingItems() const {
        std::cout << "\n=== HEALING ITEMS ===" << std::endl;
        if (healingItems.empty()) {
            std::cout << "No healing items available." << std::endl;
            return;
        }
        
        for (size_t i = 0; i < healingItems.size(); ++i) {
            if (healingItems[i].isAvailable()) {
                std::cout << i + 1 << ". " << healingItems[i].getName() 
                          << " (Heals: " << healingItems[i].getHealAmount() 
                          << " HP, Qty: " << healingItems[i].getQuantity() << ")" << std::endl;
            }
        }
    }
    
    void showDamageItems() const {
        std::cout << "\n=== DAMAGE ITEMS ===" << std::endl;
        if (damageItems.empty()) {
            std::cout << "No damage items available." << std::endl;
            return;
        }
        
        for (size_t i = 0; i < damageItems.size(); ++i) {
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
        if (index < 1 || index > healingItems.size()) {
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
        if (index < 1 || index > damageItems.size()) {
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
    
    const std::vector<HealingItem>& getHealingItems() const { return healingItems; }
    const std::vector<DamageItem>& getDamageItems() const { return damageItems; }
    
    bool hasHealingItems() const {
        for (const auto& item : healingItems) {
            if (item.isAvailable()) return true;
        }
        return false;
    }
    
    bool hasDamageItems() const {
        for (const auto& item : damageItems) {
            if (item.isAvailable()) return true;
        }
        return false;
    }
};

#endif // INVENTORY_H
