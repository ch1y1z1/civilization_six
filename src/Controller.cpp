#include "Controller.h"
#include "cstring"
#include "Display.h"

const int landformBuffs[7][2] = {
    {1, 0}, {1, 1}, {2, 1}, {2, 2}, {0, 1}, {0, 0}, {0, 0} };

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
    // dtor
}

void Controller::reset(int pop, float firstBorderThreshold)
{
    this->currentRound = 0;
    this->world = 0;
    this->pop = pop;
    this->workingPop = 0;
    this->currentAttributes = Attributes(0);
}

bool Controller::checkWin()
{
    // todo: check whether the player has won the game
    if (this->currentAttributes.tech >= 500)
        return true;
    if (this->currentAttributes.cul >= 350)
        return true; // TODO: add 5 wonder
    int score = 0.5 * this->currentAttributes.tech + 0.5 * this->currentAttributes.cul + 10 * this->pop + this->currentAttributes.prod;
    if (score >= 500)
        return true;
    return false;
}

bool Controller::bindGrid(Grid* grid)
{
    this->world = grid;
    return (grid != 0);
}

Attributes Controller::getAttributes()
{
    return this->currentAttributes;
}
int Controller::getPop()
{
    return this->pop;
}

int Controller::getWorkingPop(int& workersNumber, int*& workersCellCoords)
{
    workersNumber = this->workingPop;
    if (workersCellCoords != 0)
        delete[] workersCellCoords;
    if (workersNumber == 0)
    {
        workersCellCoords = 0;
        return 0;
    }
    workersCellCoords = new int[2 * workersNumber] {0};
    Cell** grid = this->world->getGrid();
    int m = this->world->getGridHeight(), n = this->world->getGridWidth();
    int cur = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j].Pop == COLONIZED)
            {
                workersCellCoords[cur] = i;
                workersCellCoords[cur + 1] = j;
                cur += 2;
            }
        }
    }
    if (cur != workersNumber * 2)
        return -1;
    return 0;
}

Cell& Controller::getCellDescription(int m, int n)
{
    return world->getRepresent(m, n);
}

int Controller::getRound()
{
    return currentRound;
}

bool Controller::SetProductionBuilding(int m, int n, Building* building)
{
    // todo: set the current production to building at coordinates (m, n), return true if the action is successful
    if (this->getCellDescription(m, n).buildingType != 0)
        return false;
    if (m > this->world->getGridHeight() || n > this->world->getGridWidth() || m < 0 || n < 0)
        return false;
    // if (this->getAdjacentSatisfied(this->getAdjacentCells(m, n), m, n) == 0)
    //     return false;
    // TODO: check if the building is beside another building
    this->getCellDescription(m, n).buildingType = building;
    return true;
}

bool Controller::SetProductionActivity(Activity* activity)
{
    // todo: set the current production to activity, return true if the action is successful
    this->currentProductionType = PRODUCTION_TYPE_ACTIVITY;
    this->currentProductionCell = 0;
    this->currentProduction = activity;
    return true;
}

bool Controller::SetProductionActivity(int activityOrder)
{
    if (activityOrder >= activitySize || activityOrder < 0)
        return false;
    currentProductionType = PRODUCTION_TYPE_ACTIVITY;
    currentProductionCell = 0;
    currentProduction = availableActivities[activityOrder];
    return true;
}

bool Controller::nextRound(int& newX, int& newY, float& nextThres)
{ // ! main here
    if (this->checkWin())
        return 1;

    this->currentRound++;
    this->checkBorderUpdate(newX, newY, nextThres);
    this->setPopAt();
    this->updateProduction();
    this->updateAttributes();

    return 0;
}

int Controller::updateProduction()
{
    // todo: update the process of current prodution
    // std::cout << "Please select one production" << std::endl;
    // char Buildingnames[20][20] = { "center", "campus", "theatre", "wonder", "industrialpark" };
    if (this->currentProduction == 0)
    {
        clear();
        out();
        std::cout << "Please select one production" << std::endl;
        std::cout << "1. Building" << std::endl;
        std::cout << "2. Activity" << std::endl;
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            int buildingchoice;
            while (1)
            {
                std::cout << "please input the coordinates" << std::endl;
                int m1, n1;
                std::cin >> m1 >> n1;
                int m = m1 / 2 - 1;
                int n = n1 - 1;
                if (m > this->world->getGridHeight() || n > this->world->getGridWidth() || m < 0 || n < 0)
                {
                    std::cout << "invalid input: out of range" << std::endl;
                    continue;
                }
                if (this->getCellDescription(m, n).buildingType != 0)
                {
                    std::cout << "invalid input: there has been a building yet" << std::endl;
                    continue;
                }
                std::cout << "please select one building" << std::endl;
                for (int i = 0; i < 5; i++)
                {
                    // std::cout << i << ". " << Buildingnames[i] << std::endl;
                    std::cout << i << ". " << this->availableBuildings[i]->name << std::endl;
                }
                std::cin >> buildingchoice;
                if (buildingchoice < 0 || buildingchoice > 4)
                {
                    std::cout << "invalid input: out of range" << std::endl;
                    continue;
                }
                // this->currentProductionType = PRODUCTION_TYPE_BUILDING;
                this->currentProductionCell = &this->getCellDescription(m, n);
                this->currentProduction = this->availableBuildings[buildingchoice];
                this->prod_needed_to_active = this->availableBuildings[buildingchoice]->prodSpent * this->getRound() / 100;
                this->getCellDescription(m, n).buildingType = this->availableBuildings[buildingchoice];

                break;
            }
            // this->currentProductionType = PRODUCTION_TYPE_BUILDING;
            // this->currentProductionCell = 0;
            // this->currentProduction = ;
            break;
        case 2:
            break;
        }
        clear();
    }
    // this->DrawMap(grid);
    system("pause");
    return 1;
}

Production* Controller::getProduction(int& productionType, Cell*& currentProductionCell)
{
    productionType = this->currentProductionType;
    currentProductionCell = this->currentProductionCell;
    return this->currentProduction;
}

int Controller::checkPop()
{
    if (int(this->workingPop) > this->pop)
        return -1; // you have to remove pops
    else if (int(this->workingPop) < this->pop)
        return 1; // you may add pops to work
    else
        return 0; // you may switch pops
}

void Controller::updatePop()
{
    int maxpop = this->currentAttributes.food / 2;
    float popDelta = (maxpop - pop) * 0.1;
    if (popDelta > 1)
        popDelta = 1;
    else if (popDelta < -1)
        popDelta = -1;
    this->pop += popDelta;
}

int Controller::checkBorderUpdate(int& newX, int& newY, float& nextThres)
{
    // todo: check whether the border should update or not, and if so, return the new culture threshold and expansion coordinates (newX, newY)
    nextThres = this->BorderExpandThreshold;
    if (this->currentAttributes.cul >= this->BorderExpandThreshold)
    {
        this->BorderExpandThreshold *= 2;
        out();
        std::cout << "Border is now Expandable" << std::endl;
        std::cout << "Please input the coordinates of the new border" << std::endl;
        std::cin >> newX >> newY;
        this->getCellDescription(newX, newY).Pop = OWNED;
        clear();
        return 1;
    }
    return 0;
}

int Controller::setPopAt()
{
    // todo: add or remove the worker at (m, n), return 0 if the action is successful
    bool flag = this->checkPop();
    while (flag != 0)
    {
        switch (flag)
        {
        case -1:
            out();
            std::cout << "You have to remove pops" << std::endl;
            while (true)
            {
                std::cout << "Please input the coordinates of the pop you want to remove" << std::endl;
                int x, y;
                std::cin >> x >> y;
                if (this->getCellDescription(x / 2 - 1, y - 1).Pop == COLONIZED)
                {
                    this->getCellDescription(x / 2 - 1, y - 1).Pop = OWNED;
                    this->workingPop--;
                    break;
                }
                else
                {
                    std::cout << "There is no pop at this cell" << std::endl;
                }
            }
            clear();
            break;
        case 1:
            out();
            std::cout << "you may add pop to work" << std::endl;
            while (true)
            {
                std::cout << "Please input the coordinates of the pop you want to add" << std::endl;
                int x, y;
                std::cin >> x >> y;
                if (this->getCellDescription(x / 2 - 1, y - 1).Pop == OWNED)
                {
                    this->getCellDescription(x / 2 - 1, y - 1).Pop = COLONIZED;
                    this->workingPop++;
                    break;
                }
                else if (this->getCellDescription(x / 2 - 1, y - 1).Pop == COLONIZED)
                {
                    std::cout << "There has already been a pop at this cell" << std::endl;
                }
                else if (this->getCellDescription(x / 2 - 1, y - 1).Pop == WILD)
                {
                    std::cout << "The cell haven't been owned now" << std::endl;
                }
            }
            clear();
            break;
        }
        flag = this->checkPop();
        // display->DrawMap(grid);
    }

    while (true)
    {
        out();
        std::cout << "you may switch pops now" << std::endl;
        std::cout << "Please input the coordinates of the pop you want to switch \nor you may input '0' to skip this step" << std::endl;
        int x, y, newx, newy;
        std::cin >> x;
        if (x == 0)
            return 0;
        std::cin >> y >> newx >> newy;
        if (!(this->getCellDescription(x / 2 - 1, y - 1).Pop == OWNED))
        {
            std::cout << "There is no pop at this cell" << std::endl;
            continue;
        }
        if (this->getCellDescription(newx / 2 - 1, newy - 1).Pop == COLONIZED)
        {
            std::cout << "There has already been a pop at this cell" << std::endl;
            continue;
        }
        if (this->getCellDescription(newx / 2 - 1, newy - 1).Pop == WILD)
        {
            std::cout << "The cell havn't been owned now" << std::endl;
            continue;
        }
        this->getCellDescription(x / 2 - 1, y - 1).Pop = OWNED;
        this->getCellDescription(newx / 2 - 1, newy - 1).Pop = COLONIZED;
        std::cout << "Switch successfully" << std::endl;
        clear();
        // this->DrawMap(grid);
    }

    clear();
}

void Controller::updateAttributes()
{
    // todo: calculate and update the attributes according to the buffs
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (this->getCellDescription(i, j).Pop == OWNED && this->getCellDescription(i, j).buildingType == 0)
            {
                this->currentAttributes.food += landformBuffs[this->getCellDescription(i, j).landform][0];
                this->currentAttributes.prod += landformBuffs[this->getCellDescription(i, j).landform][1];
            }
            if (this->getCellDescription(i, j).buildingType != 0)
            {
                this->currentAttributes += this->getCellDescription(i, j).buildingType->basicBonus;
            }
        }
    }
}

Cell** Controller::getAdjacentCells(int m, int n)
{
    // todo: get the adjacent cells from cell (m, n)
    // you can use this as :Cell** adjacent=getAdjacentCells(m,n) to get the details of (m,n)'s up, left ,down and right
    // Cell adj=new Cell[1];
    Cell** adjacent = new Cell * [4];
    if (m == 0 && n == 0)
    {
        adjacent[0] = 0;
        adjacent[1] = 0;
        adjacent[2] = new Cell;
        adjacent[3] = new Cell;
        *adjacent[2] = getCellDescription(m + 1, n);
        *adjacent[3] = getCellDescription(m, n + 1);
    }
    else if (m == 19 && n == 19)
    {
        adjacent[0] = new Cell;
        adjacent[1] = new Cell;
        adjacent[2] = 0;
        adjacent[3] = 0;
        *adjacent[0] = getCellDescription(m - 1, n);
        *adjacent[1] = getCellDescription(m, n - 1);
    }
    else if (m == 0 && n == 19)
    {
        adjacent[0] = 0;
        adjacent[1] = new Cell;
        adjacent[2] = new Cell;
        adjacent[3] = 0;
        *adjacent[1] = getCellDescription(m, n - 1);
        *adjacent[2] = getCellDescription(m + 1, n);
    }
    else if (m == 19 && n == 0)
    {
        adjacent[0] = new Cell;
        adjacent[1] = 0;
        adjacent[2] = 0;
        adjacent[3] = new Cell;
        *adjacent[0] = getCellDescription(m - 1, n);
        *adjacent[3] = getCellDescription(m, n + 1);
    }
    else if (m == 0)
    {
        adjacent[0] = 0;
        adjacent[1] = new Cell;
        adjacent[2] = new Cell;
        adjacent[3] = new Cell;
        *adjacent[1] = getCellDescription(m, n - 1);
        *adjacent[2] = getCellDescription(m + 1, n);
        *adjacent[3] = getCellDescription(m, n + 1);
    }
    else if (n == 0)
    {
        adjacent[0] = new Cell;
        adjacent[1] = 0;
        adjacent[2] = new Cell;
        adjacent[3] = new Cell;
        *adjacent[0] = getCellDescription(m - 1, n);
        *adjacent[2] = getCellDescription(m + 1, n);
        *adjacent[3] = getCellDescription(m, n + 1);
    }
    else if (m == 19)
    {
        adjacent[0] = new Cell;
        adjacent[1] = new Cell;
        adjacent[2] = 0;
        adjacent[3] = new Cell;
        *adjacent[0] = getCellDescription(m - 1, n);
        *adjacent[1] = getCellDescription(m, n - 1);
        *adjacent[3] = getCellDescription(m, n + 1);
    }
    else if (n == 19)
    {
        adjacent[0] = new Cell;
        adjacent[1] = new Cell;
        adjacent[2] = new Cell;
        adjacent[3] = 0;
        *adjacent[0] = getCellDescription(m - 1, n);
        *adjacent[1] = getCellDescription(m, n - 1);
        *adjacent[2] = getCellDescription(m + 1, n);
    }
    else
    {
        adjacent[0] = new Cell;
        adjacent[1] = new Cell;
        adjacent[2] = new Cell;
        adjacent[3] = new Cell;
        *adjacent[0] = getCellDescription(m - 1, n);
        *adjacent[1] = getCellDescription(m, n - 1);
        *adjacent[2] = getCellDescription(m + 1, n);
        *adjacent[3] = getCellDescription(m, n + 1);
    }
}

int Controller::getAdjacentSatisfied(Cell** adjacents, char buildingName, Landform landformType)
{
    // todo: check whether the adjacent cells satisfy the landformType and buildingName(s), you need to rewrite it if you use a hexagonal map
    unsigned satisfiedCellsNum = 0;
    for (int t = 0; t < 4; t++)
    {
        if (adjacents[t] != 0)
        {
            satisfiedCellsNum += ((adjacents[t]->buildingType && (buildingName == 'a' || adjacents[t]->buildingType->name[0] == buildingName)) && adjacents[t]->landform == landformType);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (adjacents[i] != 0)
            delete adjacents[i];
    }
    delete[] adjacents;
    return satisfiedCellsNum;
}
