#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <cstdlib>
#include <conio.h> 
#include <ctime>
#include <string> // to be able to use string data type


// Include the .h files that will be used in the random events
#include "Player.h"
#include "Enemy.h"

class Map;
bool Combat(Player &player, Enemy &enemy, Map &map);
void clearScreen();

const int MAX_EVENT_LINES = 6;

// Initialize random events
inline void InitializeEvent()
{
    // srand sets the seed for the random number generator
    // static_cast<unsigned> converts the value
    srand(static_cast<unsigned>(time(0)));
    // Converts the result of time(0) to unsigned type
    // because srand() expects an unsigned int as a seed.
}

// Función que verifica si ocurre un encuentro aleatorio
inline bool cheekRandomEncounter(){
    int probality = rand() % 100;
    return (probality < 0.15);
}

//Funcion que maneja el encuentro aleatorio usando el sistema de paneles
bool RandomEncounter(Player &player, Map &gameMap, Enemy enemies[]);



#endif
