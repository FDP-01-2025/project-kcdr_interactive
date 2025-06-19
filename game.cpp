// ========== Headers ==========
#include "src/Player.h"     // To use player functions
#include "src/Enemy.h"      // To use enemy functions
#include "src/Combat.h"     // To use combat functions
#include "src/TownMap.h"    // To use map functions
#include "src/Boss.h"       // To use Boss functions
#include "src/BossCreation.h"
#include "src/EventsAleatory.h" // To use random event functions


// ========== Libraries ==========
#include <iostream>
#include <cctype>  // To handle characters (e.g., toLower)
#include <cstdlib> // To refresh console
#include <conio.h> // To get character input without pressing Enter
using namespace std;

// ========== Player ==========

// Constructor
Player::Player(int health, int attack, int defense, int specialAttack)
    : name("Player1"), health(health), attack(attack), defense(defense), specialAttack(specialAttack) {}

void Player::showStats() const
{
    cout << "Player: " << name
         << " | Health: " << health
         << " | Attack: " << attack
         << " | Defense: " << defense
         << " | Special: " << specialAttack << endl;
}

void Player::receiveDamage(int damage)
{
    int realDamage = damage - defense;
    if (realDamage < 0)
        realDamage = 0;

    if (realDamage == 0)
        cout << "The player's defense was enough. No damage taken." << endl;

    health -= realDamage;
    if (health < 0)
        health = 0;
}

int Player::getHealth() const { return health; }
int Player::getAttack() const { return attack; }
int Player::getDefense() const { return defense; }
int Player::getSpecialAttack() const { return specialAttack; }

// ========== Enemy ==========
Enemy::Enemy(int health, int attack, int defense)
    : name("Enemy"), health(health), attack(attack), defense(defense) {}

void Enemy::showStats() const
{
    cout << "Enemy: " << name
         << " | Health: " << health
         << " | Attack: " << attack
         << " | Defense: " << defense << endl;
}

void Enemy::receiveDamage(int damage)
{
    int realDamage = damage - defense;
    if (realDamage < 0)
        realDamage = 0;
    health -= realDamage;

    if (realDamage == 0)
        cout << "The enemy's defense was enough. No damage taken." << endl;

    if (health < 0)
        health = 0;
}

int Enemy::getHealth() const { return health; }
int Enemy::getAttack() const { return attack; }
string Enemy::getName() const { return name; }

// ========== Boss ==========

// Constructor
Boss::Boss(const string &name, int health, int attack, int defense, int specialAtack)
    : name(name), health(health), attack(attack), defense(defense), specialAtack(specialAtack) {}

//========== Boss getter ==========
string Boss::getName() const
{
    return name;
}

int Boss::getHealth() const
{
    return health;
}

int Boss::getAttack() const
{
    return attack;
}

int Boss::getDefense() const
{
    return defense;
}

int Boss::getspecialAtack() const
{
    return specialAtack;
}

// Boss setters
void Boss::setHealth(int newHealth)
{
    health = newHealth;
}
//  Boss action
void Boss::takeDamage(int amount)
{
    health -= amount; // Resta la cantidad de daño (amount) a la vida actual (health)
    if (health < 0)   // Si la vida baja de 0, la pone en 0 (no puede ser negativa)
    {
        health = 0;
    }
}

int Boss::performAttack() const
{
    return attack;
}

int Boss::performSpecialAtack() const
{
    return specialAtack;
}

bool Boss::isDefeated() const
{
    return health <= 0;
}

// ========== Boss creation ==========
Boss createBoss1()
{
    return Boss("Jefe1", 200, 40, 20, 60);
}
Boss createBoss2()
{
    return Boss("Jefe2", 200, 40, 20, 60);
}
Boss createBoss3()
{
    return Boss("Jefe3", 200, 40, 20, 60);
}
Boss createBoss4()
{
    return Boss("Jefe4", 200, 40, 20, 60);
}

// ========== Combat Enemy Common==========

void Combat(Player &player, Enemy &enemy)
{
    cout << "Combat begins!" << endl;
    player.showStats();
    enemy.showStats();

    while (player.getHealth() > 0 && enemy.getHealth() > 0)
    {
        cout << "Choose an action:" << endl;
        cout << "1. Normal attack (" << player.getAttack() << " damage)" << endl;
        cout << "2. Special attack (" << player.getSpecialAttack() << " damage)" << endl;

        int option;
        cin >> option;

        int damage = 0;
        switch (option)
        {
        case 1:
            damage = player.getAttack();
            cout << "Normal attack used." << endl;
            break;
        case 2:
            damage = player.getSpecialAttack();
            cout << "Special attack used." << endl;
            break;
        default:
            damage = player.getAttack();
            cout << "Invalid option. Using normal attack by default." << endl;
            break;
        }

        enemy.receiveDamage(damage);
        cout << "Enemy's health after attack: " << enemy.getHealth() << endl;

        if (enemy.getHealth() <= 0)
        {
            cout << "Enemy defeated!" << endl;
            break;
        }

        cout << "Enemy attacks with: " << enemy.getAttack() << " damage" << endl;
        player.receiveDamage(enemy.getAttack());

        cout << "Player's health after attack: " << player.getHealth() << endl;

        if (player.getHealth() <= 0)
        {
            cout << "You have been defeated..." << endl;
            break;
        }

        player.showStats();
        enemy.showStats();
    }

    cout << "Combat ended." << endl;
}

// ========== Combat Boss==========
void CombatBoss(Player &player, Boss &boss)
{
    cout << "Be careful, you are facing" << boss.getName() << "!" << endl; // Texto para confirmar que ha iniciado un combate con el nombre del jefe

    // Se muestran las stats que tiene el boss
    cout << "Boss: " << boss.getName() << " | Health: " << boss.getHealth() // Nombre del jefe
         << " | Attack: " << boss.getAttack()                               // Ataque del jefe
         << " | Special Attack: " << boss.getspecialAtack() << endl;        // Ataque especial

    while (player.getHealth() > 0 && boss.getHealth() > 0)
    {
        cout << "Choose an action:" << endl;
        cout << "1. Normal attack (" << player.getAttack() << " damage)" << endl;
        cout << "2. Special attack (" << player.getSpecialAttack() << " damage)" << endl;

        int option;
        cin >> option;

        int damage = 0;
        switch (option)
        {
        case 1:
            damage = player.getAttack();
            cout << "Normal attack used." << endl;
            break;
        case 2:
            damage = player.getSpecialAttack();
            cout << "Special attack used." << endl;
            break;
        default:
            damage = player.getAttack();
            cout << "Invalid option. Using normal attack by default." << endl;
            break;
        }
        boss.takeDamage(damage);
        cout << boss.getName() << "'s health after attack: " << boss.getHealth() << endl;

        if (boss.isDefeated())
        {
            cout << "You defeated the boss!" << endl;
            break;
        }

        // Boss's turn (randomly chooses normal or special attack)
        int bossAttackType = rand() % 2;
        int bossDamage = (bossAttackType == 0) ? boss.getAttack() : boss.getspecialAtack();
        if (bossAttackType == 0)
        {
            cout << boss.getName() << "Uses a normal attack!" << endl;
        }else{
            cout << boss.getName() << "Uses a special attack!" << endl;
        }

        player.receiveDamage(bossDamage);
        cout << "Your health afther attack" << player.getHealth() << endl;

        if (player.getHealth() <= 0)
        {
           cout << "You have been defeated by the boss..." << endl;
           break;
        }        
        player.showStats();
        cout << "Boss: " << boss.getName() << "| Health " << boss.getHealth() << endl; 
    }   
    cout << "Boss battle ended." << endl;
}

// ========== Random Events ==========
void ShowProbability()
{
    int enemyCount = rand() % 3;
    switch (enemyCount)
    {
    case 0:
        cout << "[Enemy 1] has appeared, defeat it!" << endl;
        break;
    case 1:
        cout << "[Enemy 2] has appeared, defeat it!" << endl;
        break;
    case 2:
        cout << "[Enemy 3] has appeared, defeat it!" << endl;
        break;
    default:
        cout << "An error occurred while generating the enemy." << endl;
        break;
    }
}

// ========== Town Map ==========
Map::Map() {
    // Generates an empty map
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++)
            map[i][j] = ' ';

    // Generates the vertical limits of the map.
    for (int i = 0; i < ROWS; i++) {
        map[i][0] = '|';
        map[i][COLUMNS - 1] = '|';
    }
    // Generates the horizontal limits of the map.
    for (int j = 0; j < COLUMNS; j++) {
        map[0][j] = '-';
        map[ROWS - 8][j] = '-';
        map[ROWS - 1][j] = '-';
    }

    // House 1
    map[4][2] = '/';
    map[3][3] = '_';
    map[3][4] = '_';
    map[3][5] = '_';
    map[3][6] = '_';
    map[3][7] = '_';
    map[3][8] = '_';
    map[4][9] = '\\';
    map[5][2] = '|';
    map[5][3] = '#';
    map[5][4] = ' ';
    map[5][5] = '_';
    map[5][6] = ' ';
    map[5][7] = ' ';
    map[5][8] = ' ';
    map[5][9] = '|';
    map[6][2] = '|';
    map[6][3] = '_';
    map[6][4] = '|';
    map[6][5] = ' ';
    map[6][6] = '|';
    map[6][7] = '_';
    map[6][8] = '_';
    map[6][9] = '|';

    // House 2
    map[13][15] = '/';
    map[12][16] = '_';
    map[12][17] = '_';
    map[12][18] = '_';
    map[12][19] = '_';
    map[12][20] = '_';
    map[12][21] = '_';
    map[13][22] = '\\';
    map[14][15] = '|';
    map[14][16] = '#';
    map[14][17] = ' ';
    map[14][18] = '_';
    map[14][19] = ' ';
    map[14][20] = ' ';
    map[14][21] = ' ';
    map[14][22] = '|';
    map[15][15] = '|';
    map[15][16] = '_';
    map[15][17] = '|';
    map[15][18] = ' ';
    map[15][19] = '|';
    map[15][20] = '_';
    map[15][21] = '_';
    map[15][22] = '|';

    //player's starting position
    playerX = 9;
    playerY = 9;
    map[playerX][playerY] = 'O';
}

// shows the content of the map
void Map::displayMap() const {
    system("cls");

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
}

void Map::movePlayer(char direction) {
    int newX = playerX;
    int newY = playerY;

    //modifies the player's coordinates
    switch (direction) {
    case 'w': newX--; break;
    case 's': newX++; break;
    case 'a': newY--; break;
    case 'd': newY++; break;
    default: return;
    }

    // completes the player's movement
    if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLUMNS) {
        char dest = map[newX][newY];
        if (dest == ' ' || dest == '.')
        {
            map[playerX][playerY] = ' ';
            playerX = newX;
            playerY = newY;
            map[playerX][playerY] = 'O';
        }
    }
}

void Map::interact()
{
    char adj[4] = {
        map[playerX - 1][playerY],
        map[playerX + 1][playerY],
        map[playerX][playerY - 1],
        map[playerX][playerY + 1]};


    // message handling depending on nearby objects
    for (char c : adj) {
        if (c == '^' || c == '|' || c == '/' || c == '\\') {
            cout << "It's a house, but it's closed for now.\n";
            return;
        }
        else if (c == '(' || c == ')')
        {
            cout << "There's a bush. You can't pass.\n";
            return;
        }
    }

    cout << "Nothing interesting nearby.\n";
}

void Map::play()
{
    char option;

    while (true) {
         // clears the screen and moves the cursor to the start
        displayMap(); //generates the whole map
        cout << "\nMove: W/A/S/D | Interact: E | Quit: Q\n"; //Game controls
        cout << "Option: ";
        option = tolower(getch());


        if (option == 'q') break; //if the player presses this key, the game is closed.
        else if (option == 'e') interact();
        else movePlayer(option);
    }
}
