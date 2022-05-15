//
// Created by Anthony Stem on 5/6/22.
//

#ifndef SPACE_ACE_ABILITY_H
#define SPACE_ACE_ABILITY_H

#include <vector>

using std::vector;

enum currentAbility {
    NONE,
    MEGA_BULLETS,
    AUTO_SHOOTER,
    POINT_MULTIPLIER,
    BULLET_BARRAGE,
    FREEZE
};

class Ability {
private:
    int time;
    int cost;
    currentAbility ability;

public:
    Ability();
    Ability(int time, int cost, currentAbility ability);
    ~Ability();
    // getters
    int getTime();
    int getCost();
    currentAbility getCurrentAbility();
    // setters
    void setTime(int time);
    void setCost(int cost);
    void changeTime(int timeDelta);
    void setCurrentAbility(currentAbility ability);
    static bool contains(vector<Ability>& abilities, currentAbility ability);
};


#endif //SPACE_ACE_ABILITY_H
