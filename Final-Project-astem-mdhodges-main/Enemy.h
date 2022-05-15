/**
 * A class that represents an Enemy object.
 * Extends the Character class.
 */
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
private:

public:
    Enemy();
    Enemy(int health, int velMultiplier);
    ~Enemy();

    vector<double> getTrajectory(double x, double y) override;
    virtual void draw() const override;
};

#endif //ENEMY_H
