#ifndef STORY_H
#define STORY_H

#include <iostream>
#include <string> // to be able to use string data type

class Story {
public:
//Max. numer of text lines per scene
static const int MAX_LINES = 8;

int PrologueLineCount = 0; //number of text lines
    std::string PrologueText[Story::MAX_LINES];
    int PrologueIndex = 0; // Index to go through story lines
     bool ShowingPrologue = true; // Status to see if the prologue is displayed
    std::string textPanel;

    struct story
    {
        int index;
        char text[100];

    };
    

};

#endif
