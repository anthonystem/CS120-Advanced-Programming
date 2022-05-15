//
// Created by Antho on 5/4/2022.
//

#include "Coin.h"
#include "graphics.h"

using std::string;
using std::to_string;

/* ----- Enemy class implementations ----- */

// Constructors
Coin::Coin() : Character() {
    time = 0;
}

Coin::Coin(int health, int velMultiplier, int time) : Character(health, velMultiplier) {
    this->time = time;
}


// Destructor
Coin::~Coin() = default;

int Coin::getValue() {
    return value;
}

int Coin::getTime() {
    return time;
}

void Coin::setValue(int value) {
    this->value = value;
}

vector<double> Coin::getTrajectory(double x, double y) {
    // Returns {0,0} since the coins do not move.
    return {0,0};
}

void Coin::draw() const {
    Circle::draw();
    string valueStr;
    valueStr = "$";
    glColor3f(0, 0, 0);
    glRasterPos2i(getCenterX() - 4, getCenterY() + 4);
    for (char &letter : valueStr) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}
