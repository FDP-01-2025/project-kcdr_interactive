#ifndef MAP_H // Include guard: Prevents the header file from being included multiple times
#define MAP_H

#define ROWS 40 // Define a constant for the number of rows in the map
#define COLUMNS 90
const int MAX_LINEAS = 7; // Define a constant for the number of columns in the map (width increased)

#include <iostream> // Include iostream library for input/output operations

class Map
{ // Define a class named Map
private:
    int panelLineCount = 0;
    std::string panelTexto[MAX_LINEAS];
    char grid[ROWS][COLUMNS]; // 2D array of chars representing the map grid

    void drawBorders()
    { // Private method to draw borders around the map
        // Draw vertical borders
        for (int row = 0; row < ROWS; ++row)
        {                                 // Loop through each row
            grid[row][0] = '|';           // Set the leftmost column of each row to '|'
            grid[row][COLUMNS - 1] = '|'; // Set the rightmost column of each row to '|'
        }

        // Draw horizontal borders
        for (int col = 0; col < COLUMNS; ++col)
        {                              // Loop through each column
            grid[0][col] = '-';        // Top row set to '-' (top border line)
            grid[ROWS - 6][col] = '-'; // Row at ROWS - 6 set to '-' (panel separator line)
            grid[ROWS - 1][col] = '-'; // Bottom row set to '-' (bottom border line)
        }
    }

public:
    void setPanelTexto(int count, const std::string texto[])
    {
        panelLineCount = count;
        for (int i = 0; i < count && i < MAX_LINEAS; ++i)
            panelTexto[i] = texto[i];
    }

    const std::string *getPanelTexto() const { return panelTexto; }
    int getPanelLineCount() const { return panelLineCount; }
    // Constructor: executed when an object of Map is created
    Map()
    {
        clear();       // Clear the interior of the map
        drawBorders(); // Draw the borders on the map
    }

    // Clears the interior of the map (excluding borders)
    void clear()
    {
        for (int row = 1; row < ROWS - 1; ++row)
        { // Loop from second row to second last row
            for (int col = 1; col < COLUMNS - 1; ++col)
            {                         // Loop from second column to second last column
                grid[row][col] = ' '; // Set each cell inside borders to a space (empty)
            }
        }
    }

    // Resets the map: clears the interior and redraws the borders
    void reset()
    {
        clear();       // Clear the interior again
        drawBorders(); // Redraw the borders
    }

    // Displays the entire map grid on the console
    void display() const
    {
        for (int row = 0; row < ROWS; ++row)
        { // For each row
            for (int col = 0; col < COLUMNS; ++col)
            {                                // For each column in the row
                std::cout << grid[row][col]; // Output the character at current position
            }
            std::cout << '\n'; // Move to next line after each row
        }
    }

    // Provides access to the internal map grid for modification outside the class
    char (&getGrid())[ROWS][COLUMNS]
    {
        return grid; // Return a reference to the 2D char array
    }
};

#endif // MAP_H   // End of include guard
