#ifndef BOSS_DRAW_H // Include guard: prevents this header file from being included more than once
#define BOSS_DRAW_H // Defines BOSS_DRAW_H if it hasn't been defined already

// Este archivo contiene únicamente el arte ASCII de los jefes finales (bosses).
// Las funciones de dibujo están en enemy_draw.h para mantener consistencia con el sistema.
// A diferencia de enemy_draw.h, este archivo solo proporciona datos de arte ASCII.

#include "map.h"   // Includes the map.h file, which provides access to the game map (e.g., a 2D grid)
#include "Boss.h" // Includes the Boss.h file, which defines the Boss class and its attributes/methods

// ===== Arte ASCII de los Jefes =====

// Array que almacena el arte ASCII para cada jefe por nombre
const std::string bossArt[4] = {
    // Queen of Shadows: Master of dark magic, first final boss
    R"(
      /\   /\   /\
     /  \ /  \ /  \
    |    |    |    |
     \    \^^/    /
      \   (oo)   /
       \  /--\  /
        \|    |/
         |    |
        /|....|\ 
       / |____| \
      /__|    |__\
     |   \____/   |
     |   /    \   |
      \ (______) /
       \_|_||_|_/
       /_|_||_|_\
      /__________\
)",

    // Arcane Sovereign: Necromancer queen, second final boss
    R"(
         _/I\_
        /  o  \
       |   I   |
       |  /^\  |
       \_|_|_|_/
       /       \
      /|  ___  |\
     /||  \_/  ||\
    / ||_/   \_|| \
   /__|         |__\
   |   \       /   |
   |    \_____/    |
   |  /|       |\  |
   |_/ |_/\_/\_| \_|
   /   |_______| \ \
  /___/         \___\
      |___|___|_|
)",

    // Crystal Queen: Elemental magic wielder, third final boss  
    R"(
          /^\
         /| |\
        / /^\ \
       /  \^/  \
      /    v    \
     |  /\   /\  |
     | <  \ /  > |
     |  \  |  /  |
     |   __|__   |
     |  /     \  |
     | |  o o  | |
     | |   ^   | |
     | |  \_/  | |
     |  \_____/  |
      \__/   \__/
     /   |   |   \
    |    |___|    |
    |___|     |___|
   /             \
  /_______|_______\
)",

    // Void Sovereign: Ultimate final boss with devastating power
    R"(
         _______
        /       \
       /|  o o  |\
      / |   v   | \
     |   \__|__/   |
     |  /       \  |
     | |   /^\   | |
     | |  /   \  | |
     | | |     | | |
     | |  \___/  | |
      \ \       / /
       \ \_____/ /
        \       /
        /|     |\
       / |     | \
      /__|_____|__\
     /___/     \___\
    |___|       |___|
   /    |       |    \
  /_____|_______|_____\
        |_______|
)"
};

// ===== Función auxiliar para obtener el arte ASCII de jefes =====

// Función auxiliar para obtener el arte ASCII basado en el nombre del jefe
inline std::string getBossAsciiArt(const std::string& bossName) {
    if (bossName == "Queen of Shadows") {
        return bossArt[0];
    } else if (bossName == "Arcane Sovereign") {
        return bossArt[1];
    } else if (bossName == "Crystal Queen") {
        return bossArt[2];
    } else if (bossName == "Void Sovereign") {
        return bossArt[3];
    }
    // Por defecto, devolver el arte del primer jefe si no se reconoce el nombre
    return bossArt[0];
}

#endif // BOSS_DRAW_H // Marks the end of the include guard block
