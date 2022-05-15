//
// Created by Anthony Stem on 5/6/22.
//

#include "Ability.h"
#include <iostream>
using namespace std;

Ability::Ability() {
    time = 0;
    cost = 0;
    ability = NONE;
}

Ability::Ability(int time, int cost, currentAbility ability) {
    this->time = time;
    this->cost = cost;
    this->ability = ability;
}

Ability::~Ability() = default;

int Ability::getTime() {
    return time;
}

int Ability::getCost() {
    return cost;
}

currentAbility Ability::getCurrentAbility() {
    return ability;
}

void Ability::setTime(int time) {
    this->time = time;
}

void Ability::setCost(int cost) {
    this->cost = cost;
}

void Ability::changeTime(int timeDelta) {
    time += timeDelta;
}

void Ability::setCurrentAbility(currentAbility ability) {
    this->ability = ability;
}

bool Ability::contains(vector<Ability>& abilities, currentAbility ability) {
    for (int i = 0; i < abilities.size(); ++i) {
        if (abilities[i].getCurrentAbility() == ability) {
            return true;
        }
    }
    return false;
}
