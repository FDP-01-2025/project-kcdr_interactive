// ========== Headers ==========
#include "src/Player.h"     // To use player functions
#include "src/Enemy.h"      // To use enemy functions
#include "src/Combat.h"     // To use combat functions
#include "src/Boss.h"       // To use Boss functions
#include "src/BossCreation.h"
#include "src/EventsAleatory.h" // To use random event functions
#include "src/map.h"


// ========== Libraries ==========
#include <iostream>
#include <fstream> // To use ofstream and ifstream
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
Enemy::Enemy(const string &name, int health, int attack, int defense, const string &art)
    : name(name), health(health), attack(attack), defense(defense), asciiArt(art) {}

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


void Enemy::showArt() const {
    cout << asciiArt << endl;
}

int Enemy::getHealth() const { return health; }
int Enemy::getAttack() const { return attack; }
string Enemy::getName() const { return name; }

// ========== Enemy Draw==========

Enemy enemy[12] = {
    Enemy("Slime", 20, 5, 2, R"(
   __
  ( oo )
  /|__|\
)"),
    Enemy("Goblin", 25, 7, 3, R"(
  ,      ,
 /(.-""-.)\
 |\  \/  /|
 (_/    \_)
  /      \
  \      /
   `----`
)"), //si
    Enemy("Orc", 35, 10, 5, ""), //si
    Enemy("Bandit", 28, 8, 2, ""), //si
    Enemy("Wolf", 22, 6, 1, ""), //no
    Enemy("Skeleton", 18, 9, 2, ""), //si
    Enemy("Bat", 15, 4, 1, ""), //no
    Enemy("Spider", 17, 5, 2, ""), // no
    Enemy("Zombie", 30, 6, 4, ""), // no
    Enemy("Witch", 24, 11, 3, ""), //si
    Enemy("Knight", 40, 12, 8, ""), //si
    Enemy("Dragonling", 45, 15, 6, "")}; //si




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
    std:: cout << "Combat begins!" << endl;
    player.showStats();
    enemy.showStats();
    enemy.showArt(); // Muestra el arte ASCII del enemigo

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
Map::Map()
{
    drawBorders();
}



