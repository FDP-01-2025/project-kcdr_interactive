#ifndef MAP_H
#define MAP_H

// ======== GRID DIMENSIONS AND CONSTANTS ========
// Define the size of our game world grid - these control the playable area
#define ROWS 30           // Total number of rows in the game map (vertical size)
#define COLUMNS 90        // Total number of columns in the game map (horizontal size)
const int MAX_LINEAS = 7; // Maximum number of text lines that can be displayed in message panels

// ======== ZONE-BASED ENEMY SYSTEM ========
// The game now features different enemy types in each map area for progression:
// - Town Center (Map 0): Basic enemies (indices 0-2) - Slime, Goblin, Orc
// - North District (Map 1): Intermediate enemies (indices 3-5) - Wraith, Gremlin, Skeleton
// - South District (Map 2): Advanced enemies (indices 6-8) - Bat, Boar, Ghoul  
// - East District (Map 3): Elite enemies (indices 9-11) - Imp, Golem, Dragonling
// This creates a natural difficulty progression as players explore different areas

// ======== LIBRARIES ========
#include <string>   // For std::string operations
#include <iostream> // For input/output operations (cout, cin)
#include <cctype>   // For character manipulation functions (tolower)
#include <cstdlib>  // For system() function to clear console
#include <conio.h>  // For _getch() immediate key capture on Windows
#include "EventsAleatory.h"
#include "BossDraw.h" // Agregar esta línea
#include "Boss.h"     // Agregar esta línea
#include "InventoryMenu.h"
#include "GameItems.h"  // For shop items

// ======== REQUIRED LIBRARIES ========
// Standard C++ libraries needed for game functionality
#include <string>   // For std::string operations (text handling)
#include <iostream> // For input/output operations (console display, user input)
#include <cctype>   // For character manipulation functions (converting to lowercase)
#include <cstdlib>  // For system() function calls (clearing console screen)
#include <conio.h>  // For _getch() function - immediate key capture without pressing Enter (Windows-specific)

// ======== GAME SYSTEM INCLUDES ========
// Include our custom game systems that this map system depends on
#include "EventsAleatory.h" // Random event generation system (wild encounters)
#include "BossDraw.h"       // Boss character drawing and display functions
#include "Boss.h"           // Boss character class and creation functions

// ======== FORWARD DECLARATIONS ========
// Declare classes and functions that will be defined elsewhere to avoid circular dependencies
// This allows us to reference these types without including their full headers yet
class Player;                     // Player character class - handles player stats, inventory, etc.
class Enemy;                      // Enemy character class - handles enemy stats and behavior
class GameController;             // Main game flow controller - handles menus and game states
class Inventory;                  // Inventory system for items
class Map;                        // Map class for panel display system
extern Player playerSelected;     // Global player instance that persists throughout the game
extern Inventory playerInventory; // Global player inventory

void playGame(); // Main game loop function - will be defined later in this file
void showShopInPanel(Map &gameMap); // Forward declaration for shop panel function

// ======== BUILDING STRUCTURE CLASS ========
// This class represents individual buildings that can be placed on the game map
// Each building has a name and ASCII art representation for visual display
class StructureMap
{
private:
    std::string name;     // Human-readable name of the building (e.g., "Church", "House")
    std::string asciiArt; // Multi-line ASCII art string that visually represents the building

public:
    // Constructor: Creates a new building structure with specified name and visual representation
    // Parameters: name - what to call this building, art - ASCII art string for display
    StructureMap(const std::string &name, const std::string &art) : name(name), asciiArt(art) {}

    // Getter methods: Allow external code to access private data safely
    std::string getAsciiArt() const { return asciiArt; }         // Returns the building's ASCII art
    std::string getName() const { return name; }                 // Returns the building's name
    void showArt() const { std::cout << asciiArt << std::endl; } // Prints the ASCII art to console
};

// ======== PREDEFINED BUILDING COLLECTION ========
// Array containing all available building types that can be placed in the town
// Each building is created with a name and ASCII art using raw string literals R"(...)"
// These buildings will be randomly placed across different map areas
StructureMap Townmap[6] = {
    // Building 0: Church - Main religious building, typically placed in town center
    // Features a cross symbol and bell tower design
    StructureMap("Iglesia", R"(
     ^
    /_\
   /___\
  |  +  |
  | /_\ |
  | |_| |
 /_|   |_\
)"),

    // Building 1: Standard House Type 1 - Basic residential building
    // Simple house design with door and windows
    StructureMap("Normal house", R"(
   ':.
      []_____
     /\      \
    /  \__/\__\
    |  |''''''|
    |  |'|  |'|
    "`"`"    "`
 )"),

    // Building 2: Standard House Type 2 - Alternative residential design
    // Different roof style but similar size to type 1
    StructureMap("Normal house", R"(

       `'::::.
        _____A_
       /      /\
      /__/\__/  \
      |" '' "|  |
      |"|  |"|  |
      `"    "`"`"

    )"),

    // Building 3: Large House Type 1 - Bigger residential building
    // Extended design with more rooms and details
    StructureMap("Big house", R"(
       ':.
         []_____
        /\      \
    ___/  \__/\__\__
   /\___\ |''''''|__\
   ||'''| |'|  |'|''|
   ``"""`"`"    "`""`
        )"),

    // Building 4: Large House Type 2 - Alternative large residential design
    // Different architectural style but similar size to type 1 large house
    StructureMap("Big house", R"(
       `'::::.
        _____A_
       /      /\
    __/__/\__/  \___
   /__|" '' "| /___/\
   |''|"|  |"| |' '||
   `""`"    "`"`""""`
        )"),

    // Building 5: store - Here you can obtain items that will help you in your adventure.
    StructureMap("Shop", R"(
   ':.
     _________
    /  \______\
    |  |''ST''|
    |  |'|  |'|
    "`"`"    "`
 )"),
};

// ======== MAIN MAP MANAGEMENT CLASS ========
// This class handles the game world display, message panels, and grid management
// It's responsible for drawing the playable area, UI elements, and managing text messages
class Map
{
private:
    // Message panel system - displays important game information to the player
    int panelLineCount = 0;             // Number of text lines currently stored in the message panel
    std::string panelTexto[MAX_LINEAS]; // Array to store text lines for the message panel
    char grid[ROWS][COLUMNS];           // 2D character array representing the entire game world

    // Private method to create the visual borders and UI elements around the playable area
    void drawBorders()
    {
        // Create vertical borders on the left and right edges of the screen
        // These prevent the player from moving outside the playable area
        for (int row = 0; row < ROWS; ++row)
        {
            grid[row][0] = '|';           // Left border - vertical line character
            grid[row][COLUMNS - 1] = '|'; // Right border - vertical line character
        }

        // Create horizontal borders at top, bottom, and separate the UI panel
        for (int col = 0; col < COLUMNS; ++col)
        {
            grid[0][col] = '-';        // Top border - horizontal line
            grid[ROWS - 6][col] = '-'; // UI panel separator - divides game area from info panel
            grid[ROWS - 1][col] = '-'; // Bottom border - horizontal line
        }

        // Add control instructions in the bottom UI panel
        std::string controls = "Move: W/A/S/D | Interact: E | Inventory: I | Quit: Q | Map Transitions: Approach edges";
        int startCol = 2;          // Start position for text
        int controlRow = ROWS - 4; // Row for control instructions
        // Write control instructions character by character

        for (int i = 0; i < controls.length() && startCol + i < COLUMNS - 1; i++)
        {
            grid[controlRow][startCol + i] = controls[i];
        }
    }

public:
    // ======== MESSAGE PANEL MANAGEMENT ========
    // These methods handle the text message system that displays information during combat and events

    // Set text content for the message panel (used for combat messages, encounter notifications, etc.)
    // Parameters: count - number of text lines to display, texto - array of strings containing the messages
    void setPanelText(int count, const std::string texto[])
    {
        panelLineCount = count; // Store how many lines we're displaying
        // Copy each text line into our internal storage, respecting the maximum line limit
        for (int i = 0; i < count && i < MAX_LINEAS; ++i)
            panelTexto[i] = texto[i];
    }

    // Getter methods to allow other systems (like combat) to access the stored panel text
    const std::string *getPanelTexto() const { return panelTexto; } // Returns pointer to text array
    int getPanelLineCount() const { return panelLineCount; }        // Returns number of active text lines

    // ======== MAP INITIALIZATION ========
    // Constructor: Sets up a fresh map when the object is created
    Map()
    {
        clear();       // Fill the playable area with empty spaces
        drawBorders(); // Create the visual frame and UI elements
    }

    // ======== GRID ACCESS ========
    // Provides direct access to the character grid for external systems to modify
    // This allows other parts of the game to place buildings, enemies, or effects on the map
    char (&getGrid())[ROWS][COLUMNS] { return grid; }

    // ======== MAP AREA MANAGEMENT ========
    // These methods handle clearing and resetting the playable area

    // Clears only the interior playable area while preserving borders and UI elements
    // This is used when we want to redraw the map content without recreating the frame
    void clear()
    {
        // Loop through only the interior cells, skipping the border rows and columns
        for (int row = 1; row < ROWS - 1; ++row)
        {
            for (int col = 1; col < COLUMNS - 1; ++col)
            {
                grid[row][col] = ' '; // Fill each interior cell with empty space
            }
        }
    }

    // Completely resets the map: clears content and redraws all visual elements
    // This is used when transitioning between different map areas
    void reset()
    {
        clear();       // Remove all existing content from the playable area
        drawBorders(); // Redraw the frame and UI elements
    }

    // ======== DISPLAY SYSTEM ========
    // Renders the entire map grid to the console screen
    void display() const
    {
        // Print each character in the grid, row by row, to create the visual map
        for (int row = 0; row < ROWS; ++row)
        {
            for (int col = 0; col < COLUMNS; ++col)
            {
                std::cout << grid[row][col]; // Output each character at its position
            }
            std::cout << '\n'; // Move to the next line after completing each row
        }
    }
};

// ======== DEPENDENT SYSTEM INCLUDES ========
// Include headers for systems that depend on the Map class being fully defined
// These must come after the Map class definition to avoid circular dependency issues
#include "enemy_draw.h"     // Enemy visual representation and drawing functions
#include "Enemy.h"          // Enemy class definition and behavior
#include "Player.h"         // Player class definition and stats management
#include "combat_system.h"  // Combat mechanics and battle flow
#include "GameController.h" // Main game state management and menu systems

// ======== UTILITY FUNCTIONS FOR MAP MANIPULATION ========

// Function to place multi-line ASCII art onto the game map at specified coordinates
// This is used to draw buildings, decorations, and other visual elements
// Parameters: gameGrid - the map grid to draw on, art - ASCII art string, startRow/startCol - position to begin drawing
inline void drawAsciiArt(char gameGrid[ROWS][COLUMNS], const std::string &art, int startRow, int startCol)
{
    int currentRow = 0, currentCol = 0; // Track our position within the ASCII art

    // Process each character in the ASCII art string one by one
    for (char ch : art)
    {
        if (ch == '\n')
        {                   // When we encounter a newline character
            currentRow++;   // Move to the next row in the art
            currentCol = 0; // Reset to the beginning of the new row
            continue;       // Skip to the next character
        }

        // Only place the character if it meets all boundary and visibility conditions
        if (ch != ' ' &&                           // Skip empty spaces (preserve existing map content)
            startRow + currentRow < ROWS - 6 &&    // Don't draw into the UI panel area
            startCol + currentCol < COLUMNS - 1 && // Stay within the right border
            startRow + currentRow > 0 &&           // Stay below the top border
            startCol + currentCol > 0)             // Stay to the right of the left border
        {
            // Place the character at the calculated position on the game grid
            gameGrid[startRow + currentRow][startCol + currentCol] = ch;
        }
        currentCol++; // Move to the next column position for the next character
    }
}

// Function to write a single line of text onto the game map at specified coordinates
// This is used for labels, messages, and other text-based information displayed on the map
// Parameters: gameGrid - the map to write on, text - string to display, row - vertical position, startCol - horizontal starting position
inline void drawTextOnMap(char gameGrid[ROWS][COLUMNS], const std::string &text, int row, int startCol)
{
    // Write each character of the text string to consecutive positions on the specified row
    for (int i = 0; i < text.length() && startCol + i < COLUMNS - 1; i++)
    {
        // Ensure we're writing within valid map boundaries (not in borders or UI area)
        if (row < ROWS - 6 && row > 0 && startCol + i > 0)
        {
            gameGrid[row][startCol + i] = text[i]; // Place each character at its calculated position
        }
    }
}

// Function to create and display the bush encounter scene before wild battles
// This provides visual feedback when a random encounter is triggered during exploration
// Parameter: gameMap - reference to the map object that will display the encounter scene
inline void showBushEncounter(Map &gameMap)
{
    char (&grid)[ROWS][COLUMNS] = gameMap.getGrid(); // Get direct reference to the map's character grid
    gameMap.reset();                                 // Clear the current map and redraw borders for a clean encounter scene

    // Define ASCII art for a bush using raw string literal - this represents the source of the encounter
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

    // Position the bush in the center of the map for dramatic effect
    int bushRow = 8;                               // Vertical position (roughly center of playable area)
    int bushCol = 35;                              // Horizontal position (roughly center of map width)
    drawAsciiArt(grid, bushArt, bushRow, bushCol); // Place the bush art on the map

    // Create atmospheric text messages that build tension before the encounter
    std::string message1 = "You sense something in the distance..."; // Initial warning message
    std::string message2 = "The bushes rustle ominously...";         // Building suspense
    std::string message3 = "Press any key to continue...";           // User interaction prompt

    // Position the text messages below the bush for clear visibility
    int textRow1 = 18; // First message row
    int textRow2 = 19; // Second message row
    int textRow3 = 21; // Instruction row (with extra space)

    // Center each message horizontally on the screen for better presentation
    drawTextOnMap(grid, message1, textRow1, (COLUMNS - message1.length()) / 2);
    drawTextOnMap(grid, message2, textRow2, (COLUMNS - message2.length()) / 2);
    drawTextOnMap(grid, message3, textRow3, (COLUMNS - message3.length()) / 2);

    // Display the encounter scene to the player
    system("cls");     // Clear the console screen
    gameMap.display(); // Show the bush encounter scene
    // Note: _getch() pause is intentionally removed here - it will be handled by the calling RandomEncounter() function
}

// ======== MAP AREA GENERATION FUNCTIONS ========
// These functions create different town districts with unique building layouts
// Each function places buildings from the Townmap array at specific coordinates to create varied environments

// Map Area 1: Town Center - The main hub where players begin their journey
// Features the church as a central landmark with houses arranged around it
inline void generateCenterTown(char gameGrid[ROWS][COLUMNS])
{
    // Place shop on the left side
    drawAsciiArt(gameGrid, Townmap[5].getAsciiArt(), 8, 5); // Shop on left side

    // Place other buildings with adjusted positions
    drawAsciiArt(gameGrid, Townmap[0].getAsciiArt(), 4, 56);  // Church
    drawAsciiArt(gameGrid, Townmap[1].getAsciiArt(), 4, 25);  // Normal house type 1
    drawAsciiArt(gameGrid, Townmap[2].getAsciiArt(), 14, 70); // Normal house type 2
    drawAsciiArt(gameGrid, Townmap[3].getAsciiArt(), 14, 35); // Big house type 1

    // Create transition zones - special characters that trigger map changes when the player approaches
    gameGrid[1][45] = 'N';           // North exit at top center
    gameGrid[ROWS - 7][45] = 'S';    // South exit at bottom center
    gameGrid[12][1] = 'W';           // West exit at left side
    gameGrid[12][COLUMNS - 2] = 'E'; // East exit at right side
}

// Map Area 2: North District
inline void generateNorthTown(char gameGrid[ROWS][COLUMNS])
{
    // Place shop on the left side
    drawAsciiArt(gameGrid, Townmap[5].getAsciiArt(), 10, 5); // Shop on left side

    // Arrange buildings in a different pattern than the center town for visual variety
    drawAsciiArt(gameGrid, Townmap[2].getAsciiArt(), 4, 45);  // Normal house type 2
    drawAsciiArt(gameGrid, Townmap[0].getAsciiArt(), 4, 25);  // Church
    drawAsciiArt(gameGrid, Townmap[1].getAsciiArt(), 12, 70); // Normal house type 1
    drawAsciiArt(gameGrid, Townmap[3].getAsciiArt(), 14, 35); // Big house type 1

    // Create return transition - only one exit back to the center (prevents getting lost)
    gameGrid[ROWS - 7][45] = 'S'; // South exit returns to Town Center
}

// Map Area 3: South District
inline void generateSouthTown(char gameGrid[ROWS][COLUMNS])
{
    // Place shop on the left side
    drawAsciiArt(gameGrid, Townmap[5].getAsciiArt(), 10, 5); // Shop on left side

    // Use different building arrangements to create a unique feel for this district
    drawAsciiArt(gameGrid, Townmap[4].getAsciiArt(), 8, 45);  // Big house type 2
    drawAsciiArt(gameGrid, Townmap[1].getAsciiArt(), 5, 25);  // Normal house type 1
    drawAsciiArt(gameGrid, Townmap[0].getAsciiArt(), 13, 70); // Church
    drawAsciiArt(gameGrid, Townmap[1].getAsciiArt(), 15, 35); // Normal house type 1

    // Create return transition to center
    gameGrid[1][45] = 'N'; // North exit returns to Town Center
}

// Map Area 4: East District
inline void generateEastTown(char gameGrid[ROWS][COLUMNS])
{
    // Place shop on the left side
    drawAsciiArt(gameGrid, Townmap[5].getAsciiArt(), 12, 5); // Shop on left side

    // Arrange buildings to suggest a commercial district with mixed architecture
    drawAsciiArt(gameGrid, Townmap[0].getAsciiArt(), 3, 65);  // Church
    drawAsciiArt(gameGrid, Townmap[1].getAsciiArt(), 5, 25);  // Normal house type 1
    drawAsciiArt(gameGrid, Townmap[2].getAsciiArt(), 12, 70); // Normal house type 2
    drawAsciiArt(gameGrid, Townmap[4].getAsciiArt(), 15, 35); // Big house type 2

    // Create return transition to center
    gameGrid[12][1] = 'W'; // West exit returns to Town Center
}

// ======== PLAYER POSITION AND MAP STATE MANAGEMENT ========
// These global variables track the player's current location and which map area they're exploring

// Player coordinate system - tracks exact position within the current map
static int playerX = 14;   // Player's row position (vertical coordinate) - starts in middle of map
static int playerY = 45;   // Player's column position (horizontal coordinate) - starts in center horizontally
static int currentMap = 0; // Current map area identifier: 0=Center, 1=North, 2=South, 3=East District

// ======== MAP GENERATION DISPATCHER ========
// Function to generate the appropriate map layout based on the player's current location
// This centralizes map generation and makes it easy to add new areas
inline void generateCurrentMap(char gameGrid[ROWS][COLUMNS])
{
    // Use a switch statement to call the appropriate map generation function
    switch (currentMap)
    {
    case 0:
        generateCenterTown(gameGrid); // Generate the main town center hub
        break;
    case 1:
        generateNorthTown(gameGrid); // Generate the northern residential district
        break;
    case 2:
        generateSouthTown(gameGrid); // Generate the southern residential district
        break;
    case 3:
        generateEastTown(gameGrid); // Generate the eastern commercial district
        break;
        // Note: Additional cases can be added here for future map expansions
    }
}

// ======== MAP INFORMATION ACCESS FUNCTIONS ========
// These utility functions provide information about the current map state to other game systems

// Returns a human-readable name for the current map area for display purposes
// Used in the UI to show the player which district they're currently exploring
inline std::string getCurrentMapName()
{
    switch (currentMap)
    {
    case 0:
        return "Town Center"; // The main hub area
    case 1:
        return "North District"; // Northern residential area
    case 2:
        return "South District"; // Southern residential area
    case 3:
        return "East District"; // Eastern commercial area
    default:
        return "Unknown"; // Fallback for invalid map IDs
    }
}

// Returns the numeric ID of the current map for save/load operations and internal logic
inline int getCurrentMapId()
{
    return currentMap;
}

// Sets the current map ID - used when loading a saved game to restore the player's location
// Parameter: mapId - the map area to set as current (should match one of the valid map IDs)
inline void setCurrentMapId(int mapId)
{
    currentMap = mapId;
}

// ======== PLAYER PLACEMENT FUNCTION ========
// Function to place the player character on the map at their current coordinates
// Parameter: gameGrid - the map grid where the player character will be drawn
inline void initializePlayer(char gameGrid[ROWS][COLUMNS])
{
    gameGrid[playerX][playerY] = 'O'; // Place the player character 'O' at their current position on the grid
}

// ======== MAP TRANSITION SYSTEM ========
// Function to handle transitions between different map areas when the player approaches transition zones
// This implements the progression system where players must defeat enemies before advancing
// Parameters: gameGrid - current map grid, transitionChar - the character representing the transition direction
inline bool changeMap(char gameGrid[ROWS][COLUMNS], char transitionChar)
{
    // ======== PROGRESSION GATE CHECK ========
    // Validate that the player has defeated enough enemies to advance to the next area
    // This creates a gameplay requirement and prevents players from skipping combat
    if (!playerSelected.canAdvanceToNextMap())
    {
        // Display informative message about why the transition is blocked
        std::cout << " You need to defeat " << (5 - playerSelected.getEnemiesKilled())
                  << " more enemies before you can advance to the next area!\n";

        // Show current progress to help the player understand their goal
        std::cout << "Current enemies defeated: " << playerSelected.getEnemiesKilled() << "/5\n";
        std::cout << "Press any key to continue...";
        _getch();     // Wait for player acknowledgment before continuing
        return false; // Prevent the map change and keep player in current area
    }

    // ======== TRANSITION CALCULATION ========
    // Initialize destination variables with current values (default to no change)
    int newMap = currentMap;            // Destination map ID
    int newX = playerX, newY = playerY; // Destination coordinates for player spawn

    // Determine destination map and spawn position based on the transition direction
    switch (transitionChar)
    {
    case 'N': // Moving North
        if (currentMap == 0)
        {
            // Center -> North District transition
            newMap = 1;
            newX = ROWS - 8; // Spawn near bottom of north map (coming from south)
            newY = 45;       // Keep horizontal center position
        }
        else if (currentMap == 2)
        {
            // South District -> Center transition
            newMap = 0;
            newX = ROWS - 8; // Spawn near bottom of center map
            newY = 45;       // Keep horizontal center position
        }
        break;

    case 'S': // Moving South
        if (currentMap == 0)
        {
            // Center -> South District transition
            newMap = 2;
            newX = 2;  // Spawn near top of south map (coming from north)
            newY = 45; // Keep horizontal center position
        }
        else if (currentMap == 1)
        {
            // North District -> Center transition
            newMap = 0;
            newX = 2;  // Spawn near top of center map
            newY = 45; // Keep horizontal center position
        }
        break;

    case 'E': // Moving East
        if (currentMap == 0)
        {
            // Center -> East District transition
            newMap = 3;
            newX = 12; // Keep vertical center position
            newY = 2;  // Spawn near left side of east map (coming from west)
        }
        break;

    case 'W': // Moving West
        if (currentMap == 3)
        {
            // East District -> Center transition
            newMap = 0;
            newX = 12;          // Keep vertical center position
            newY = COLUMNS - 3; // Spawn near right side of center map (coming from east)
        }
        break;
    }

    // ======== EXECUTE TRANSITION ========
    // Only proceed if we calculated a valid destination different from current location
    if (newMap != currentMap)
    {
        gameGrid[playerX][playerY] = ' '; // Clear the player's current position on the old map

        // ======== PER-MAP ENEMY COUNTER SYSTEM ========
        // Update the enemy counter system to track progress per map area
        int oldMap = currentMap;
        playerSelected.changeToMap(oldMap, newMap); // Notify player object of map change

        // ======== UPDATE PLAYER STATE ========
        currentMap = newMap; // Set the new current map
        playerX = newX;      // Update player's vertical position
        playerY = newY;      // Update player's horizontal position

        // ======== PROVIDE FEEDBACK ========
        // Inform the player about the successful transition and their progress
        std::cout << "\nYou have advanced to a new area!\n";
        std::cout << "Enemy counter for this map: " << playerSelected.getEnemiesKilled() << "/5\n";
        std::cout << "Press any key to continue...";
        _getch(); // Wait for player acknowledgment

        return true; // Signal that the map change was successful
    }

    return false; // No valid transition occurred - stay in current map
}

// ======== PLAYER MOVEMENT SYSTEM ========
// Function to handle player movement and all related game mechanics (collisions, encounters, map transitions)
// This is one of the core gameplay functions that processes player input and triggers game events
// Parameters: gameMap - reference to the map object, direction - character representing movement direction (w/a/s/d)
inline bool movePlayer(Map &gameMap, char direction)
{
    // ======== GRID SYNCHRONIZATION ========
    // Create a local copy of the map grid for manipulation
    // This ensures we can modify the grid without affecting the original until we're ready
    char gameGrid[ROWS][COLUMNS];
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            gameGrid[i][j] = gameMap.getGrid()[i][j]; // Copy each character from the map
        }
    }

    // ======== MOVEMENT CALCULATION ========
    // Calculate the new position based on the player's input direction
    int newX = playerX; // Start with current vertical position
    int newY = playerY; // Start with current horizontal position

    // Determine new coordinates based on movement direction
    switch (direction)
    {
    case 'w':
        newX--; // Move up (decrease row number)
        break;
    case 's':
        newX++; // Move down (increase row number)
        break;
    case 'a':
        newY--; // Move left (decrease column number)
        break;
    case 'd':
        newY++; // Move right (increase column number)
        break;
    default:
        return false; // Invalid direction - no movement occurs
    }

    // ======== BOUNDARY VALIDATION ========
    // Check if the calculated new position is within valid map boundaries
    // This prevents the player from moving into borders or the UI panel area
    if (newX > 0 && newX < ROWS - 6 && newY > 0 && newY < COLUMNS - 1)
    {
        char dest = gameGrid[newX][newY]; // Get the character at the destination position

        // ======== TRANSITION ZONE DETECTION ========
        // Check if the destination contains a map transition character
        if (dest == 'N' || dest == 'S' || dest == 'E' || dest == 'W')
        {
            return changeMap(gameGrid, dest); // Attempt to transition to a new map area
        }

        // ======== WALKABLE SPACE VALIDATION ========
        // Check if the destination is a space the player can actually move to
        if (dest == ' ' || dest == '.')
        {
            // ======== EXECUTE MOVEMENT ========
            gameGrid[playerX][playerY] = ' '; // Clear the player's old position
            playerX = newX;                   // Update player's vertical coordinate
            playerY = newY;                   // Update player's horizontal coordinate
            gameGrid[playerX][playerY] = 'O'; // Place player character at new position

            // ======== GRID SYNCHRONIZATION ========
            // Copy our modified grid back to the Map object to make changes persistent
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLUMNS; j++)
                {
                    gameMap.getGrid()[i][j] = gameGrid[i][j];
                }
            }

            // ======== RANDOM ENCOUNTER SYSTEM ========
            // After successful movement, check if a random encounter should occur
            if (cheekRandomEncounter()) // Function returns true with 15% probability
            {
                // ======== ENCOUNTER SCENE PRESENTATION ========
                // Display the atmospheric bush encounter scene to build tension
                showBushEncounter(gameMap);

                // ======== BATTLE EXECUTION ========
                // Start the random encounter battle - this function handles the entire combat sequence
                bool playerSurvived = RandomEncounter(playerSelected, gameMap, enemy);

                // ======== DEATH HANDLING ========
                // If the player died in combat, handle the death sequence
                if (!playerSurvived)
                {
                    GameMenu::displayDeathScreen(); // Show death screen with options
                    return false;                   // Signal that the player died (stops movement processing)
                }
                // If player survived, the RandomEncounter function already displayed victory message
            }
            return true; // Movement was successful
        }
    }

    return false; // Movement failed due to boundaries or obstacles
}

// ======== PLAYER INTERACTION SYSTEM ========
// Function to handle player interactions with the environment when pressing the 'E' key
// This allows players to interact with buildings, transition zones, and other map elements
// Parameter: gameMap - reference to the current map object for grid access
inline void interact(Map &gameMap)
{
    // ======== GRID ACCESS SETUP ========
    // Create a local copy of the map grid for examination
    char gameGrid[ROWS][COLUMNS];
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            gameGrid[i][j] = gameMap.getGrid()[i][j];
        }
    }

    // ======== SHOP DETECTION ========
    // Check for shop interaction by looking for "ST" text directly above the player
    /*int checkRow = playerX - 1; // One row above the player
    int checkCol = playerY - 1; // Starting column for "ST" check

    // Verify boundaries and look for "ST" pattern directly above player
    if (checkRow >= 0 && checkRow < ROWS &&
        checkCol >= 0 && checkCol < COLUMNS - 1)
    {

        // Look for "ST" pattern which is unique to shops at playerY-1 position
        if (gameGrid[checkRow][checkCol] == 'S' && gameGrid[checkRow][checkCol + 1] == 'T')
        {
            // Execute shop menu
            InventoryMenu::displayShopMenu();
            return; // Exit interaction function
        }
    }*/

    // ======== ADJACENT CELL DETECTION ========
    // Check all four cells adjacent to the player's current position
    // This array contains the characters in the cells around the player
    char adj[4] = {
        gameGrid[playerX - 1][playerY], // Cell directly above the player
        gameGrid[playerX + 1][playerY], // Cell directly below the player
        gameGrid[playerX][playerY - 1], // Cell directly left of the player
        gameGrid[playerX][playerY + 1]  // Cell directly right of the player
    };

    // ======== TRANSITION ZONE INTERACTION ========
    // Check if any adjacent cell contains a map transition character
    // This allows players to use 'E' to transition between maps instead of walking into the transition
    for (char c : adj)
    {
        if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        {
            if (changeMap(gameGrid, c))
            {
                return; // Exit the interaction function if map transition was successful
            }
        }
    }

    // ======== BUILDING INTERACTION ========
    // Check if any adjacent cell contains part of a building structure
    // These characters represent different parts of ASCII art buildings
    for (char c : adj)
    {
        if(gameGrid[playerX - 1][playerY] == 'S' && gameGrid[playerX - 1][playerY + 1 ]== 'T'
        || gameGrid[playerX - 1][playerY] == 'T' && gameGrid[playerX - 1][playerY - 1 ]== 'S'){

            // Execute shop menu using the new panel system
            ItemFactory::displayShop(playerInventory, playerGold);
            return; // Exit interaction function
        }

        else if(c == '^' || c == '|' || c == '/' || c == '\\' || c == '_' || c == '+')
        {
            // ======== BUILDING INTERACTION ========
            // All buildings now trigger direct boss battles
            std::cout << "\nYou approach a building..." << std::endl;
            std::cout << "A guardian emerges to defend the building!" << std::endl;
            std::cout << "Battle begins!" << std::endl;

            // ======== ENEMY SELECTION ========
            // Select a specific enemy instead of random
            Enemy buildingEnemy = enemy[2]; // Cambia el 0 por el índice del enemigo que quieras
            // Ejemplo: enemy[1], enemy[2], enemy[3], enemy[4], enemy[5]

            // ======== COMBAT EXECUTION ========
            bool playerAlive = Combat(playerSelected, buildingEnemy, gameMap);

            // ======== POST-BATTLE FEEDBACK ========
            if (playerAlive)
            {
                std::cout << "You survived the battle! Continue exploring the map...\n";
            }
            else
            {
                std::cout << "Game Over. Try again.\n";
            }

            // ======== USER ACKNOWLEDGMENT ========
            std::cout << "Press any key to continue...";
            _getch(); // Wait for player to acknowledge the message
            return;   // Exit interaction function
        }
    }

    // ======== DEFAULT INTERACTION RESPONSE ========
    // If no interactable objects are found, provide feedback to the player
    std::cout << "Nothing interesting nearby.\n";
    std::cout << "Press any key to continue...";
    _getch(); // Wait for player acknowledgment
}

// Function to show inventory using the same bordered panel system as the main game
inline void showInventoryInPanel(Map &gameMap)
{
    // ======== INVENTORY PANEL SETUP ========
    // Create a fresh map with borders for the inventory display
    Map inventoryMap;
    char (&grid)[ROWS][COLUMNS] = inventoryMap.getGrid();
    
    // ======== INVENTORY TITLE ========
    std::string title = "INVENTORY";
    int titleRow = 2;
    int titleCol = (COLUMNS - title.length()) / 2;
    drawTextOnMap(grid, title, titleRow, titleCol);
    
    // ======== GOLD DISPLAY ========
    std::string goldText = "Gold: " + std::to_string(playerGold) + " coins";
    int goldRow = 4;
    int goldCol = (COLUMNS - goldText.length()) / 2;
    drawTextOnMap(grid, goldText, goldRow, goldCol);
    
    // ======== INVENTORY ITEMS DISPLAY ========
    // Get inventory items and display them in the main panel area
    int currentRow = 6; // Start below the gold display
    int leftMargin = 5; // Left margin for item list
    bool hasItems = false;
    
    // ======== HEALING ITEMS SECTION ========
    if (playerInventory.getHealingItemCount() > 0) {
        std::string healingHeader = "HEALING ITEMS:";
        drawTextOnMap(grid, healingHeader, currentRow++, leftMargin);
        currentRow++; // Add spacing
        
        // Display each healing item with quantity
        for (int i = 0; i < playerInventory.getHealingItemCount(); i++) {
            const HealingItem& item = playerInventory.getHealingItem(i);
            if (item.getQuantity() > 0) {
                std::string itemText = "  " + item.getName() + ": x" + std::to_string(item.getQuantity());
                drawTextOnMap(grid, itemText, currentRow++, leftMargin);
                hasItems = true;
            }
        }
        currentRow++; // Add spacing after healing items
    }
    
    // ======== DAMAGE ITEMS SECTION ========
    if (playerInventory.getDamageItemCount() > 0) {
        std::string damageHeader = "DAMAGE ITEMS:";
        drawTextOnMap(grid, damageHeader, currentRow++, leftMargin);
        currentRow++; // Add spacing
        
        // Display each damage item with quantity
        for (int i = 0; i < playerInventory.getDamageItemCount(); i++) {
            const DamageItem& item = playerInventory.getDamageItem(i);
            if (item.getQuantity() > 0) {
                std::string itemText = "  " + item.getName() + ": x" + std::to_string(item.getQuantity());
                drawTextOnMap(grid, itemText, currentRow++, leftMargin);
                hasItems = true;
            }
        }
    }
    
    // ======== EMPTY INVENTORY MESSAGE ========
    if (!hasItems) {
        std::string emptyText = "Your inventory is empty";
        int emptyCol = (COLUMNS - emptyText.length()) / 2;
        drawTextOnMap(grid, emptyText, currentRow, emptyCol);
    }
    
    // ======== INSTRUCTION MESSAGES ========
    // Set up the instruction panel message that appears below the game area
    std::string instructions[MAX_LINEAS];
    instructions[0] = "View your collected items and gold";
    instructions[1] = "Items can be used during combat";
    instructions[2] = "Press any key to return to map";
    
    // Apply the instruction panel to the map
    inventoryMap.setPanelText(3, instructions);
    
    // ======== DISPLAY THE INVENTORY PANEL ========
    system("cls");
    inventoryMap.display();
    _getch();
}

// Function to show shop using the same bordered panel system as the main game
inline void showShopInPanel(Map &gameMap)
{
    bool inShop = true;
    
    while (inShop) {
        // ======== SHOP PANEL SETUP ========
        // Create a fresh map with borders for the shop display
        Map shopMap;
        char (&grid)[ROWS][COLUMNS] = shopMap.getGrid();
        
        // ======== SHOP TITLE ========
        std::string title = "MYSTICAL SHOP";
        int titleRow = 2;
        int titleCol = (COLUMNS - title.length()) / 2;
        drawTextOnMap(grid, title, titleRow, titleCol);
        
        // ======== GOLD DISPLAY ========
        std::string goldText = "Your Gold: " + std::to_string(playerGold) + " coins";
        int goldRow = 4;
        int goldCol = (COLUMNS - goldText.length()) / 2;
        drawTextOnMap(grid, goldText, goldRow, goldCol);
        
        // ======== SHOP ITEMS DISPLAY ========
        int currentRow = 6;
        int leftMargin = 10;
        
        drawTextOnMap(grid, "1. Small Health Potion (25 HP) - 10 Gold", currentRow++, leftMargin);
        drawTextOnMap(grid, "2. Medium Health Potion (50 HP) - 25 Gold", currentRow++, leftMargin);
        drawTextOnMap(grid, "3. Throwing Knife (15 DMG) - 15 Gold", currentRow++, leftMargin);
        drawTextOnMap(grid, "4. Grenade (45 DMG) - 40 Gold", currentRow++, leftMargin);
        drawTextOnMap(grid, "5. Magic Elixir (150 HP) - 100 Gold", currentRow++, leftMargin);
        drawTextOnMap(grid, "6. Lightning Bolt (100 DMG) - 150 Gold", currentRow++, leftMargin);
        drawTextOnMap(grid, "7. Exit Shop", currentRow++, leftMargin);
        
        // ======== INSTRUCTION MESSAGES ========
        std::string instructions[MAX_LINEAS];
        instructions[0] = "Welcome to the Mystical Shop!";
        instructions[1] = "Enter item number to purchase";
        instructions[2] = "Choose wisely, adventurer!";
        
        // Apply the instruction panel to the map
        shopMap.setPanelText(3, instructions);
        
        // ======== DISPLAY THE SHOP PANEL ========
        system("cls");
        shopMap.display();
        
        // ======== GET USER INPUT ========
        std::cout << "Choose an item to purchase (1-7): ";
        char choice = _getch();
        int itemChoice = choice - '0'; // Convert char to int
        
        // ======== PROCESS PURCHASE ========
        if (itemChoice == 7) {
            // Exit shop
            inShop = false;
            
            // Show farewell message
            Map farewellMap;
            char (&farewellGrid)[ROWS][COLUMNS] = farewellMap.getGrid();
            
            std::string farewell = "Thank you for visiting!";
            int farewellRow = 10;
            int farewellCol = (COLUMNS - farewell.length()) / 2;
            drawTextOnMap(farewellGrid, farewell, farewellRow, farewellCol);
            
            std::string wishes = "May your journey be prosperous!";
            int wishesRow = 12;
            int wishesCol = (COLUMNS - wishes.length()) / 2;
            drawTextOnMap(farewellGrid, wishes, wishesRow, wishesCol);
            
            std::string exitInstr[MAX_LINEAS];
            exitInstr[0] = "Farewell, brave adventurer!";
            exitInstr[1] = "Press any key to return to map";
            farewellMap.setPanelText(2, exitInstr);
            
            system("cls");
            farewellMap.display();
            _getch();
            
        } else if (itemChoice >= 1 && itemChoice <= 6) {
            // Process item purchase
            bool purchaseSuccess = false;
            std::string itemName = "";
            int itemCost = 0;
            
            switch (itemChoice) {
                case 1:
                    if (playerGold >= 10) {
                        playerGold -= 10;
                        playerInventory.addHealingItem(GameItems::smallPotion);
                        purchaseSuccess = true;
                        itemName = "Small Health Potion";
                        itemCost = 10;
                    }
                    break;
                case 2:
                    if (playerGold >= 25) {
                        playerGold -= 25;
                        playerInventory.addHealingItem(GameItems::mediumPotion);
                        purchaseSuccess = true;
                        itemName = "Medium Health Potion";
                        itemCost = 25;
                    }
                    break;
                case 3:
                    if (playerGold >= 15) {
                        playerGold -= 15;
                        playerInventory.addDamageItem(GameItems::throwingKnife);
                        purchaseSuccess = true;
                        itemName = "Throwing Knife";
                        itemCost = 15;
                    }
                    break;
                case 4:
                    if (playerGold >= 40) {
                        playerGold -= 40;
                        playerInventory.addDamageItem(GameItems::grenade);
                        purchaseSuccess = true;
                        itemName = "Grenade";
                        itemCost = 40;
                    }
                    break;
                case 5:
                    if (playerGold >= 100) {
                        playerGold -= 100;
                        playerInventory.addHealingItem(GameItems::magicElixir);
                        purchaseSuccess = true;
                        itemName = "Magic Elixir";
                        itemCost = 100;
                    }
                    break;
                case 6:
                    if (playerGold >= 150) {
                        playerGold -= 150;
                        playerInventory.addDamageItem(GameItems::lightningBolt);
                        purchaseSuccess = true;
                        itemName = "Lightning Bolt";
                        itemCost = 150;
                    }
                    break;
            }
            
            // ======== SHOW PURCHASE RESULT ========
            Map resultMap;
            char (&resultGrid)[ROWS][COLUMNS] = resultMap.getGrid();
            
            if (purchaseSuccess) {
                std::string successTitle = "PURCHASE SUCCESSFUL!";
                int successRow = 8;
                int successCol = (COLUMNS - successTitle.length()) / 2;
                drawTextOnMap(resultGrid, successTitle, successRow, successCol);
                
                std::string itemText = "You bought: " + itemName;
                int itemRow = 10;
                int itemCol = (COLUMNS - itemText.length()) / 2;
                drawTextOnMap(resultGrid, itemText, itemRow, itemCol);
                
                std::string costText = "Cost: " + std::to_string(itemCost) + " gold";
                int costRow = 11;
                int costCol = (COLUMNS - costText.length()) / 2;
                drawTextOnMap(resultGrid, costText, costRow, costCol);
                
                std::string remainingText = "Remaining Gold: " + std::to_string(playerGold);
                int remainingRow = 13;
                int remainingCol = (COLUMNS - remainingText.length()) / 2;
                drawTextOnMap(resultGrid, remainingText, remainingRow, remainingCol);
                
            } else {
                std::string failTitle = "PURCHASE FAILED!";
                int failRow = 10;
                int failCol = (COLUMNS - failTitle.length()) / 2;
                drawTextOnMap(resultGrid, failTitle, failRow, failCol);
                
                std::string reason = "Not enough gold!";
                int reasonRow = 12;
                int reasonCol = (COLUMNS - reason.length()) / 2;
                drawTextOnMap(resultGrid, reason, reasonRow, reasonCol);
            }
            
            std::string resultInstr[MAX_LINEAS];
            if (purchaseSuccess) {
                resultInstr[0] = "Item added to your inventory!";
                resultInstr[1] = "Thank you for your purchase!";
                resultInstr[2] = "Press any key to continue shopping";
            } else {
                resultInstr[0] = "You need more gold for this item";
                resultInstr[1] = "Defeat enemies to earn more gold";
                resultInstr[2] = "Press any key to continue shopping";
            }
            
            resultMap.setPanelText(3, resultInstr);
            
            system("cls");
            resultMap.display();
            _getch();
            
        } else {
            // Invalid choice
            Map errorMap;
            char (&errorGrid)[ROWS][COLUMNS] = errorMap.getGrid();
            
            std::string errorTitle = "INVALID CHOICE!";
            int errorRow = 10;
            int errorCol = (COLUMNS - errorTitle.length()) / 2;
            drawTextOnMap(errorGrid, errorTitle, errorRow, errorCol);
            
            std::string errorMsg = "Please select a valid option (1-7)";
            int msgRow = 12;
            int msgCol = (COLUMNS - errorMsg.length()) / 2;
            drawTextOnMap(errorGrid, errorMsg, msgRow, msgCol);
            
            std::string errorInstr[MAX_LINEAS];
            errorInstr[0] = "Invalid selection detected";
            errorInstr[1] = "Please choose a number from 1-7";
            errorInstr[2] = "Press any key to try again";
            
            errorMap.setPanelText(3, errorInstr);
            
            system("cls");
            errorMap.display();
            _getch();
        }
    }
}

// ======== MAIN GAME LOOP ========
// Main function that runs the game
// ======== MAIN GAME LOOP SYSTEM ========
// This is the central function that runs the entire gameplay experience
// It handles map display, input processing, and coordinates all game systems
inline void playGame()
{
    // ======== GAME INITIALIZATION ========
    InitializeEvent(); // Set up the random event system for encounters
    Map gameMap;       // Create the main map object that will handle display and message panels

    // ======== MAIN GAMEPLAY LOOP ========
    // This loop continues until the player quits or dies, handling all gameplay interactions
    char option; // Variable to store the player's input character
    while (true)
    {
        // ======== MAP REGENERATION ========
        // Refresh the map display for the current location - this happens every loop iteration
        gameMap.reset();                       // Clear existing content and redraw borders/UI
        generateCurrentMap(gameMap.getGrid()); // Generate buildings and structures for current area
        initializePlayer(gameMap.getGrid());   // Place the player character 'O' at their position

        // ======== SCREEN DISPLAY ========
        system("cls");     // Clear the console screen for a clean display
        gameMap.display(); // Render the complete map with all elements to the screen

        // ======== GAME STATUS INFORMATION ========
        // Display important information below the map for player reference
        std::cout << "Current Map: " << getCurrentMapName();                        // Show which area they're in
        
        // Add zone information to help players understand enemy difficulty
        std::string zoneInfo = "";
        switch (currentMap)
        {
        case 0:
            zoneInfo = " (Basic Enemies)";
            break;
        case 1:
            zoneInfo = " (Intermediate Enemies)";
            break;
        case 2:
            zoneInfo = " (Advanced Enemies)";
            break;
        case 3:
            zoneInfo = " (Elite Enemies)";
            break;
        }
        std::cout << zoneInfo << "\n";
        
        std::cout << "Player Position: (" << playerX << ", " << playerY << ")\n";       // Show exact coordinates (useful for debugging)
        std::cout << "Enemies Defeated: " << playerSelected.getEnemiesKilled() << "/5"; // Show progress toward area completion

        // ======== PROGRESSION STATUS INDICATOR ========
        // Show if the player has met the requirements to advance to new areas
        if (playerSelected.canAdvanceToNextMap())
        {
            std::cout << " - Ready to advance! "; // Visual indicator that progression is unlocked
        }
        std::cout << "\n"; // Add spacing after status information

        // ======== INPUT CAPTURE ========
        // Get immediate player input without requiring Enter key press
        option = _getch();             // Capture single keypress (Windows-specific function)
        option = std::tolower(option); // Convert to lowercase for consistent processing

        // ======== INPUT PROCESSING ========
        // Process the player's input and trigger appropriate game actions
        if (option == 'q')
        {
            // ======== QUIT TO MAIN MENU ========
            // Return to the main menu system when player presses 'Q'
            GameController::runMainMenu(); // Hand control back to the main menu system
            break;                         // Exit the main game loop
        }
        else if (option == 'e')
        {
            // ======== ENVIRONMENT INTERACTION ========
            // Handle interaction with buildings, transition zones, and other map elements
            interact(gameMap); // Interact with environment
        }

        else if (option == 'i')
        {
            showInventoryInPanel(gameMap); // Show inventory using panel system
            // Screen will refresh automatically on next loop iteration
        }
        else
        {
            // ======== MOVEMENT PROCESSING ========
            // Handle all movement-related actions (w/a/s/d keys)
            bool mapChanged = movePlayer(gameMap, option);
            // Note: The loop will automatically regenerate everything for the next iteration
            // This includes new map layouts if the player transitioned to a different area
        }
    }
}

// ======== RANDOM ENCOUNTER BATTLE SYSTEM ========
// Function to handle wild enemy encounters that occur during exploration
// This provides the main combat experience and progression mechanism for the game
// Parameters: player - reference to player character, gameMap - map for display, enemies - array of available enemy types
// Returns: bool - true if player survived the encounter, false if player died
bool RandomEncounter(Player &player, Map &gameMap, Enemy enemies[])
{
    // ======== ZONE-BASED ENEMY SELECTION ========
    // Different map areas have different enemy types for progression and variety
    int minEnemyIndex = 0; // Minimum enemy index for current zone
    int maxEnemyIndex = 2; // Maximum enemy index for current zone (inclusive)
    
    // Determine enemy range based on current map area
    switch (currentMap)
    {
    case 0: // Town Center - Basic enemies (Slime, Goblin, Orc)
        minEnemyIndex = 0;
        maxEnemyIndex = 2;
        break;
    case 1: // North District - Intermediate enemies
        minEnemyIndex = 3;
        maxEnemyIndex = 5;
        break;
    case 2: // South District - Advanced enemies
        minEnemyIndex = 6;
        maxEnemyIndex = 8;
        break;
    case 3: // East District - Elite enemies
        minEnemyIndex = 9;
        maxEnemyIndex = 11;
        break;
    default: // Fallback to basic enemies
        minEnemyIndex = 0;
        maxEnemyIndex = 2;
        break;
    }
    
    // ======== ENEMY SELECTION ========
    // Randomly select an enemy from the zone-specific range for variety in encounters
    int enemyRange = maxEnemyIndex - minEnemyIndex + 1;           // Calculate number of enemies in range
    int randomEnemyIndex = minEnemyIndex + (rand() % enemyRange); // Generate random index within zone range
    Enemy wildEnemy = enemies[randomEnemyIndex];                  // Create a copy of the selected enemy for this battle

    // ======== ENCOUNTER ANNOUNCEMENT SYSTEM ========
    // Create and display an informative message panel to announce the encounter
    // This provides context and builds anticipation before the battle begins
    std::string text[MAX_EVENT_LINES];                       // Array to hold the announcement text lines
    text[0] = "*** WILD ENCOUNTER! ***";                     // Dramatic header to grab attention
    text[1] = "A wild " + wildEnemy.getName() + " appears!"; // Identify the specific enemy type
    text[2] = "Zone: " + getCurrentMapName();                // Show which zone the encounter is in
    text[3] = "Prepare for battle!";                         // Build tension and prepare player mentally
    text[4] = "Press any key to continue...";                // Instruction for user interaction

    // ======== MESSAGE PANEL DISPLAY ========
    // Use the map's panel system to display the encounter message properly
    gameMap.setPanelText(5, text); // Set 5 lines of text in the map's message panel
    clearScreen();                 // Clear the console for clean display
    gameMap.display();             // Show the map with the encounter message panel
    _getch();                      // Wait for player acknowledgment before proceeding to combat

    // ======== COMBAT EXECUTION ========
    // Initiate the actual battle between player and enemy
    // The Combat function handles all battle mechanics, turn-based fighting, and outcome determination
    bool playerSurvived = Combat(player, wildEnemy, gameMap);

    // ======== RETURN BATTLE RESULT ========
    // Return the outcome so calling functions know whether to continue gameplay or handle death
    return playerSurvived; // true = player won and can continue, false = player died
}

#endif // MAP_H