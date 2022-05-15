/**
 * An abstract class that represents a Character or element of the game which has health and interacts with the game.
 * Extends the Circle class.
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include "circle.h"
#include <vector>
using std::vector;

class Character : public Circle {
protected:
    int health;
    double xVec;
    double yVec;
    int velMultiplier;

public:
    Character();
    Character(int health, int velMultiplier);
    ~Character();
    int getHealth() const;
    int getVelMultiplier() const;
    double getXVec() const;
    double getYVec() const;
    void setHealth(int health);
    void setVelMultiplier(int velMultiplier);
    void setXVec(double xVec);
    void setYVec(double yVec);
    void decreaseHealth(int damage);

    /**
     * Checks if the Character object's health is <= 0
     *
     * @returns true if the health is less than or equal to 0; false if the health is >= 0.
     * */
    bool isDead();

    // Pure virtual function to calculate trajectory given x and y.
    virtual vector<double> getTrajectory(double x, double y) = 0;
};
#endif //CHARACTER_H
