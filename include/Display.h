#ifndef DISPLAY_H
#define DISPLAY_H
#include "Controller.h"
#include <windows.h>
#include <iostream>
void DISPLAY(Display *dis, Grid *grid, Controller *con);
void go(float x, float y);
void out();
void clear();
void judge(int x, int y, Grid *grid);
class Display
{
public:
    Display();

    ~Display();

    void DrawMap(Grid *grid, Controller *controller);

    int DrawAttributes(Controller *controller, Grid *grid);

    void DrawWorkersChange(Controller *controller, int workersNum = 0);

    void DrawProduction(Controller *controller);

    void MainProcess(Controller *controller, Grid *grid, Building **buildings, Activity **activities);
    void turn_red()
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    }
    void turn_blue()
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    }
    void turn_green()
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    }
    void turn_white()
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
    }

protected:
private:
};

#endif // DISPLAY_H
