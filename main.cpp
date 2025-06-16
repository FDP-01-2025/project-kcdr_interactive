#include "src/Player.h" // Incluir el archivo Jugador.h para poder usar la clase Jugador
#include "src/Enemy.h" // Incluir el archivo Enemigo.h para poder usar la clase Enemigo
#include "src/EventsAleatory.h" // Incluir el archivo EventsAleatory.h para poder usar la clase EventosAleatorios
#include "game.cpp"
#include <iostream>
using namespace std;

int main()
{
    /*
    int opcion;
    // Declaramos los personajes (Ahorita es una prueba)
    Jugador prueba1(200, 10, 20, 10);
    Jugador prueba2(10, 1, 2, 200);

    //Creamos una variable llama "jugadorSeleccionado" que es un puntero de jugador  
    Jugador* jugadorSeleccionado = nullptr;

    // Mostramos los personajes que existen
    cout << "Elige tu personaje:\n";
    cout << "1. Guerrero\n";
    cout << "2. Mago\n";
    cout << "3. Arquero\n";
    cout << "4. Ninja\n> ";
    // Lo almacenamos en la variable opcion
    cin >> opcion;

    switch (opcion)
    {
    case 1:
        jugadorSeleccionado = &prueba1;
        break;
    case 2:
    jugadorSeleccionado = &prueba2;
        break;    
    
    default:
     cout << "Opción inválida. Se usará Guerrero por defecto.\n";
        break;
    }

    cout << "has elegido" << endl;
    jugadorSeleccionado -> mostrarStats();

        Enemigo enemigo(80, 1, 10);

        Combate(*jugadorSeleccionado, enemigo);*/

    system("cls");
    Mapa juego;
    juego.jugar();


    return 0;
}