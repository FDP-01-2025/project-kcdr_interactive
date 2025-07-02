#ifndef UNIQUE_CHARACTER_H
#define UNIQUE_CHARACTER_H

#include <iostream>
#include <string>
#include "characters_draw.h" // Para usar funciones de dibujo
#include "Player.h"          // Clase Player
#include "map.h"             // Para usar el mapa y sus dimensiones

// Creamos las instancias de los personajes como objetos de la clase Player
const Player allCharacters[4] = {
    Player(60, 100, 40, 120),   // Rhaekor
    Player(80, 40, 100, 60),    // Cerephios
    Player(100, 60, 60, 90),    // Kaelren
    Player(70, 80, 70, 100)     // Valdrik
};

// Nombre de cada personaje, para identificar cuál se ha elegido
const std::string characterNames[4] = {
    "Rhaekor", "Cerephios", "Kaelren", "Valdrik"
};

// Variable global que guarda el personaje elegido por el jugador
Player playerSelected(0, 0, 0, 0); // Inicialización vacía por defecto
std::string selectedName;         // Nombre del personaje seleccionado

// Muestra el menú de selección y guarda el personaje elegido
void chooseCharacterAndSave() {
    int option;

    std::cout << "\n=== CHARACTER SELECTION ===\n";
    for (int i = 0; i < 4; ++i) {
        std::cout << i + 1 << ". " << characterNames[i]
                  << " (HP: " << allCharacters[i].getHealth()
                  << ", ATK: " << allCharacters[i].getAttack()
                  << ", DEF: " << allCharacters[i].getDefense()
                  << ", ESP: " << allCharacters[i].getSpecialAttack() << ")\n";
    }

    std::cout << "Select (1-4): ";
    std::cin >> option;

    if (option < 1 || option > 4) {
        std::cout << "Invalid selection. Defaulting to Rhaekor.\n";
        playerSelected = allCharacters[0];
        selectedName = characterNames[0];
    } else {
        playerSelected = allCharacters[option - 1];
        selectedName = characterNames[option - 1];
    }

    // Set the player's name to the selected character name
    playerSelected.setName(selectedName);
    
    std::cout << "You have selected: " << selectedName << std::endl;
}

// Dibuja automáticamente al personaje elegido según su nombre
void drawSelectedCharacter(char map[ROWS][COLUMNS], int row, int col) {
    if (selectedName == "Rhaekor")
        drawRhaekor(map, row, col);
    else if (selectedName == "Cerephios")
        drawCerephios(map, row, col);
    else if (selectedName == "Kaelren")
        drawKaelren(map, row, col);
    else if (selectedName == "Valdrik")
        drawValdrik(map, row, col);
}

#endif // UNIQUE_CHARACTER_H

