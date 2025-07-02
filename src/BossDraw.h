#ifndef BOSS_DRAW_H // Include guard: prevents this header file from being included more than once
#define BOSS_DRAW_H // Defines BOSS_DRAW_H macro if not already defined

// This file contains only the ASCII art data for final bosses.
// Drawing functions are located in enemy_draw.h to maintain consistency with the enemy system.
// Unlike enemy_draw.h, this file only provides ASCII art data and helper functions.

#include <string> // Include string library for std::string data type

// ===== Boss ASCII Art Data =====

// Array that stores ASCII art for each boss by index
const std::string bossArt[4] = {
    // Queen of Shadows: Master of dark magic, first final boss (13 lines, max 18 chars)
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
      /__________\
)",

    // Arcane Sovereign: Necromancer queen, second final boss (12 lines, max 19 chars)
    R"(
         _/I\_
        /  o  \
       |   I   |
       |  /^\  |
       /       \
      /|  ___  |\
     /||  \_/  ||\
    / ||_/   \_|| \
   /__|         |__\
   |   \       /   |
   |    \_____/    |
      |___|___|_|
)",

    // Crystal Queen: Elemental magic wielder, third final boss (14 lines, max 21 chars)
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
     | |  o o  | |
     | |   ^   | |
     |  \_____/  |
    |    |___|    |
  /_______|_______\
)",

    // Void Sovereign: Ultimate final boss (15 lines, max 21 chars)
    R"(
         _______
        /       \
       /|  o o  |\
      / |   v   | \
     |   \__|__/   |
     |  /       \  |
     | |   /^\   | |
     | |  /   \  | |
     | |  \___/  | |
      \ \       / /
       \ \_____/ /
        /|     |\
       / |     | \
      /__|_____|__\
        |_______|
)"
};

// ===== Helper Function to Get Boss ASCII Art =====

// Helper function to get ASCII art based on boss name
// Returns the appropriate ASCII art string for the specified boss
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
    // Default: return the first boss art if name is not recognized
    return bossArt[0];
}

#endif // BOSS_DRAW_H // Marks the end of the include guard block
