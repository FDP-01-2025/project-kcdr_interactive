#ifndef TOWNMAP_H
#define TOWNMAP_H

#include <iostream>
#include <string> // to be able to use string data type

#include "../src/Story.h"

const int ROWS = 30;
const int COLUMNS = 50;

class Map {
private:
    char map[ROWS][COLUMNS];
    int playerX, playerY;

    Story storyP;

public:
    Map();
    void DisplayPrologue();
    void GeneratePrologue(int lineCount, std::string text[Story::MAX_LINES]);
    void displayMap() const;
    void movePlayer(char direction);
    void interact();
    void play();
};

#endif
