#include "Enemy.h"
#include "graphics.h"
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::to_string;

/* ----- Enemy class implementations ----- */

// Constructors
Enemy::Enemy() : Character() {
}

Enemy::Enemy(int health, int velMultiplier) : Character(health, velMultiplier) {
}


// Destructor
Enemy::~Enemy() = default;


// Class functions
vector<double> Enemy::getTrajectory(double x, double y) {
    vector<double> temp;
    double xVec = (x - getCenterX()) / sqrt(pow(x - getCenterX(), 2) + pow((y - getCenterY()), 2));
    double yVec = (y - getCenterY()) / sqrt(pow(x - getCenterX(), 2) + pow((y - getCenterY()), 2));
    temp.push_back(xVec);
    temp.push_back(yVec);
    return temp;
}

void Enemy::draw() const {
    Circle::draw();
    string healthStr;
    healthStr = to_string(health);
    glColor3f(1, 1, 1);
    glRasterPos2i(getCenterX() - 4, getCenterY() + 4);
    for (char &letter : healthStr) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}