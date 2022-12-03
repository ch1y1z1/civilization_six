#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "Attributes.h"
#include <iostream>

class Production
{
public:
    char *name = 0;
    float prodSpent = 0.0;

    Production() {}
    Production(char *name, float prodSpent) : name(name), prodSpent(prodSpent) {}
    ~Production() {}
};

class Activity : public Production
{
public:
    Activity();
    Activity(char *name, float prodSpent, Attributes basicBonus);
    ~Activity();

    float prodAccumulated = 0.0;
    int effectedRounds = 5;
    int remainingEffectedRounds = 0;

    // this array represents the basic bonus on 4 aspects: tech, cul, food, prod
    Attributes basicBonus;
};

#endif // ACTIVITY_H
