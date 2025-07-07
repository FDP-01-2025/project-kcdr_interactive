#ifndef STORY_H
#define STORY_H

#include <iostream>
#include <string> // to be able to use string data type
#include "map.h"
#include <fstream>
#include <conio.h>
class Story
{
public:
    static void showPrologueOnMap();
};

void Story::showPrologueOnMap()
{
    Map gameMap;
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset();

    // Título y líneas de introducción
    std::string title = "Brothers of the Dawn: Fragments of the Alba.";
    std::string line1 = "In a world torn by chaos and darkness,";
    std::string line2 = "a lone hero rises to restore hope.";
    std::string line3 = "Your journey begins in the heart of a forgotten town...";
    std::string line4 = "Face the unknown, forge your legend, and reclaim the light!";
    std::string line5 = "";
    std::string line6 = "Press any key to begin your adventure...";

    int startRow = 7;
    int titleCol = (COLUMNS - title.length()) / 2;
    int l1Col = (COLUMNS - line1.length()) / 2;
    int l2Col = (COLUMNS - line2.length()) / 2;
    int l3Col = (COLUMNS - line3.length()) / 2;
    int l4Col = (COLUMNS - line4.length()) / 2;
    int l5Col = (COLUMNS - line5.length()) / 2;
    int l6Col = (COLUMNS - line6.length()) / 2;

    for (int i = 0; i < title.length(); ++i)
        grid[startRow][titleCol + i] = title[i];
    for (int i = 0; i < line1.length(); ++i)
        grid[startRow + 2][l1Col + i] = line1[i];
    for (int i = 0; i < line2.length(); ++i)
        grid[startRow + 3][l2Col + i] = line2[i];
    for (int i = 0; i < line3.length(); ++i)
        grid[startRow + 5][l3Col + i] = line3[i];
    for (int i = 0; i < line4.length(); ++i)
        grid[startRow + 6][l4Col + i] = line4[i];
    for (int i = 0; i < line5.length(); ++i)
        grid[startRow + 7][l5Col + i] = line5[i];
    for (int i = 0; i < line6.length(); ++i)
        grid[startRow + 9][l6Col + i] = line6[i];

    gameMap.display();
    _getch();
}

#endif
