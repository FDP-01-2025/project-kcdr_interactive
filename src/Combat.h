#ifndef COMBAT_H // ifndef to check if this file has already been included in another .h
#define COMBAT_H // if it hasn't been included anywhere else, this allows it to be used here


#include "Player.h" // Incluir el archivo Jugador.h para poder usar la clase Jugador
#include "Enemy.h" // Incluir el archivo Enemigo.h para poder usar la clase Enemigo
#include "Boss.h" // Incluir archivo Boss.h para poder usar la clase 

void Combat(Player &player, Enemy &enemy);

void CombatBoss(Player &player, Boss &boss);


#endif