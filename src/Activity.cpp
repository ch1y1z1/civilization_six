#include "Activity.h"

Activity::Activity()
{
    // ctor
    std::cout << "hello"; // my building test here, cmake is ok now, please ignore it
}

Activity::Activity(char *name, float prodSpent, Attributes basicBonus)
{
    this->name = name;
    this->prodSpent = prodSpent;
    this->basicBonus = basicBonus;
}

Activity::~Activity()
{
    // dtor
}
