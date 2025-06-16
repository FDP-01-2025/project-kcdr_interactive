#ifndef TOWNMAP_H
#define TOWNMAP_H

#include <iostream>
#include <string> // to be able to use string data type

const int ROWS = 30;
const int COLUMNS = 50;

class Map {
private:
    char map[ROWS][COLUMNS];
    int playerX, playerY;

public:
    Map();
    void displayMap() const;
    void movePlayer(char direction);
    void interact();
    void play();
};

#endif
