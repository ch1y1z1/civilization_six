#include <iostream>
#include "Display.h"
#include <cstring>
#include <vector>
using namespace std;

int main()
{
    Controller* controller = new Controller();

    Activity* symposium = new Activity((char*)"symposium", 50, Attributes(30.0));
    Activity* exhibition = new Activity((char*)"exhibition", 50, Attributes(0, 30.0));
    Activity* distribution = new Activity((char*)"distribution", 50, Attributes(0, 0, 0, 30.0));

    Activity** activities = new Activity * [3] {symposium, exhibition, distribution};

    Building* center = new Building((char*)"cen", 0.0, Attributes(0.0), Attributes(0.7, 0.3, 0.5, 0.5), Attributes(1.0), (char*)"a", NOTYPE, symposium);
    Building* campus = new Building((char*)"cam", 100.0, Attributes(1.0), Attributes(0.2), Attributes(1.0), (char*)"a", MOUNTAIN, symposium);
    Building* theatre = new Building((char*)"the", 100.0, Attributes(0, 1.0), Attributes(0, 0.2), Attributes(1.0), (char*)"aw", NOTYPE, exhibition);
    Building* wonder = new Building((char*)"won", 250.0, Attributes(0, 20.0), Attributes(0), Attributes(5.0), (char*)"w", NOTYPE);
    Building* industrialPark = new Building((char*)"ind", 100.0, Attributes(0, 0, 0, 2.0), Attributes(0, 0, 0, 2.0), Attributes(1.0), (char*)"a", NOTYPE, distribution);

    Building** buildings = new Building * [5] {center, campus, theatre, wonder, industrialPark};

    Grid* grid = new Grid("./resource/map.txt");

    Display d;
    d.MainProcess(controller, grid, buildings, activities);

    return 0;

}
