#include "src/Player.h" // Incluir el archivo Jugador.h para poder usar la clase Jugador
#include "src/Enemy.h" // Incluir el archivo Enemigo.h para poder usar la clase Enemigo
#include "src/EventsAleatory.h" // Incluir el archivo EventsAleatory.h para poder usar la clase EventosAleatorios
#include "src/Combat.h"
#include "game.cpp"
#include <iostream>
using namespace std;



int main()
{

    // Crear un jugador (puedes cambiar los stats)
    Player player(100, 15, 5, 25);

    // Llamar a una batalla contra el primer enemigo
    Combat(player, enemy[1]);  
      return 0;
}