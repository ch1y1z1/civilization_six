#ifndef CONTROLLER_H
#define CONTROLLER_H

#define TOTAL_ROUND (100)

#define PRODUCTION_TYPE_BUILDING (1)
#define PRODUCTION_TYPE_ACTIVITY (2)

#include "Grid.h"

class Controller
{
    friend class Display;

public:
    Controller();

    virtual ~Controller();

    int get_round_needed_to_active();

    int get_totle_round_needed();

    bool bindGrid(Grid* grid);

    bool nextRound(int& newX, int& newY, float& nextThres);

    int checkPop();

    Activity** availableActivities;
    Activity** new_availableActivities;
    int activitySize = 3;
    Building** availableBuildings;
    // int buildingSize = 0;

    bool SetProductionBuilding(int m, int n, Building* Building);
    bool SetProductionActivity(Activity* activity);
    bool SetProductionActivity(int activityOrder);

    int setPopAt();

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

    float BorderExpandThreshold = 0.8;

    int currentRound = 1;

    Production* currentProduction = 0;

    int currentProductionType = 0;

    Cell* currentProductionCell = 0;
    Cell** adjacent = new Cell * [4];

    Grid* world;

    int updateProduction();

    void updatePop();

    void updateAttributes();

    bool checkWin();

    Cell** getAdjacentCells(int m, int n);

    int getAdjacentSatisfied(Cell** adjacents, char buildingName, Landform landformType);

    float prod_needed_to_active;

    int round_needed_to_active = -1;

    int totle_round_needed = -1;

    int buffround = -1;
};

#endif // CONTROLLER_H
