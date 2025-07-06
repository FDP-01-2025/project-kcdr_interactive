#ifndef INVENTORY_MENU_H
#define INVENTORY_MENU_H

#include "ItemFactory.h"
#include "Inventory.h"
#include <iostream>

// Forward declarations for global variables
extern int playerGold;
extern Inventory playerInventory;

class InventoryMenu {
public:
    // ==================== INVENTORY MENU ====================
    
    static void displayInventoryMenu() {
        std::cout << "\n=== INVENTORY ===" << std::endl;
        std::cout << "Gold: " << playerGold << std::endl;
        std::cout << "\nItems:" << std::endl;
        playerInventory.showAllItems();
        
        std::cout << "\nOptions:" << std::endl;
        std::cout << "1. Use Item" << std::endl;
        std::cout << "2. Return to Main Menu" << std::endl;
        std::cout << "Enter choice: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 1) {
            std::cout << "Enter item ID to use: ";
            int itemId;
            std::cin >> itemId;
            // Note: You'll need to implement item usage with player reference
            // playerInventory.useItem(itemId, player);
            std::cout << "Item usage system needs player reference for implementation." << std::endl;
        }
    }
    
    // ==================== SHOP MENU ====================
    
    static void displayShopMenu() {
        std::cout << "\n=== ITEM SHOP ===" << std::endl;
        std::cout << "Your Gold: " << playerGold << std::endl;
        
        ItemFactory::showShopItems();
        
        std::cout << "\nEnter item ID to buy (0 to exit): ";
        int itemId;
        std::cin >> itemId;
        
        if (itemId > 0) {
            if (ItemFactory::buyItem(itemId, playerInventory, playerGold)) {
                std::cout << "Purchase successful!" << std::endl;
                std::cout << "Remaining Gold: " << playerGold << std::endl;
            } else {
                std::cout << "Purchase failed! Check if you have enough gold." << std::endl;
            }
        }
    }
    
    // ==================== QUICK INVENTORY DISPLAY ====================
    
    static void showQuickInventory() {
        std::cout << "\n--- Quick Inventory ---" << std::endl;
        std::cout << "Gold: " << playerGold << std::endl;
        playerInventory.showAllItems();
        std::cout << "-----------------------" << std::endl;
    }
    
    // ==================== GOLD DISPLAY ====================
    
    static void showCurrentGold() {
        std::cout << "Current Gold: " << playerGold << std::endl;
    }
};

#endif // INVENTORY_MENU_H
