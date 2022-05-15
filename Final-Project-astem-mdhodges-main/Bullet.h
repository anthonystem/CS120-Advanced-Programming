/**
 * A class that represents a Bullet object which is a Character object.
 * Extends the Character class.
 */
#ifndef BULLET_H
#define BULLET_H

#include "Character.h"

class Bullet : public Character {
private:
    // Currently, no class fields. Left for scalability.
public:
    Bullet();
    ~Bullet();

    /**
     * Sets Bullet trajectory towards the specified point.
     *
     * @param x - x location of target.
     * @param y - y location of target.
     * @returns a vector of doubles; index 0 = x component, index 1 = y component.
     */
    vector<double> getTrajectory(double x, double y) override;
};
#endif //BULLET_H
