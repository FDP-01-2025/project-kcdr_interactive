#ifndef UNIQUE_CHARACTER_H // Header guard start: prevents double inclusion
#define UNIQUE_CHARACTER_H

#include <iostream>          // For input/output streams
#include <string>            // For using std::string
#include "characters_draw.h" // Contains the drawing functions for characters
#include "mapa.h"            // Contains the map matrix definition (map[FILAS][COLUMNAS])
using namespace std;         // Use the standard namespace to avoid prefixing std::

/* 1. Struct to define the character */
struct Character
{
    string name; // Character's name
    int health;  // Character's health points (HP)
    int attack;  // Character's attack power (ATK)
    int defense; // Character's defense power (DEF)
    int special; // Character's special ability power (ESP)
};

/* 2. Fixed list (array) of available characters */
const Character allCharacters[4] = {
    {"Rhaekor", 60, 100, 40, 120},
    {"Cerephios", 80, 40, 100, 60},
    {"Kaelren", 100, 60, 60, 90},
    {"Valdrik", 70, 80, 70, 100}};

/* 3. Global variable for the selected character
      Accessible from main.cpp or other files */
Character player;

/* 4. Function to select and uniquely define the character */
void chooseCharacterAndSave()
{
    int option; // Variable to store user's choice

    cout << "\n=== CHARACTER SELECTION ===\n";
    // Loop through all available characters and print their stats
    for (int i = 0; i < 4; ++i)
    {
        cout << i + 1 << ". " << allCharacters[i].name
             << " (HP: " << allCharacters[i].health
             << ", ATK: " << allCharacters[i].attack
             << ", DEF: " << allCharacters[i].defense
             << ", ESP: " << allCharacters[i].special << ")\n";
    }
    cout << "Select (1-4): ";
    cin >> option; // Read user input

    // Check if input is invalid (outside 1-4)
    if (option < 1 || option > 4)
    {
        cout << "Invalid selection. Defaulting to Rhaekor.\n";
        player = allCharacters[0]; // Default character assigned
    }
    else
    {
        player = allCharacters[option - 1]; // Assign selected character
    }

    cout << "You have selected: " << player.name << endl;
}

/* 5. Function to automatically draw the selected character on the map
   Takes the map matrix and the coordinates where to draw */
void drawSelectedCharacter(char map[FILAS][COLUMNAS], int row, int col)
{
    if (player.name == "Rhaekor")
        drawRhaekor(map, row, col); // Call Rhaekor's drawing function
    else if (player.name == "Cerephios")
        drawCerephios(map, row, col); // Call Cerephios's drawing function
    else if (player.name == "Kaelren")
        drawKaelren(map, row, col); // Call Kaelren's drawing function
    else if (player.name == "Valdrik")
        drawValdrik(map, row, col); // Call Valdrik's drawing function
}

#endif // End of header guard
