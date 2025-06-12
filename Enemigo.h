#ifndef ENEMIGO_H // ifndef para saber si este archivo ya fue incluido en otro .h
#define ENEMIGO_H // si no ha sido incluido en ningun otro, pues hara que se pueda usar aqui

// NO INCLUIMOS "using namespace std;" EN UN ARCHIVO .h POR QUE PODRIA DAR CONFLICTOS CON ARCHIVOS .cpp O DECLARACION DE NOMBRES (BUENA PRACTICA)

#include <string> // para poder usar cadenas de texto

class Enemigo
{
    // Lo declaramos privado para que solo se puedan hacer modificaciones dentro del archivo .h y que no se puedan modificar dentro de main al momento de incluirlo

private:
    std::string nombre; // Nombre del enemigo para poder diferenciar que tipo de enemigo es
    int vida;           // Atibuto vida que representara la salud que tiene el enemigo
    int ataque;         // Atributo ataque que representara el ataque que tiene el enemigo
    int defensa;        // atributo defensa que representara cuanta defensa tiene el enemigo

public: // Permitimos que el constructor sea publico para poder usarse fuera de la clase por ejemplo usarse en main.cpp
        // Constructor: crea un enemigo con su vida, ataque defensa
    Enemigo(int vida, int ataque, int defensa);

    // Metodos de utilidad, solo sirven para obterner los valores leerlos y mostrarlos y no devuelveen ningun valor (Por eso los inicialiamos con void = vacio)
    void mostrarStats() const;
    void recibirDanio(int danio); // en recibirDanio no le ponemos const por que este dato si queremos que cambie por que segun el ataque que haga el jugador ira bajando

    // Funciones publicas "Getters" para obtener datos de una clase privada
    int getAtaque() const;
    int getVida() const;
    std::string getNombre() const;
};

#endif
