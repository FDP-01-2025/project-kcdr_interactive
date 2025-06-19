#include "map.h"             // Incluye la definición de la clase Map (mapa)
#include "characters_draw.h" // Incluye las funciones para dibujar personajes

int main()
{
    Map map; // Crea un objeto de tipo Map llamado map

    // Dibuja dos personajes en el mapa
    drawRhaekor(map.getGrid(), 6, 10); // Dibuja al personaje "Rhaekor" en la posición fila 6, columna 10
    drawValdrik(map.getGrid(), 6, 50); // Dibuja al personaje "Valdrik" en la posición fila 6, columna 50

    map.display(); // Muestra el mapa con los personajes dibujados en consola

    return 0; // Finaliza el programa
}
