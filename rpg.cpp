#include "Enemigo.h"
#include "Jugador.h"
#include "Combate.h"
#include <iostream> // Para poder usar cout y endl

using namespace std;

// ========== Jugadores ==========
// Mandamos a llamar los datos que declaramos en el .h
Jugador::Jugador(int vida, int ataque, int defensa, int ataque_especial)
    : nombre("Jugador1"), vida(vida), ataque(ataque), defensa(defensa), ataque_especial(ataque_especial) {}

// Muestra los atributos del jugador
void Jugador::mostrarStats() const
{
    cout << "Jugador: " << nombre
         << " | Vida: " << vida
         << " | Ataque: " << ataque
         << " | Defensa: " << defensa
         << " | Especial: " << ataque_especial << endl;
}

void Jugador::recibirDanio(int danio)
{
    int danioReal = danio - defensa;
    if (danioReal < 0)
    {
        danioReal = 0; // Si la defensa es mayor que el daño, daño real es 0
    }

    if (danioReal == 0)
    {
        cout << "La defensa del jugador fue suficiente No se recibió daño." << endl;
    }
    vida -= danioReal; // Restar daño a la vida SIEMPRE, después de ajustar dañoReal

    if (vida < 0)
    {
        vida = 0; // Evitar vida negativa
    }
}

int Jugador::getVida() const
{
    return vida; // Devuelve el valor de la variable privada 'vida'
}

int Jugador::getAtaque() const
{
    return ataque; // Devuelve el valor de la variable privada 'ataque'
}

int Jugador::getDefensa() const
{
    return defensa; // Devuelve el valor de la variable privada 'defensa'
}

int Jugador::getAtaqueEspecial() const
{
    return ataque_especial; // Devuelve el valor de la variable privada 'defensa'
}

// ========== Enemigos ==========
// Mandamos a llamar los datos que declaramos en el .h
Enemigo::Enemigo(int vida, int ataque, int defensa)
    : nombre("Enemigo"), vida(vida), ataque(ataque), defensa(defensa) {}

void Enemigo::mostrarStats() const
{
    cout << "Enemigo: " << nombre
         << " | Vida: " << vida
         << " | Ataque: " << ataque
         << " | Defensa: " << defensa << endl;
}

void Enemigo::recibirDanio(int danio)
{
    int danioReal = danio - defensa;
    if (danioReal < 0)
    {
        danioReal = 0; // Si la defensa es mayor al ataque no tendra daño real
    }
    vida -= danioReal; // Restar daño a la vida SIEMPRE, después de ajustar dañoReal

    if (danioReal == 0)
    {
        cout << "La defensa del jugador fue suficiente No se recibió daño." << endl;
    }

    if (vida < 0)
    {
        vida = 0; // Evitar vida negativa
    }
}

int Enemigo::getVida() const
{
    return vida; // Devuelve el valor de la variable privada 'vida'
}

int Enemigo::getAtaque() const
{
    return ataque; // Devuelve el valor de la variable privada 'ataque'
}

string Enemigo::getNombre() const
{
    return nombre; // Devuelve el valor de la variable privada 'nombre'
}

// ========== Combate ==========

// Funcion que no retornara nada y recibe datos del jugador y del enemigo
void Combate(Jugador &jugador, Enemigo &enemigo)
{
    cout << "Inicie el combate" << endl;
    jugador.mostrarStats(); // Manda a llamar a "mostrarStats" para mostrar las stats del jugador
    enemigo.mostrarStats(); // Manda a llamar a "mostrarStats" para mostrar las stats del enemigo

    // Bucle while para que el combate continuara mientras ambos tengan vida
    while (jugador.getVida() > 0 && enemigo.getVida() > 0)
    {

        // Se le pide al usuario seleccionar un acción
        cout << "Elige una acción" << endl;
        cout << "1. Ataque normal (" << jugador.getAtaque() << "daño" << endl;           // Se manda a llamar getAtaque para mostrar cuanto daño hace el ataque
        cout << "2. Ataque especial (" << jugador.getAtaqueEspecial() << "daño" << endl; // Se manda a llamar getAtaqueEspecial para mostrar cuanto daño hace el ataque

        int opcion;    // Declaramos una variable donde se almacenara la seleccion del jugador
        cin >> opcion; // Donde se almacena la seleccion del jugador

        int danio = 0; // Declaramos variable "danio"
        // Usamos switch para poder manejar las decciones del usuario
        switch (opcion)
        {
            // Si elije 1 hara un ataque normal y se mostrara un mensaje
        case 1:
            danio = jugador.getAtaque();
            cout << "Se ha usado ataque normal" << endl;
            break;

            // Si elije 2 hara un ataque especial y se mostrara un mensaje
        case 2:
            danio = jugador.getAtaqueEspecial();
            cout << "Se ha usado ataque especial" << endl;
            break;

            // Si el usuario pone una opcion aparte del 1 y 2 se le mostrara un mensaje de opcion invalida y hara un ataque normal
        default:
            danio = jugador.getAtaque();
            cout << "Opcion invalida, ataque normal por defencto" << endl;
            break;
        }
        enemigo.recibirDanio(danio); // Se manda a llamar la funcion "RecibirDanio" del enemigo, funcion para calcular cuanta defensa reduce al daño y le resta vida

        // Mostrar vida actualizada del enemigo
        cout << "Vida del enemigo después del ataque: " << enemigo.getVida() << endl;

        if (enemigo.getVida() <= 0) // si el enemigo tiene 0 de vida el combate termina
        {
            // Mensaje de confirmacion que el enemigo ha sido derrotado
            cout << "Enemigo derrotado" << endl;
        }

        cout << "El enemigo ataca con: " << enemigo.getAtaque() << "de daño" << endl; // el enemigo ataca
        jugador.recibirDanio(enemigo.getAtaque());                                    // Se calcula el daño y se le resta al jugador

        cout << "Vida del jugador despues del ataque" << jugador.getVida()<< endl;

        // ¿El jugador ha muerto?
        if (jugador.getVida() <= 0) // Se valida que si getVida llega a 0 el jugador esta muerto
        {
            // Mensaje de confirmacion que el jugador esta derrotado
            cout << "Has sido derrotado..." << endl;
        }

        // Se muestran las estadisticas finales del jugador y del enemigo
        jugador.mostrarStats();
        enemigo.mostrarStats();
    }

    cout << "Fin del combate" << endl;
}
