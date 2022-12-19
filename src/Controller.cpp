#include "Controller.h"
#include "cstring"

Controller::Controller()
{
    this->currentRound = 0;
    this->world = 0;
    this->pop = 2;
    this->workingPop = 0;
    this->currentAttributes = Attributes(0);
}

Controller::~Controller()
{
    //dtor
}

void Controller::reset(int pop, float firstBorderThreshold) {
    this->currentRound = 0;
    this->world = 0;
    this->pop = pop;
    this->workingPop = 0;
    this->currentAttributes = Attributes(0);
}

bool Controller::checkWin() {
    // todo: check whether the player has won the game
    if (this->currentAttributes.tech >= 500) return true;
    if (this->currentAttributes.cul >= 350) return true;  // TODO: add 5 qiguan
    int score = 0.5 * this->currentAttributes.tech + 0.5 * this->currentAttributes.cul + 10 * this->pop + this->currentAttributes.prod;
    if (score >= 500) return true;
    return false;
}

bool Controller::bindGrid(Grid* grid) {
    this->world = grid;
    return (grid != 0);
}

Attributes Controller::getAttributes() {
    return this->currentAttributes;
}

int Controller::getPop() {
    return this->pop;
}

int Controller::getWorkingPop(int& workersNumber, int*& workersCellCoords) {
    workersNumber = this->workingPop;
    if (workersCellCoords != 0) delete[] workersCellCoords;
    if (workersNumber == 0) {
        workersCellCoords = 0;
        return 0;
    }
    workersCellCoords = new int[2 * workersNumber] {0};
    Cell** grid = this->world->getGrid();
    int m = this->world->getGridHeight(), n = this->world->getGridWidth();
    int cur = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j].Pop == COLONIZED) {
                workersCellCoords[cur] = i;
                workersCellCoords[cur + 1] = j;
                cur += 2;
            }
        }
    }
    if (cur != workersNumber * 2) return -1;
    return 0;
}

Cell& Controller::getCellDescription(int m, int n) {
    return world->getRepresent(m, n);
}

int Controller::getRound() {
    return currentRound;
}

bool Controller::SetProductionBuilding(int m, int n, Building* building) {
    // todo: set the current production to building at coordinates (m, n), return true if the action is successful
    if (this->getCellDescription(m, n).buildingType == 0)
        return false;
    this->getCellDescription(m, n).buildingType = building;
}

bool Controller::SetProductionActivity(Activity* activity) {
    // todo: set the current production to activity, return true if the action is successful
}

bool Controller::SetProductionActivity(int activityOrder) {
    if (activityOrder >= activitySize || activityOrder < 0)
        return false;
    currentProductionType = PRODUCTION_TYPE_ACTIVITY;
    currentProductionCell = 0;
    currentProduction = availableActivities[activityOrder];
    return true;
}

bool Controller::nextRound(int& newX, int& newY, float& nextThres) {  // ! main here
    if (this->checkWin())
        return 1;

    this->currentRound++;
    this->checkBorderUpdate(newX, newY, nextThres);
    this->updatePop();
    this->updateProduction();
    this->updateAttributes();




    return 0;
}

int Controller::updateProduction() {
    // todo: update the process of current prodution
}

Production* Controller::getProduction(int& productionType, Cell*& currentProductionCell) {
    productionType = this->currentProductionType;
    currentProductionCell = this->currentProductionCell;
    return this->currentProduction;
}


int Controller::checkPop() {
    if (int(this->workingPop) > this->pop)
        return -1;  //you have to remove pops
    else if (int(this->workingPop) < this->pop)
        return 1;   //you may add pops to work
    else return 0;  //you may switch pops
}

void Controller::updatePop() {
    int maxpop = this->currentAttributes.food / 2;
    float popDelta = (maxpop - pop) * 0.1;
    if (popDelta > 1)
        popDelta = 1;
    else if (popDelta < -1)
        popDelta = -1;
    this->pop += popDelta;
}

int Controller::checkBorderUpdate(int& newX, int& newY, float& nextThres) {
    // todo: check whether the border should update or not, and if so, return the new culture threshold and expansion coordinates (newX, newY)
    nextThres = this->BorderExpandThreshold;
    if (this->currentAttributes.cul >= this->BorderExpandThreshold)
    {
        this->BorderExpandThreshold *= 2;
        std::cout << "Border is now Expandable" << std::endl;
        std::cout << "Please input the coordinates of the new border" << std::endl;
        std::cin >> newX >> newY;
        return 1;
    }
    newX = -1;
    return 0;
}

int Controller::setPopAt(int m, int n, bool isAdding) {
    // todo: add or remove the worker at (m, n), return 0 if the action is successful


}

void Controller::updateAttributes() {
    // todo: calculate and update the attributes according to the buffs
}

Cell** Controller::getAdjacentCells(int m, int n) {
    // todo: get the adjacent cells from cell (m, n)
}

int Controller::getAdjacentSatisfied(Cell** adjacents, char buildingName, Landform landformType) {
    // todo: check whether the adjacent cells satisfy the landformType and buildingName(s), you need to rewrite it if you use a hexagonal map
    unsigned satisfiedCellsNum = 0;
    for (int t = 0; t < 4; t++) {
        if (adjacents[t] != 0) {
            satisfiedCellsNum += ((adjacents[t]->buildingType && (buildingName == 'a' || adjacents[t]->buildingType->name[0] == buildingName))
                && adjacents[t]->landform == landformType);
        }
    }
    return satisfiedCellsNum;
}

