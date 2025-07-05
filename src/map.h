#ifndef MAP_H
#define MAP_H

#define ROWS 30           // Number of rows for the game map grid
#define COLUMNS 90        // Number of columns for the game map grid
const int MAX_LINEAS = 7; // Define a constant for the number of columns in the map (width increased)

// ======== LIBRARIES ========
#include <string>   // For std::string operations
#include <iostream> // For input/output operations (cout, cin)
#include <cctype>   // For character manipulation functions (tolower)
#include <cstdlib>  // For system() function to clear console
#include <conio.h>  // For _getch() immediate key capture on Windows
#include "EventsAleatory.h"
#include "BossDraw.h" // Agregar esta línea
#include "Boss.h"     // Agregar esta línea

// Forward declarations to avoid circular dependencies
class Player;
class Enemy;
class GameController;
extern Player playerSelected;
void playGame(); // Forward declaration for the main game loop function
// ======== STRUCTURE MAP CLASS ========
// This class represents building structures (houses, church, etc.)
class StructureMap
{
private:
    std::string name;     // Name of the structure (e.g., "Church", "House")
    std::string asciiArt; // ASCII art representation of the structure

public:
    // Constructor: creates a structure with name and ASCII art
    StructureMap(const std::string &name, const std::string &art) : name(name), asciiArt(art) {}

    // Getter methods to access private data
    std::string getAsciiArt() const { return asciiArt; }         // Returns the ASCII art
    std::string getName() const { return name; }                 // Returns the structure name
    void showArt() const { std::cout << asciiArt << std::endl; } // Displays ASCII art
};

// ======== TOWN STRUCTURES ARRAY ========
// Array containing all building structures available in the town
StructureMap Townmap[5] = {
    // Structure 0: Church - placed in town center
    StructureMap("Iglesia", R"(
     ^
    /_\
   /___\
  |  +  |
  | /_\ |
  | |_| |
 /_|_|_|_\
)"),

    // Structure 1: Normal house type 1
    StructureMap("Normal house", R"(
   ':.
      []_____
     /\      \
    /  \__/\__\
    |  |''''''|
    |  |'|  |'|
    "`"`"    "`
 )"),

    // Structure 2: Normal house type 2
    StructureMap("Normal house", R"(

       `'::::.
        _____A_
       /      /\
      /__/\__/  \
      |" '' "|  |
      |"|  |"|  |
      `"    "`"`"

    )"),

    // Structure 3: Big house type 1
    StructureMap("Big house", R"(
       ':.
         []_____
        /\      \
    ___/  \__/\__\__
   /\___\ |''''''|__\
   ||'''| |'|  |'|''|
   ``"""`"`"    "`""`
        )"),

    // Structure 4: Big house type 2
    StructureMap("Big house", R"(
       `'::::.
        _____A_
       /      /\
    __/__/\__/  \___
   /__|" '' "| /___/\
   |''|"|  |"| |' '||
   `""`"    "`"`""""`
        )"),
};

// ======== MAP CLASS ========
// This class manages the game world grid and display
class Map
{
private:
    int panelLineCount = 0;
    std::string panelTexto[MAX_LINEAS];
    char grid[ROWS][COLUMNS]; // 2D array representing the game world

    // Private method to draw borders and UI elements
    void drawBorders()
    {
        // Draw vertical borders (left and right edges)
        for (int row = 0; row < ROWS; ++row)
        {
            grid[row][0] = '|';           // Left border
            grid[row][COLUMNS - 1] = '|'; // Right border
        }

        // Draw horizontal borders (top, middle separator, bottom)
        for (int col = 0; col < COLUMNS; ++col)
        {
            grid[0][col] = '-';        // Top border
            grid[ROWS - 6][col] = '-'; // Separator line for UI panel
            grid[ROWS - 1][col] = '-'; // Bottom border
        }

        // Add control instructions in the bottom UI panel
        std::string controls = "Move: W/A/S/D | Interact: E | Quit: Q | Map Transitions: Approach edges";
        int startCol = 2;          // Start position for text
        int controlRow = ROWS - 4; // Row for control instructions
        // Write control instructions character by character
        for (int i = 0; i < controls.length() && startCol + i < COLUMNS - 1; i++)
        {
            grid[controlRow][startCol + i] = controls[i];
        }
    }

public:
    void setPanelText(int count, const std::string texto[])
    {
        panelLineCount = count;
        for (int i = 0; i < count && i < MAX_LINEAS; ++i)
            panelTexto[i] = texto[i];
    }

    const std::string *getPanelTexto() const { return panelTexto; }
    int getPanelLineCount() const { return panelLineCount; }
    // Constructor: initializes the  map
    Map()
    {
        clear();       // Clear all cells
        drawBorders(); // Draw UI borders and instructions
    }

    // Provides access to the grid for external modifications
    char (&getGrid())[ROWS][COLUMNS] { return grid; }

    // Clears the interior of the map (keeps borders intact)
    void clear()
    {
        for (int row = 1; row < ROWS - 1; ++row)
        { // Skip top and bottom borders
            for (int col = 1; col < COLUMNS - 1; ++col)
            {                         // Skip left and right borders
                grid[row][col] = ' '; // Fill with empty space
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
};

// Include headers that depend on Map class
#include "enemy_draw.h"
#include "Enemy.h"
#include "Player.h"
#include "combat_system.h"
#include "GameController.h"

// ======== UTILITY FUNCTIONS ========

// Function to draw ASCII art structures on the game map
inline void drawAsciiArt(char gameGrid[ROWS][COLUMNS], const std::string &art, int startRow, int startCol)
{
    int currentRow = 0, currentCol = 0;

    // Process each character in the ASCII art string
    for (char ch : art)
    {
        if (ch == '\n')
        {                   // If newline character
            currentRow++;   // Move to next row
            currentCol = 0; // Reset column position
            continue;
        }

        // Check if position is within map boundaries and not a space
        if (ch != ' ' &&
            startRow + currentRow < ROWS - 6 &&    // Above UI panel
            startCol + currentCol < COLUMNS - 1 && // Within right border
            startRow + currentRow > 0 &&           // Below top border
            startCol + currentCol > 0)
        { // After left border

            gameGrid[startRow + currentRow][startCol + currentCol] = ch;
        }
        currentCol++; // Move to next column
    }
}

// Function to draw text on the game map
inline void drawTextOnMap(char gameGrid[ROWS][COLUMNS], const std::string &text, int row, int startCol)
{
    for (int i = 0; i < text.length() && startCol + i < COLUMNS - 1; i++)
    {
        if (row < ROWS - 6 && row > 0 && startCol + i > 0)
        {
            gameGrid[row][startCol + i] = text[i];
        }
    }
}

// Function to show bush encounter scene
inline void showBushEncounter(Map &gameMap)
{
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid();
    gameMap.reset(); // Clear map and redraw borders
    
    // ASCII art for bush
    std::string bushArt = R"(
     @@@@@@@@
   @@@@@@@@@@@@
  @@@@@@@@@@@@@@
 @@@@@@@@@@@@@@@@
  @@@@@@@@@@@@@@
   @@@@@@@@@@@@
     @@@@@@@@
       ||||
       ||||
)";
    
    // Draw bush in center of map
    int bushRow = 8;
    int bushCol = 35;
    drawAsciiArt(grid, bushArt, bushRow, bushCol);
    
    // Draw encounter text
    std::string message1 = "You sense something in the distance...";
    std::string message2 = "The bushes rustle ominously...";
    std::string message3 = "Press any key to continue...";
    
    int textRow1 = 18;
    int textRow2 = 19;
    int textRow3 = 21;
    
    drawTextOnMap(grid, message1, textRow1, (COLUMNS - message1.length()) / 2);
    drawTextOnMap(grid, message2, textRow2, (COLUMNS - message2.length()) / 2);
    drawTextOnMap(grid, message3, textRow3, (COLUMNS - message3.length()) / 2);
    
    system("cls");
    gameMap.display();
    _getch(); // Solo una llamada a _getch aquí
}

// ======== MAP GENERATION FUNCTIONS ========

// Map 1: Town Center - main hub with church and basic houses
inline void generateCenterTown(char gameGrid[ROWS][COLUMNS])
{
    drawAsciiArt(gameGrid, Townmap[0].getAsciiArt(), 8, 40);
    drawAsciiArt(gameGrid, Townmap[1].getAsciiArt(), 5, 10);
    drawAsciiArt(gameGrid, Townmap[2].getAsciiArt(), 12, 65);
    drawAsciiArt(gameGrid, Townmap[3].getAsciiArt(), 15, 20);

    // Add transition zones (letters that trigger map changes)
    gameGrid[1][45] = 'N';           // North exit (top)
    gameGrid[ROWS - 7][45] = 'S';    // South exit (bottom)
    gameGrid[12][1] = 'W';           // West exit (left)
    gameGrid[12][COLUMNS - 2] = 'E'; // East exit (right)
}

// Map 2: North District - residential area with different house arrangement
inline void generateNorthTown(char gameGrid[ROWS][COLUMNS])
{
    // Different arrangement of structures
    drawAsciiArt(gameGrid, Townmap[2].getAsciiArt(), 8, 40);
    drawAsciiArt(gameGrid, Townmap[0].getAsciiArt(), 5, 10);
    drawAsciiArt(gameGrid, Townmap[1].getAsciiArt(), 12, 65);
    drawAsciiArt(gameGrid, Townmap[3].getAsciiArt(), 15, 20);

    // Return transition to center
    gameGrid[ROWS - 7][45] = 'S'; // South exit back to center
}

// Map 3: South District - another residential area with unique layout
inline void generateSouthTown(char gameGrid[ROWS][COLUMNS])
{
    // Different arrangement from other districts
    drawAsciiArt(gameGrid, Townmap[4].getAsciiArt(), 8, 40);
    drawAsciiArt(gameGrid, Townmap[1].getAsciiArt(), 5, 10);
    drawAsciiArt(gameGrid, Townmap[0].getAsciiArt(), 12, 65);
    drawAsciiArt(gameGrid, Townmap[1].getAsciiArt(), 15, 20);

    // Return transition to center
    gameGrid[1][45] = 'N'; // North exit back to center
}

// Map 4: East District - commercial-looking area with larger buildings
inline void generateEastTown(char gameGrid[ROWS][COLUMNS])
{
    drawAsciiArt(gameGrid, Townmap[0].getAsciiArt(), 8, 40);
    drawAsciiArt(gameGrid, Townmap[1].getAsciiArt(), 5, 10);
    drawAsciiArt(gameGrid, Townmap[2].getAsciiArt(), 12, 65);
    drawAsciiArt(gameGrid, Townmap[3].getAsciiArt(), 15, 20);

    // Return transition to center
    gameGrid[12][1] = 'W'; // West exit back to center
}

// ======== PLAYER AND MAP SYSTEM ========

// Global variables for player state and current map
static int playerX = 16;   // Player's row position
static int playerY = 45;   // Player's column position
static int currentMap = 0; // Current map ID (0=Center, 1=North, 2=South, 3=East)

// Function to generate the appropriate map based on current location
inline void generateCurrentMap(char gameGrid[ROWS][COLUMNS])
{
    switch (currentMap)
    {
    case 0:
        generateCenterTown(gameGrid);
        break; // Generate town center
    case 1:
        generateNorthTown(gameGrid);
        break; // Generate north Town
    case 2:
        generateSouthTown(gameGrid);
        break; // Generate south Town
    case 3:
        generateEastTown(gameGrid);
        break; // Generate east Town
    }
}

// Function to get human-readable map name for display
inline std::string getCurrentMapName()
{
    switch (currentMap)
    {
    case 0:
        return "Town Center";
    case 1:
        return "North District";
    case 2:
        return "South District";
    case 3:
        return "East District";
    default:
        return "Unknown";
    }
}

// Function to get current map ID
inline int getCurrentMapId()
{
    return currentMap;
}

// Function to set current map ID (used when loading game)
inline void setCurrentMapId(int mapId)
{
    currentMap = mapId;
}

// Function to place player character on the map
inline void initializePlayer(char gameGrid[ROWS][COLUMNS])
{
    gameGrid[playerX][playerY] = 'O'; // Place player character 'O' on grid
}

// Function to handle map transitions when player approaches edges
inline bool changeMap(char gameGrid[ROWS][COLUMNS], char transitionChar)
{
    //Validacion para poder comprobar al momento de ir a otro mapa que moto a los 5 enemigos para poder pasar de mapa
    if (!playerSelected.canAdvanceToNextMap())
    {
        //Muestra un mensaje que aun le faltan derrotar enemigos
        std::cout << " You need to defeat " << (5 - playerSelected.getEnemiesKilled())
                  << " more enemies before you can advance to the next area!\n";
        //Muestro un mensaje con los enemigos que faltan por derrotar
        std::cout << "Current enemies defeated: " << playerSelected.getEnemiesKilled() << "/5\n";
        std::cout << "Press any key to continue...";
        _getch();
        return false; // Cannot change map yet
    }

    int newMap = currentMap;            // Default to current map
    int newX = playerX, newY = playerY; // Default to current position

    // Determine destination map and spawn position based on transition character
    switch (transitionChar)
    {
    case 'N': // Going North
        if (currentMap == 0)
        {
            newMap = 1; // Center -> North District
            newX = ROWS - 8;
            newY = 45; // Spawn at bottom of north map
        }
        else if (currentMap == 2)
        {
            newMap = 0; // South District -> Center
            newX = ROWS - 8;
            newY = 45; // Spawn at bottom of center map
        }
        break;

    case 'S': // Going South
        if (currentMap == 0)
        {
            newMap = 2; // Center -> South District
            newX = 2;
            newY = 45; // Spawn at top of south map
        }
        else if (currentMap == 1)
        {
            newMap = 0; // North District -> Center
            newX = 2;
            newY = 45; // Spawn at top of center map
        }
        break;

    case 'E': // Going East
        if (currentMap == 0)
        {
            newMap = 3; // Center -> East District
            newX = 12;
            newY = 2; // Spawn at left side of east map
        }
        break;

    case 'W': // Going West
        if (currentMap == 3)
        {
            newMap = 0; // East District -> Center
            newX = 12;
            newY = COLUMNS - 3; // Spawn at right side of center map
        }
        break;
    }

    // If map actually changed, update player position and map
    if (newMap != currentMap)
    {
        gameGrid[playerX][playerY] = ' '; // Clear old position
        
        // Use new per-map enemy counter system
        int oldMap = currentMap;
        playerSelected.changeToMap(oldMap, newMap);
        
        currentMap = newMap;              // Update current map
        playerX = newX;                   // Update player X position
        playerY = newY;                   // Update player Y position
        
        std::cout << "\nYou have advanced to a new area!\n";
        std::cout << "Enemy counter for this map: " << playerSelected.getEnemiesKilled() << "/5\n";
        std::cout << "Press any key to continue...";
        _getch();
        
        return true; // Signal that map changed
    }

    return false; // No map change occurred
}

// Function to handle player movement
inline bool movePlayer(Map &gameMap, char direction)
{
    char gameGrid[ROWS][COLUMNS];
    // Copy the grid from the Map object
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            gameGrid[i][j] = gameMap.getGrid()[i][j];
        }
    }

    int newX = playerX; // Calculate new X position
    int newY = playerY; // Calculate new Y position

    // Determine new position based on input direction
    switch (direction)
    {
    case 'w':
        newX--;
        break; // Move up (decrease row)
    case 's':
        newX++;
        break; // Move down (increase row)
    case 'a':
        newY--;
        break; // Move left (decrease column)
    case 'd':
        newY++;
        break; // Move right (increase column)
    default:
        return false; // Invalid direction
    }

    // Check if new position is within map boundaries
    if (newX > 0 && newX < ROWS - 6 && newY > 0 && newY < COLUMNS - 1)
    {
        char dest = gameGrid[newX][newY]; // Get character at destination

        // Check if destination is a transition zone
        if (dest == 'N' || dest == 'S' || dest == 'E' || dest == 'W')
        {
            return changeMap(gameGrid, dest); // Attempt map transition
        }

        // Check if destination is walkable (empty space)
        if (dest == ' ' || dest == '.')
        {
            gameGrid[playerX][playerY] = ' '; // Clear old position
            playerX = newX;                   // Update player X
            playerY = newY;                   // Update player Y
            gameGrid[playerX][playerY] = 'O'; // Place player at new position

            // Copy the modified grid back to the Map object
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLUMNS; j++)
                {
                    gameMap.getGrid()[i][j] = gameGrid[i][j];
                }
            }
              // Después del movimiento exitoso, verificar encuentro aleatorio
            if (cheekRandomEncounter()) // 15% de probabilidad
            {
                // Mostrar escena de arbusto con encuentro
                showBushEncounter(gameMap);

                // Manejar encuentro aleatorio
                bool playerSurvived = RandomEncounter(playerSelected, gameMap, enemy);
                
                // Si el jugador no sobrevivió, manejar la muerte
                if (!playerSurvived)
                {
                    handleDeathScreen();
                    return false; // El jugador murió
                }
                // Si sobrevivió, RandomEncounter ya mostró el mensaje de victoria
            }
            return true; // Movimiento exitoso
        }
    }

    return false; // No map change occurred
}

// Function to handle player interaction with environment
inline void interact(Map &gameMap)
{
    char gameGrid[ROWS][COLUMNS];
    // Copy the grid from the Map object
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            gameGrid[i][j] = gameMap.getGrid()[i][j];
        }
    }

    // Check all four adjacent cells around the player
    char adj[4] = {
        gameGrid[playerX - 1][playerY], // Cell above player
        gameGrid[playerX + 1][playerY], // Cell below player
        gameGrid[playerX][playerY - 1], // Cell left of player
        gameGrid[playerX][playerY + 1]  // Cell right of player
    };

    // Check for transition zones adjacent to player
    for (char c : adj)
    {
        if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        {
            if (changeMap(gameGrid, c))
            {           // Attempt map transition
                return; // Exit if map changed
            }
        }
    }

    // Check for building structures adjacent to player
    for (char c : adj)
    {
        if (c == '^' || c == '|' || c == '/' || c == '\\' || c == '_' || c == '+')
        {

            std::cout << "It's a building, but it's closed for now.\n";
            Enemy enemy1 = enemy[11]; // Ejemplo: Slime

            // Draw combat screen with enemy
            Boss boss1 = createBoss1();
            bool playerAlive = CombatBosss(playerSelected, boss1, gameMap);

            if (playerAlive)
            {
                std::cout << "You survived the battle! Continue exploring the map...\n";
                // Aquí la lógica para seguir recorriendo el mapa
            }
            else
            {
                std::cout << "Game Over. Try again.\n";
                // Aquí la lógica para reiniciar o terminar
            }

            std::cout << "Press any key to continue...";
            _getch(); // Wait for key press
            return;
        }
    }

    // No interesting objects nearby
    std::cout << "Nothing interesting nearby.\n";
    std::cout << "Press any key to continue...";
    _getch(); // Wait for key press
}

// ======== MAIN GAME LOOP ========
// Main function that runs the game
inline void playGame()
{
    InitializeEvent();
    Map gameMap; // Create game map instance

    char option; // Variable to store player input
    while (true)
    { // Main game loop
        // Regenerate map for current location
        gameMap.reset();                       // Clear map and redraw borders
        generateCurrentMap(gameMap.getGrid()); // Generate current map structures
        initializePlayer(gameMap.getGrid());   // Place player on map

        system("cls");     // Clear console screen
        gameMap.display(); // Display current map

        // Show current game state information
        std::cout << "Current Map: " << getCurrentMapName() << "\n";
        std::cout << "Player Position: (" << playerX << ", " << playerY << ")\n";
        std::cout << "Enemies Defeated: " << playerSelected.getEnemiesKilled() << "/5";
        if (playerSelected.canAdvanceToNextMap())
        {
           std:: cout << " - Ready to advance! " ;
        }
        

        // Get player input (immediate, no Enter required)
        option = _getch();             // Get single character input
        option = std::tolower(option); // Convert to lowercase

        // Process player input
        if (option == 'q')
            break; // Quit game
        else if (option == 'e')
            interact(gameMap); // Interact with environment
        else
        {
            bool mapChanged = movePlayer(gameMap, option); // Move player
            // If map changed, loop will regenerate everything automatically
        }
    }
}

bool RandomEncounter(Player &player, Map &gameMap, Enemy enemies[])
{
    // Seleccionar enemigo aleatorio
    int randomEnemyIndex = rand() % 6;
    Enemy wildEnemy = enemies[randomEnemyIndex];

    // Iniciar combate directamente sin pausas adicionales
    bool playerSurvived = Combat(player, wildEnemy, gameMap);
    
    return playerSurvived;
}

#endif // MAP_H