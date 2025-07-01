#ifndef BOSS_DRAW_H // Include guard: prevents this header file from being included more than once
#define BOSS_DRAW_H // Defines BOSS_DRAW_H if it hasn't been defined already

// Este archivo proporciona funcionalidad específica para dibujar los jefes finales (bosses) en el mapa.
// El arte ASCII está centralizado aquí, separado de la lógica de los jefes.
// A diferencia de enemy_draw.h, este archivo está especializado en jefes con capacidades únicas.

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

// ===== Function to Draw Any Boss on the Map =====

// Esta función funciona de manera similar a drawEnemy, toma:
// - una referencia constante a un objeto Boss `b`,
// - una referencia al array 2D del mapa,
// - coordenadas `row` y `col` para determinar dónde colocar el arte ASCII del jefe.

void drawBoss(const Boss &b, char map[ROWS][COLUMNS], int row, int col)
{
    // Obtener el string de arte ASCII del jefe basado en su nombre
    std::string art = getBossAsciiArt(b.getName()); 
    
    // Inicializar contadores de fila y columna relativos al arte ASCII que se dibujará
    int currentRow = 0;
    int currentCol = 0;

    // Recorrer cada carácter en el string de arte ASCII
    for (char ch : art)
    {
        if (ch == '\n') // Cuando se encuentra un salto de línea,
        {
            currentRow++;   // mover una fila hacia abajo
            currentCol = 0; // resetear la posición de la columna al principio
            continue;       // saltar al siguiente carácter
        }

        // Solo dibujar caracteres si la posición calculada está dentro de los límites del mapa
        if (row + currentRow < ROWS && col + currentCol < COLUMNS)
        {
            // Colocar el carácter en la posición correcta del mapa del juego
            map[row + currentRow][col + currentCol] = ch;
        }

        currentCol++; // Pasar a la siguiente columna para la línea actual
    }
}

// Función de conveniencia para dibujar un jefe por número (1-4)
inline void drawBoss(int bossNumber, char map[ROWS][COLUMNS], int row, int col)
{
    // El número del jefe debe ser 1-4
    if (bossNumber < 1 || bossNumber > 4) {
        return; // Salir si el número del jefe no es válido
    }
    
    // Crear el jefe correspondiente
    Boss boss = Boss("", 0, 0, 0, 0); // Placeholder inicial
    
    switch (bossNumber) {
        case 1:
            boss = createBoss1(); // Queen of Shadows
            break;
        case 2:
            boss = createBoss2(); // Arcane Sovereign
            break;
        case 3:
            boss = createBoss3(); // Crystal Queen
            break;
        case 4:
            boss = createBoss4(); // Void Sovereign
            break;
    }
    
    // Dibujar el jefe usando la función principal
    drawBoss(boss, map, row, col);
}

#endif // BOSS_DRAW_H // Marks the end of the include guard block
