#ifndef INVENTORY_MENU_H
#define INVENTORY_MENU_H

#include "ItemFactory.h"
#include "Inventory.h"
#include "map.h"  // For using the map grid system
#include <iostream>
#include <iomanip>
#include <conio.h>  // For _getch()
#include <cstdlib>  // For system()

// Forward declarations for global variables
extern int playerGold;
extern Inventory playerInventory;

class InventoryMenu {
public:
    
    // Shows inventory as a clean visual list using the map grid system
    static void displayInventoryList() {
        // Implementation will be in map.h to avoid circular dependency
        // This function will show a clean list of items with quantities and gold
    }
    
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
