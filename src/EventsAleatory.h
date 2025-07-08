#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <cstdlib>
#include <conio.h> 
#include <ctime>
#include <string> // For std::string type


// Include the .h files used in random events
#include "Player.h"
#include "Enemy.h"

class Map;
bool Combat(Player &player, Enemy &enemy, Map &map);
void clearScreen();

const int MAX_EVENT_LINES = 6;

// Initialize random events (seed the random number generator)
inline void InitializeEvent()
{
    // srand sets the seed for the random number generator
    // static_cast<unsigned> converts the value
    srand(static_cast<unsigned>(time(0)));
    // Converts the result of time(0) to unsigned type
    // because srand() expects an unsigned int as a seed.
}

// Function that checks if a random encounter occurs
inline bool cheekRandomEncounter(){
    double probality = rand() % 100;
    return (probality < 8); // 8% probability
}

// Function that handles random encounters using the panel system
bool RandomEncounter(Player &player, Map &gameMap, Enemy enemies[]);



#endif
