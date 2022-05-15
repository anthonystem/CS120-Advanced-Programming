#include "Character.h"

/* ----- Character class implementations ----- */

// Constructors
Character::Character() {
    health = 1;
    velMultiplier = 1;
    xVec = 0;
    yVec = 0;
}

Character::Character(int health, int velMultiplier) {
    this->health = health;
    this->velMultiplier = velMultiplier;
}


// Destructor
Character::~Character() = default;


// Getters
int Character::getHealth() const {
    return health;
}

int Character::getVelMultiplier() const {
    return velMultiplier;
}

double Character::getXVec() const {
    return xVec;
}

double Character::getYVec() const {
    return yVec;
}


// Setters
void Character::setHealth(int health) {
    this->health = health;
}

void Character::setVelMultiplier(int velMultiplier) {
    this->velMultiplier = velMultiplier;
}

void Character::setXVec(double xVec) {
    this->xVec = xVec;
}

void Character::setYVec(double yVec) {
    this->yVec = yVec;
}


// Class functions
void Character::decreaseHealth(int damage) {
    health -= damage;
}

bool Character::isDead() {
    bool isDead = false;
    if (health <= 0) {
        isDead = true;
    }
    return isDead;
}