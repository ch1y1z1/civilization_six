#ifndef BUILDING_H
#define BUILDING_H
#include "Attributes.h"
#include "Activity.h"

enum Landform
{
    OCEAN = 0,
    SEA,
    PLAIN,
    HILLY,
    DESERT,
    MOUNTAIN,
    NOTYPE
};
// this constant two-dimension array represents landform buffs on food and productivity respectively
<<<<<<< HEAD
 static int landformBuffs[7][2] = {{1, 0}, {1, 1}, {2, 1}, {2, 2}, {0, 1}, {0, 0}, {0, 0}};
=======

>>>>>>> 03cda9f35277b07d4c3f15577bcd88ed4021f455

class Building: public Production
{
public:
    Building();
    Building(char* name, float prodSpent, Attributes basicBonus, Attributes popBonus, Attributes locationBonus, char* locationBonusTargetBuildings, Landform locationBonusTargetLandform, Activity* activity = 0);
    ~Building();

    // this array represents the basic bonus on 4 aspects: tech, cul, food, prod
    Attributes basicBonus;

    // this array represents the bonus related to population on those 4 aspects
    Attributes popBonus;

    // this array represents the bonus of adjacent location on those 4 aspects
    Attributes locationBonus;
    char* locationBonusTargetBuildings;
    Landform locationBonusTargetLandform;

    Activity* activity;
};

#endif // BUILDING_H
