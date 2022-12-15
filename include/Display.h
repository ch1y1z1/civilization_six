#ifndef DISPLAY_H
#define DISPLAY_H
#define DEFAULT "\033[0m"
#define Blue "\033[0;34m"
#define Green "\033[0;32m"
#define Red "\033[0;31m"
#define Yellow "\033[0;33m"
#define White "\033[0;37m"
#include "Controller.h"
#include <windows.h>
#include <iostream>
class Display
{
    public:
        Display();

        ~Display();

        void go(float x, float y);

        void DrawMap(Grid *grid);

        int DrawAttributes(Controller* controller);

        void DrawWorkersChange(Controller* controller, int workersNum=0);

        void DrawProduction(Controller* controller, Building** buildings);

        void MainProcess(Controller* controller, Grid* grid, Building** buildings, Activity** activities);

    protected:

    private:
};

#endif // DISPLAY_H
