#ifndef CONTROLLER_H
#define CONTROLLER_H

#define TOTAL_ROUND (100)

#define PRODUCTION_TYPE_BUILDING (1)
#define PRODUCTION_TYPE_ACTIVITY (2)

#include "Grid.h"

class Controller
{
public:
    Controller();

    virtual ~Controller();

    bool bindGrid(Grid* grid);

    bool nextRound(int& newX, int& newY, float& nextThres);

    int checkPop();

    Activity** availableActivities;
    int activitySize = 0;

    bool SetProductionBuilding(int m, int n, Building* Building);
    bool SetProductionActivity(Activity* activity);
    bool SetProductionActivity(int activityOrder);

    int setPopAt(int m, int n, bool isAdding = true);

    Attributes getAttributes();

    int getPop();
    int getWorkingPop(int& workersNumber, int*& workersCellCoords);

    Production* getProduction(int& productionType, Cell*& currentProductionCell);

    Cell& getCellDescription(int m, int n);

    int getRound();

    void reset(int pop, float firstBorderThreshold = 5.0);

    int checkBorderUpdate(int& newX, int& newY, float& nextThres);

protected:

private:
    Attributes currentAttributes;

    float pop;

    int workingPop;

    float BorderExpandThreshold = 0.2;

    int currentRound;

    Production* currentProduction;
    int currentProductionType = 0;
    Cell* currentProductionCell = 0;

    Grid* world;

    int updateProduction();

    void updatePop();

    void updateAttributes();

    bool checkWin();

    Cell** getAdjacentCells(int m, int n);

    int getAdjacentSatisfied(Cell** adjacents, char buildingName, Landform landformType);

};

#endif // CONTROLLER_H
