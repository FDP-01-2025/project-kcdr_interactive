#ifndef SAVE_H
#define SAVE_H
#include "Player.h"
#include "configurationDifficulty.h"
#include <string>
#include <fstream>
#include <iostream>

// Guarda el estado completo del juego (jugador + dificultad) en un archivo
void saveGameState(const Player &player, const configurationDifficulty &config, const std::string &filename)
{
    std::ofstream file(filename); // Crea un archivo para escribir datos
    if (file.is_open()) // Verifica si el archivo se abrio correctamente
    { 
        // Guardar stats del jugador
        file << player.getHealth() << ' ' << player.getAttack() << ' ' << player.getDefense() << ' ' << player.getSpecialAttack() << '\n';
        // Guardar configuración de dificultad
        file << config.enemyHealth << ' ' << config.enemyAttack << std::endl;
        file.close();
        std::cout << "Game successfully saved in: " << filename << std::endl;
    }
    else
    {
        std::cout << "The file could not be opened for saving." << std::endl;
    }
}

// Carga el estado completo del juego (jugador + dificultad) desde un archivo
void loadGameState(Player &player, configurationDifficulty &config, const std::string &filename)
{
    std::ifstream file(filename); //Abre el archivo para leer datos
    if (file.is_open()) // Verifica si el archivo se abrio correctamente
    {
        //Variables temporales para guardar los datos que se lean del archivo 
        int health, attack, defense, specialAttack;
        int enemyHealth, enemyAttack;

        // Cargar stats del jugador
        file >> health >> attack >> defense >> specialAttack;
        //Lee los 4 primeros numeros del archivo y crea un nuevo jugador con esos valores 
        player = Player(health, attack, defense, specialAttack);

        // Cargar configuración de dificultad
        file >> enemyHealth >> enemyAttack;
        config = configurationDifficulty(enemyHealth, enemyAttack);

        file.close();
        std::cout << "Game successfully loaded from " << filename << std::endl;
    }
    else
    {
        std::cout << "File could not be opened for uploading." << std::endl;
    }
}
#endif