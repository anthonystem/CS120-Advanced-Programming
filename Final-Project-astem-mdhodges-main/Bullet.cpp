#include "Bullet.h"

/* ----- Bullet class implementations ----- */

// Constructor
Bullet::Bullet() : Character() {
}


// Destructor
Bullet::~Bullet() = default;


// Class functions
vector<double> Bullet::getTrajectory(double x, double y) {
    vector<double> temp;
    double xVec = (x - 400) / sqrt(pow(x - 400, 2) + pow((y - 400), 2));
    double yVec = (y - 400) / sqrt(pow(x - 400, 2) + pow((y - 400), 2));
    temp.push_back(xVec);
    temp.push_back(yVec);
    return temp;
}