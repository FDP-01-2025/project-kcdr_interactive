#ifndef EVENTO_H
#define EVENTO_H

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <string> // para poder usar cadenas de texto

// Se incluyen los archivos .h que van a ser utilizados en los eventos aleatorios
#include "Enemigo.h"

// Inicializar los eventos aleatorios
void InicializarEvento()
{

    // srand establece la semilla para el generador de numeros aleatorios
    // static_cast<unsigned> convierte el valor
    srand(static_cast<unsigned>(time(0)));
    // Convierte el resultado de time(0) al tipo unsigned (número entero sin signo)
    // porque srand() espera un unsigned int como semilla.
}

void VerificarEncuentro()
{

    //variable que devuelve un numero del 0 al 99 
    int probabilidad = rand() % 100;

    if (probabilidad < 25)
    {
        std::cout << "Escuchas un ruido proveniente de los arbustos" << std::endl;
        
    }

    //devuelve un numero del 0 al 2
    int cantidadEnemigo = rand() % 3;

    //Dependiendo del numero que devuelva se muestra un caso o otro
    switch (cantidadEnemigo)
    {
    case 0:
        std::cout << "[Enemigo 1] ha aparecido, derrotalo" << std::endl;
        break;

    case 1:
        std::cout << "[Enemigo 2] ha aparecido, derrotalo" << std::endl;
        break;

    case 2:
        std::cout << "[Enemigo 3] ha aparecido, derrotalo" << std::endl;
        break;

    default:
        std::cout << "Ha ocurrido un error al generar la cantidad de enemigos" << std::endl;
        break;
    }
}

#endif