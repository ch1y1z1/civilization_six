#include "Building.h"

Building::Building()
{
    //ctor
}

Building::Building(char* name, float prodSpent, Attributes basicBonus, Attributes popBonus, Attributes locationBonus, char* locationBonusTargetBuildings, Landform locationBonusTargetLandform, Activity* activity):
    basicBonus(basicBonus), popBonus(popBonus), locationBonus(locationBonus), locationBonusTargetBuildings(locationBonusTargetBuildings), locationBonusTargetLandform(locationBonusTargetLandform), activity(activity)
    {
        this->name = name;
        this->prodSpent = prodSpent;
    }

Building::~Building()
{
    //dtor
}
