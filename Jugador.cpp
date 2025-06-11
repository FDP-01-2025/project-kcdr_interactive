#include "Jugador.h" // incluimos el .h de jugador para poder mandar a llamar los valores que creamos
#include <iostream>  // Libreria para poder usar la consola

using namespace std; // incluimos para evitar el uso de ::std en cada linea de codigo (Aca no hay problema en usarlo)

// Mandamos a llamar los datos que declaramos en el .h
Jugador::Jugador(int vida, int ataque, int defensa, int ataque_especial)
    : nombre("Jugador1"), vida(vida), ataque(ataque), defensa(defensa), ataque_especial(ataque_especial) {}

// Muestra los atributos del jugador
void Jugador::mostrarStats() const
{
    cout << "Nombre: " << nombre
         << "\nVida: " << vida
         << "\nAtaque: " << ataque
         << "\nDefensa" << defensa
         << "\n---------------------------\n";
}

void Jugador::recibirDanio(int danio)
{
    int danioReal = danio - defensa;
    if (danioReal < 0)
    {
        danioReal = 0; // Si la defensa es mayor que el daño, daño real es 0
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
