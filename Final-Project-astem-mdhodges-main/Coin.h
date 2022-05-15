//
// Created by Antho on 5/4/2022.
//

#ifndef SPACE_ACE_COIN_H
#define SPACE_ACE_COIN_H


#include "Character.h"

class Coin : public Character {
private:
    int value;
    int time;
public:
    Coin();
    Coin(int health, int velMultiplier, int time);
    ~Coin();
    // getters
    int getValue();
    int getTime();
    // setters
    void setValue(int value);
    vector<double> getTrajectory(double x, double y) override;
    virtual void draw() const override;

};


#endif //SPACE_ACE_COIN_H
