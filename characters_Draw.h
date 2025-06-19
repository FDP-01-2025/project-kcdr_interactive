#ifndef CHARACTERS_DRAW_H
#define CHARACTERS_DRAW_H

#include "mapa.h" // Asegúrate de tener definida la matriz mapa[FILAS][COLUMNAS]

void drawRhaekor(char mapa[FILAS][COLUMNAS], int fila, int columna) {
    const char* art[] = {
        "   ////\\\\\\\\   ",    // Cabello largo
        "  |  O  O  |  ",    // Cara determinada
        "  |   ==   |  ",    // Boca seria
        "  |_______|  ",    // Mandíbula
        "  /|     |\\  ",    // Brazos musculosos
        " /_|_[]__|_\\ ",    // Pecho con armadura ligera
        "   /  |  \\   ",    // Cintura
        "  /   |   \\  ",    // Piernas separadas
        " /____|____\\ "     // Botas
    };
    for (int i = 0; i < 9; ++i)
        for (int j = 0; art[i][j] != '\0'; ++j)
            if (fila + i < FILAS && columna + j < COLUMNAS)
                mapa[fila + i][columna + j] = art[i][j];
}

void drawCerephios(char mapa[FILAS][COLUMNAS], int fila, int columna) {
    const char* art[] = {
        "   _______   ",    // Casco
        "  | [o] [o]| ",    // Visor metálico
        "  |_______| ",     // Casco cerrado
        "   |=====|   ",    // Cuello protegido
        "  /|#####|\\ ",    // Armadura completa
        " | |#####| |",     // Pecho blindado
        "   |__|__|   ",    // Abdomen
        "  /   |   \\  ",    // Piernas firmes
        " /____|____\\ "     // Botas reforzadas
    };
    for (int i = 0; i < 9; ++i)
        for (int j = 0; art[i][j] != '\0'; ++j)
            if (fila + i < FILAS && columna + j < COLUMNAS)
                mapa[fila + i][columna + j] = art[i][j];
}

void drawKaelren(char mapa[FILAS][COLUMNAS], int fila, int columna) {
    const char* art[] = {
        "    _____    ",    // Capucha
        "   /     \\   ",    // Rostro calmado
        "  |  o o  |  ",    // Ojos sabios
        "  |   ~   |  ",    // Boca tranquila
        "  |_______|  ",    // Barba ligera
        "    |||||    ",    // Bastón
        "   /|||\\     ",    // Túnica mágica
        "  / | | \\    ",    // Túnica larga
        " /__|_|__\\   "     // Botas de viajero
    };
    for (int i = 0; i < 9; ++i)
        for (int j = 0; art[i][j] != '\0'; ++j)
            if (fila + i < FILAS && columna + j < COLUMNAS)
                mapa[fila + i][columna + j] = art[i][j];
}

void drawValdrik(char mapa[FILAS][COLUMNAS], int fila, int columna) {
    const char* art[] = {
        "   /^^^^^\\   ",    // Cabello corto
        "  |  o o  |  ",    // Rostro firme
        "  |   -   |  ",    // Boca concentrada
        "  |_______|  ",    // Quijada recta
        "  /|     |\\  ",    // Brazos armados
        " | |=====| | ",    // Armadura ligera
        "   |  |  |   ",    // Cintura ajustada
        "  /   |   \\  ",    // Piernas listas
        " /____|____\\ "     // Botas funcionales
    };
    for (int i = 0; i < 9; ++i)
        for (int j = 0; art[i][j] != '\0'; ++j)
            if (fila + i < FILAS && columna + j < COLUMNAS)
                mapa[fila + i][columna + j] = art[i][j];
}

#endif // CHARACTERS_DRAW_H
