#include "src/Player.h" // Incluir el archivo Jugador.h para poder usar la clase Jugador
#include "src/Enemy.h" // Incluir el archivo Enemigo.h para poder usar la clase Enemigo
#include "src/EventsAleatory.h" // Incluir el archivo EventsAleatory.h para poder usar la clase EventosAleatorios
#include "src/BossCreation.h"
#include "game.cpp"
#include <iostream>
using namespace std;

int main()
{
    Boss boss1 = createBoss1();

    return 0;
}