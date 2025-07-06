#ifndef BOSS_DRAW_H // Header guard: prevents multiple inclusions of this file during compilation process
#define BOSS_DRAW_H     // Defines the BOSS_DRAW_H preprocessor macro to mark this file as included

// ======== BOSS VISUAL REPRESENTATION SYSTEM ========
// This specialized header file manages ASCII art data for final boss encounters in the game
// It serves as a centralized repository for boss visual representations and related helper functions
//
// ARCHITECTURAL DESIGN NOTE:
// - This file contains ONLY ASCII art data and retrieval functions
// - Actual drawing/rendering functions are located in enemy_draw.h for system consistency
// - This separation allows for easy art updates without affecting rendering logic
// - Unlike enemy_draw.h which handles both art and drawing, this focuses purely on data storage

#include <string> // Standard C++ string library - required for std::string data type and string operations

// ======== BOSS ASCII ART DATA REPOSITORY ========
// This section contains all visual representations for the game's final boss encounters
// Each boss has unique ASCII art that reflects their thematic role and power level

// Constant array storing ASCII art for all boss types, indexed by boss difficulty/progression
// Using const ensures the art data cannot be accidentally modified during runtime
// Raw string literals R"(...)" allow multi-line strings without escape characters
const std::string bossArt[4] = {
    // ======== BOSS 0: QUEEN OF SHADOWS ========
    // First-tier final boss - Master of dark magic and shadow manipulation
    // VISUAL DESIGN: Features crown-like spikes, menacing eyes, and flowing dark robes
    // DIMENSIONS: 13 lines tall, maximum 18 characters wide
    // THEMATIC ELEMENTS: Triple crown spikes represent royal authority, glowing eyes show magical power
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

    // ======== BOSS 1: ARCANE SOVEREIGN ========
    // Second-tier final boss - Necromancer queen with command over death magic
    // VISUAL DESIGN: Features mystical staff, flowing robes, and arcane symbols
    // DIMENSIONS: 12 lines tall, maximum 19 characters wide  
    // THEMATIC ELEMENTS: Central staff (_/I\_) represents magical focus, symmetrical design shows balance of power
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

    // ======== BOSS 2: CRYSTAL QUEEN ========
    // Third-tier final boss - Elemental magic wielder with mastery over crystalline forces
    // VISUAL DESIGN: Features crystalline crown, angular geometric patterns, and jeweled elements
    // DIMENSIONS: 14 lines tall, maximum 21 characters wide
    // THEMATIC ELEMENTS: Angular shapes represent crystal formations, multiple eyes show omniscience
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

    // ======== BOSS 3: VOID SOVEREIGN ========
    // Fourth-tier final boss - Ultimate antagonist with reality-warping void powers
    // VISUAL DESIGN: Features imposing crown, void-touched face, and reality-bending form
    // DIMENSIONS: 15 lines tall, maximum 21 characters wide
    // THEMATIC ELEMENTS: Enclosed design represents contained chaos, multiple layers show dimensional complexity
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

// ======== BOSS ART RETRIEVAL SYSTEM ========
// This section provides the interface for accessing boss ASCII art based on boss identification

// ======== DYNAMIC ART LOOKUP FUNCTION ========
// Helper function that maps boss names to their corresponding ASCII art representations
// This allows the combat system to display the correct boss art without knowing array indices
// Parameters: bossName - string identifier for the boss type
// Returns: std::string containing the complete ASCII art for the specified boss
inline std::string getBossAsciiArt(const std::string& bossName) {
    // ======== BOSS NAME MATCHING SYSTEM ========
    // Use string comparison to determine which boss art to return
    // This approach allows for easy boss identification and art retrieval
    
    if (bossName == "Queen of Shadows") {
        return bossArt[0];  // Return first boss art (dark magic master)
    } else if (bossName == "Arcane Sovereign") {
        return bossArt[1];  // Return second boss art (necromancer queen)
    } else if (bossName == "Crystal Queen") {
        return bossArt[2];  // Return third boss art (elemental wielder)
    } else if (bossName == "Void Sovereign") {
        return bossArt[3];  // Return fourth boss art (ultimate antagonist)
    }
    
    // ======== FALLBACK MECHANISM ========
    // If an unrecognized boss name is provided, return the first boss art as default
    // This prevents crashes and ensures the game can continue even with invalid boss names
    return bossArt[0];
}

#endif // BOSS_DRAW_H - End of header guard, matches the #ifndef at the beginning of the file
