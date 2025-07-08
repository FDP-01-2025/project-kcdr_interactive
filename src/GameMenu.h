/*
 * GameMenu.h - Game Menu System and Interface Coordinator
 * ------------------------------------------------------
 * Provides a high-level interface for menu navigation, combat integration,
 * save management, and map transitions in "Brothers of the Dawn: Fragments of the Alba".
 * Implements the Facade pattern to simplify access to complex subsystems.
 */

#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "TitleScreen.h"
#include "MenuSystem.h"
#include "SaveManager.h"
#include "GameController.h"

// GameMenu: Facade for menu, combat, and save/load operations
class GameMenu {
public:
    // Title and menu display
    static void displayTitleScreen();
    static void displayMainMenu();
    static void displayDeathScreen();

    // Combat system integration
    static void incrementEnemiesDefeated();
    static void saveProgressAfterCombat(const std::string& location);
    static int getCurrentEnemyCount();
    static void updatePlayerPosition(int x, int y);

    // Map management
    static void resetMapEnemyCounter();
    static int getCurrentMapEnemyCount();
};

// Implementation
void GameMenu::displayTitleScreen() {
    TitleScreen::displayGameTitle();
    TitleScreen::displayIntroduction();
}

void GameMenu::displayMainMenu() {
    GameController::runMainMenu();
}

void GameMenu::displayDeathScreen() {
    GameController::handleDeathScreen();
}

void GameMenu::incrementEnemiesDefeated() {
    SaveManager::incrementEnemiesDefeated();
}

void GameMenu::saveProgressAfterCombat(const std::string& location) {
    SaveManager::saveProgressAfterCombat(location);
}

int GameMenu::getCurrentEnemyCount() {
    return SaveManager::getCurrentEnemyCount();
}

void GameMenu::updatePlayerPosition(int x, int y) {
    SaveManager::updatePlayerPosition(x, y);
}

void GameMenu::resetMapEnemyCounter() {
    SaveManager::resetMapEnemyCounter();
}

int GameMenu::getCurrentMapEnemyCount() {
    return SaveManager::getCurrentMapEnemyCount();
}

#endif // GAME_MENU_H
