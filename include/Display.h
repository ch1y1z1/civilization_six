#ifndef DISPLAY_H
#define DISPLAY_H
#define DEFAULT "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define WHITE "\033[37m"
#include "Controller.h"
#include <windows.h>
#include <iostream>

class Display
{
public:
    Display();

    ~Display();

    void out();

    void clear();

    void go(float x, float y);

    void DrawMap(Grid *grid);

    int DrawAttributes(Controller *controller, Grid *grid);

    void DrawWorkersChange(Controller *controller, int workersNum = 0);

    void DrawProduction(Controller *controller, Building **buildings);

    void MainProcess(Controller *controller, Grid *grid, Building **buildings, Activity **activities);

protected:
private:
};

#endif // DISPLAY_H
