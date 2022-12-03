#ifndef DISPLAY_H
#define DISPLAY_H

#include "Controller.h"

class Display
{
    public:
        Display();

        ~Display();

        void DrawMap(Grid* grid);

        int DrawAttributes(Controller* controller);

        void DrawWorkersChange(Controller* controller, int workersNum=0);

        void DrawProduction(Controller* controller, Building** buildings);

        void MainProcess(Controller* controller, Grid* grid, Building** buildings, Activity** activities);

    protected:

    private:
};

#endif // DISPLAY_H
