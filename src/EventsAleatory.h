#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string> // to be able to use string data type

// Include the .h files that will be used in the random events
#include "../src/Combat.h"

// Initialize random events
void InitializeEvent()
{
    // srand sets the seed for the random number generator
    // static_cast<unsigned> converts the value
    srand(static_cast<unsigned>(time(0)));
    // Converts the result of time(0) to unsigned type
    // because srand() expects an unsigned int as a seed.
}

void CheckForEncounter()
{
    // Variable that returns a number from 0 to 99
    int probability = rand() % 100;

    if (probability < 25)
    {
        std::cout << "You hear a noise coming from the bushes..." << std::endl;
    }

    // Returns a number from 0 to 2
    int enemyCount = rand() % 3;

    // Depending on the number returned, a different case is shown
    switch (enemyCount)
    {
    case 0:
        std::cout << "[Enemy 1] has appeared, defeat it!" << std::endl;
        break;

    case 1:
        std::cout << "[Enemy 2] has appeared, defeat it!" << std::endl;
        break;

    case 2:
        std::cout << "[Enemy 3] has appeared, defeat it!" << std::endl;
        break;

    default:
        std::cout << "An error occurred while generating the number of enemies." << std::endl;
        break;
    }
}

#endif
