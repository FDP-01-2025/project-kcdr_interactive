#ifndef DIFICULTY_H // Define to check if this file has already been included in another .h
#define DIFICULTY_H // If it hasn't been included anywhere else, this allows it to be used here

// DO NOT INCLUDE "using namespace std;" IN A HEADER FILE BECAUSE IT COULD CAUSE CONFLICTS WITH OTHER .cpp FILES OR NAME DECLARATIONS (GOOD PRACTICE)
#include <iostream>

// Enum to define the difficulty levels
enum Difficulty
{
    EASY = 1,   // Easy difficulty level
    NORMAL = 2, // Normal difficulty level
    HARD = 3    // Hard difficulty level
};

// Class to hold the configuration for each difficulty level
// This class contains the player's and enemy's stats for each difficulty level
class configurationDifficulty
{
public:
    int enemyHealth;
    int enemyAttack;

    configurationDifficulty(int h = 0, int a = 0) // constructor con valires por defecto (0,0)
        : enemyHealth(h), enemyAttack(a)
    {
    } // Se inician los valores con los datos dados
};

configurationDifficulty selectDifficult()
{
    int option;
    do
    {
       std::cout << "Select a difficulty: \n1) Easy\n2) Normal\n3) Hard\n";
    std::cin >> option;

    switch (option)
    {
    case 1:  // Easy                                   
        return configurationDifficulty(-5, -2); // Enemigos mas debiles
        break;
    case 2:     // Nomral                           
        return configurationDifficulty(0, 0); // Enemigos con stats base
        break;
    case 3:
    return configurationDifficulty (10, 5); //Enemigos mas fuertes
    default:
    std:: cout << "Invalid option, reselect a correct difficulty. \n"; //mensaje para mostarle al usario que su opcion no fue valida
        break;
    }
    } while (true); // El ciclo solo termina con un return válido
    
   
}

#endif