#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "TitleScreen.h"
#include "MenuSystem.h"
#include "SaveManager.h"
#include "GameController.h"

// Enhanced game menu class for "Brothers of the Dawn: Fragments of the Alba"
class GameMenu
{
public:
    // Display the complete title sequence (title + introduction)
    static void displayTitleScreen();
    
    // Display the main menu and handle user choices
    static void displayMainMenu();
    
    // Display death screen with continue/exit options
    static void displayDeathScreen();
    
    // Functions for combat system integration
    static void incrementEnemiesDefeated();
    static void saveProgressAfterCombat(const std::string& location);
    static int getCurrentEnemyCount();
    static void updatePlayerPosition(int x, int y);
    
    // Functions for map management
    static void resetMapEnemyCounter();
    static int getCurrentMapEnemyCount();
};

// Implementation of simplified methods
void GameMenu::displayTitleScreen()
{
    // First show the ASCII title
    TitleScreen::displayGameTitle();
    
    // Then show the introduction
    TitleScreen::displayIntroduction();
}

void GameMenu::displayMainMenu()
{
    GameController::runMainMenu();
}

void GameMenu::displayDeathScreen()
{
    GameController::handleDeathScreen();
}

void GameMenu::incrementEnemiesDefeated()
{
    SaveManager::incrementEnemiesDefeated();
}

void GameMenu::saveProgressAfterCombat(const std::string& location)
{
    SaveManager::saveProgressAfterCombat(location);
}

int GameMenu::getCurrentEnemyCount()
{
    return SaveManager::getCurrentEnemyCount();
}

void GameMenu::updatePlayerPosition(int x, int y)
{
    SaveManager::updatePlayerPosition(x, y);
}

void GameMenu::resetMapEnemyCounter()
{
    SaveManager::resetMapEnemyCounter();
}

int GameMenu::getCurrentMapEnemyCount()
{
    return SaveManager::getCurrentMapEnemyCount();
}

#endif // GAME_MENU_H
