#ifndef ENEMY_UTILS_H
#define ENEMY_UTILS_H

#include "enemy_draw.h"
#include "configurationDifficulty.h"

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


#endif