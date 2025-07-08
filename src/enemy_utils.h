#ifndef ENEMY_UTILS_H
#define ENEMY_UTILS_H

#include "enemy_draw.h"
#include "configurationDifficulty.h"
#include "Boss.h"

// This file contains utility functions for applying difficulty scaling to enemies and bosses.
// Apply difficulty scaling to all normal enemies (indices 0-11)
// Increases enemy stats based on the selected difficulty configuration
inline void applyDifficultyEnemies(const configurationDifficulty &config)
{
    for (int i = 0; i < 12; ++i)
    {
        int newMaxHealth = enemy[i].getMaxHealth() + config.enemyHealth;
        enemy[i] = Enemy(
            enemy[i].getName(),
            newMaxHealth, // Both current and max health are set to the new value
            enemy[i].getAttack() + config.enemyAttack,
            enemy[i].getDefense(),
            enemy[i].getAsciiArt());
    }
}

// Apply difficulty scaling to all bosses (indices 0-3)
// Bosses receive double the health and attack bonuses compared to normal enemies
inline void applyDifficultyBosses(Boss bosses[4], const configurationDifficulty &config)
{
    for (int i = 0; i < 4; ++i)
    {
        int newMaxHealth = bosses[i].getMaxHealth() + config.enemyHealth * 2;
        bosses[i] = Boss(
            bosses[i].getName(),
            newMaxHealth,                                          // Both current and max health are set to the new value
            bosses[i].getAttack() + config.enemyAttack * 2,        // Double attack bonus
            bosses[i].getDefense() + config.enemyAttack / 2,       // Defense bonus based on attack
            bosses[i].getSpecialAttack() + config.enemyAttack * 3, // Triple special attack bonus
            bosses[i].getAsciiArt()                                // Preserve original ASCII art
        );
    }
}

#endif
