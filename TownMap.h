#ifndef TOWNMAP_H
#define TOWNMAP_H

#include <iostream>

#include <string> // para poder usar cadenas de texto

const int FILAS = 30;
const int COLUMNAS = 50;

class Mapa {
private:
    char mapa[FILAS][COLUMNAS];
    int jugadorX, jugadorY;

public:
    Mapa();
    void mostrarMapa() const;
    void moverJugador(char direccion);
    void interactuar();
    void jugar();
};

#endif