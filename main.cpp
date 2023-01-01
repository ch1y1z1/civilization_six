#include <iostream>
#include "Display.h"
#include <cstring>
using namespace std;
int main()
{
    Controller* controller = new Controller();

    Activity* symposium = new Activity((char*)"symposium", 50, Attributes(30.0));
    Activity* exhibition = new Activity((char*)"exhibition", 50, Attributes(0, 30.0));
    Activity* distribution = new Activity((char*)"distribution", 50, Attributes(0, 0, 0, 30.0));

    Activity** activities = new Activity * [3]
    { symposium, exhibition, distribution };

    Building* center = new Building((char*)"cen", 0.0, Attributes(0.0), Attributes(0.7, 0.3, 0.5, 0.5 / 2), Attributes(1.0), (char*)"a", NOTYPE, symposium, 0);
    Building* campus = new Building((char*)"cam", 100.0, Attributes(1.0), Attributes(0.2), Attributes(1.0), (char*)"a", MOUNTAIN, symposium, 1);
    Building* theatre = new Building((char*)"the", 100.0, Attributes(0, 1.0), Attributes(0, 0.2), Attributes(1.0), (char*)"aw", NOTYPE, exhibition, 2);
    Building* wonder = new Building((char*)"won", 250.0, Attributes(0, 20.0 / 4), Attributes(0), Attributes(5.0), (char*)"w", NOTYPE, 0, 3);
    Building* industrialPark = new Building((char*)"ind", 100.0, Attributes(0, 0, 0, 2.0 / 4), Attributes(0, 0, 0, 2.0 / 4), Attributes(1.0), (char*)"a", NOTYPE, distribution, 4);

    Building** buildings = new Building * [5]
    { center, campus, theatre, wonder, industrialPark };

    Grid* grid = new Grid("./resource/map.txt");

    Display d;
    d.MainProcess(controller, grid, buildings, activities);
    return 0;
}
/**
 * @brief move your cursor to (x,y) and hide it
 *
 * @param x
 * @param y
 */
void go(float x, float y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a, coord);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(a, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(a, &CursorInfo);


}
/**
 * @brief guide your input
 *
 */
void out()
{
    clear();
    go(0, 23);
    cout << "--------------------------------------------\n";
    cout << "              INTERACT HERE\n";
    go(0, 0);
    go(0, 25);
}
/**
 * @brief clear your input
 *
 */
void clear()
{
    go(0, 25);
    for (int j = 0; j < 30; j++)
    {
        for (int i = 0; i < 65; i++)
        {
            cout << " ";
        }
        cout << endl;
    }
}

