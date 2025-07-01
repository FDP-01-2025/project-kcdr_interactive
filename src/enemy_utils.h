#ifndef ENEMY_UTILS_H
#define ENEMY_UTILS_H

#include "enemy_draw.h"
#include "configurationDifficulty.h"
#include "Boss.h"

// Aplica la dificultad a todos los enemigos normales (índices 0-11)
inline void applyDifficultyEnemies(const configurationDifficulty& config){
    for (int i = 0; i < 12; ++i)
    {
        enemy[i] = Enemy(
            enemy[i].getName(),
            enemy[i].getHealth() + config.enemyHealth,
            enemy[i].getAttack() + config.enemyAttack,
            enemy[i].getDefense(),
            enemy[i].getAsciiArt()
        );
    }
}

// Aplica la dificultad a todos los jefes (índices 0-3)
inline void applyDifficultyBosses(Boss bosses[4], const configurationDifficulty& config) {
    for (int i = 0; i < 4; ++i) {
        bosses[i] = Boss(
            bosses[i].getName(),
            bosses[i].getHealth() + config.enemyHealth * 2,
            bosses[i].getAttack() + config.enemyAttack * 2,
            bosses[i].getDefense() + config.enemyAttack / 2,
            bosses[i].getspecialAtack() + config.enemyAttack * 3
        );
    }
}

#endif
