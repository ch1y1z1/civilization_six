#include "Activity.h"

Activity::Activity()
{
    //ctor
}

Activity::Activity(char* name, float prodSpent, Attributes basicBonus){
        this->name = name;
        this->prodSpent = prodSpent;
        this->basicBonus = basicBonus;
    }



Activity::~Activity()
{
    //dtor
}
