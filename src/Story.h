#ifndef STORY_H
#define STORY_H

#include <iostream>
#include <string> // to be able to use string data type
#include "map.h"
class Story
{
public:
//Display Prologue game
    static void showPrologueOnMap();
};

void Story::showPrologueOnMap()
{
    system("cls");

    Map gameMap;
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset();

    // Título y líneas de introducción
    std::string line0 = "Your siblings have been kidnapped by the forces of evil.";
    std::string line1 = "Explore the villages, collect items and gold, fight against your enemies";
    std::string line2 = "and give freedom back to your brothers ";
    std::string line3 = "Your journey begins in the heart of an abandoned town...";
    std::string line4 = "Now, it's your turn to forge your legend and claim the light!";
    std::string line5 = "good luck, warrior";
    std::string line6 = "";
    std::string line7 = "Press any key to begin your adventure...";

    int startRow = 7;
    int l0Col = (COLUMNS - line0.length()) / 2;
    int l1Col = (COLUMNS - line1.length()) / 2;
    int l2Col = (COLUMNS - line2.length()) / 2;
    int l3Col = (COLUMNS - line3.length()) / 2;
    int l4Col = (COLUMNS - line4.length()) / 2;
    int l5Col = (COLUMNS - line5.length()) / 2;
    int l6Col = (COLUMNS - line6.length()) / 2;
    int l7Col = (COLUMNS - line7.length()) / 2;

    for (int i = 0; i < line0.length(); ++i)
        grid[startRow][l0Col + i] = line0[i];
    for (int i = 0; i < line1.length(); ++i)
        grid[startRow + 1][l1Col + i] = line1[i];
    for (int i = 0; i < line2.length(); ++i)
        grid[startRow + 2][l2Col + i] = line2[i];
    for (int i = 0; i < line3.length(); ++i)
        grid[startRow + 4][l3Col + i] = line3[i];
    for (int i = 0; i < line4.length(); ++i)
        grid[startRow + 5][l4Col + i] = line4[i];
    for (int i = 0; i < line5.length(); ++i)
        grid[startRow + 6][l5Col + i] = line5[i];
    for (int i = 0; i < line6.length(); ++i)
        grid[startRow + 7][l6Col + i] = line6[i];
    for (int i = 0; i < line7.length(); ++i)
        grid[startRow + 8][l7Col + i] = line7[i];

    gameMap.display();
    _getch();
}

#endif
