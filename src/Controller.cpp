#include "Controller.h"
#include "cstring"
#include "Display.h"

const int landformBuffs[7][2] = {
    {1, 0}, {1, 1}, {2, 1}, {2, 2}, {0, 1}, {0, 0}, {0, 0} };

Controller::Controller()
{
    this->currentRound = 1;
    this->world = 0;
    this->pop = 2;
    this->workingPop = 0;
    this->currentAttributes = Attributes(0);
}

Controller::~Controller()
{
    // dtor
}

/**
 *@brief
 *
 * @return int round needed to active
 */
int Controller::get_round_needed_to_active()
{
    return this->round_needed_to_active;
}

int Controller::get_totle_round_needed()
{
    return this->totle_round_needed;
}

void Controller::reset(int pop, float firstBorderThreshold)
{
    this->currentRound = 1;
    this->world = 0;
    this->pop = pop;
    this->workingPop = 0;
    this->currentAttributes = Attributes(0, 0, 0, 0.5);
}

/**
 *@brief check whether the player has won the game
 *
 * @return true
 * @return false
 */
bool Controller::checkWin()
{
    // todo: check whether the player has won the game
    int won = 0;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (this->getCellDescription(i, j).buildingType == 0)
                continue;
            else if (this->getCellDescription(i, j).buildingType->num == 3)
                won++;
        }
    }
    if (this->currentAttributes.tech >= 500)
        return true;
    if (this->currentAttributes.cul >= 350 && won == 5)
        return true;
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

/**
 *@brief Get a reference to a cell (m, n) for modification
 *
 * @param m x
 * @param n y
 * @return Cell& reference to the cell
 */

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

/**
 *@brief main process of the controller here
 * first check if the player has won the game
 * if not, then update the current round
 * then check if the border should be updated
 * then change the distribution of population
 * then update the production
 * then update the attributes
 * @param newX
 * @param newY
 * @param nextThres
 * @return true
 * @return false
 */
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


/**
 *@brief update the attributes of the controller
 * first check if the current production is finished
 * if finished, then cin players choice
 * if not finished, then update the production
 *
 * @return int if the production is finished
 */
int Controller::updateProduction()
{
    // todo: update the process of current production
    // std::cout << "Please select one production" << std::endl;
    // char Buildingnames[20][20] = { "center", "campus", "theatre", "wonder", "industrialpark" };
    if (this->buffround == -1)
    {
        ;
    }
    else if (this->buffround == 0)
    {
        this->currentAttributes -= this->buffactivity->basicBonus;
        this->buffround = -1;
    }
    else
    {
        this->buffround--;
    }
    if (this->currentAttributes.prod == 0)
    {
        clear();
        out();
        std::cout << "you have no production now." << std::endl;
        std::cout << "you are not able to product anything." << std::endl;
        std::cout << "press any key to continue" << std::endl;
        std::cin.get();
        std::cin.get();
        clear();
        return this->getRound();
    }
    if (this->currentProductionType == 0)
    {
    label:
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
                    std::cout << "Invalid input: Out of range" << std::endl;
                    continue;
                }
                else if (this->getCellDescription(m, n).Pop == WILD)
                {
                    std::cout << "Invalid input: The cell haven't been owned now" << std::endl;
                    continue;
                }
                else if (this->getCellDescription(m, n).landform == OCEAN || this->getCellDescription(m, n).landform == SEA && this->getCellDescription(m, n).landform == MOUNTAIN)
                {
                    std::cout << "Invalid input: You cannot set a building in this landform " << std::endl;
                    continue;
                }
                else if (this->getCellDescription(m, n).buildingType != 0)
                {
                    std::cout << "Invalid input: There has been a building yet" << std::endl;
                    continue;
                }
                std::cout << "Please select one building" << std::endl;
                for (int i = 0; i < 5; i++)
                {
                    // std::cout << i << ". " << Buildingnames[i] << std::endl;
                    std::cout << i << ". " << this->availableBuildings[i]->name << std::endl;
                }
                std::cin >> buildingchoice;
                if (buildingchoice == 0) {
                    std::cout << "Invalid input: only one center is permitted" << std::endl;
                    continue;
                }
                if (buildingchoice < 0 || buildingchoice > 4)
                {
                    std::cout << "Invalid input: Out of range" << std::endl;
                    continue;
                }
                this->currentProductionType = PRODUCTION_TYPE_BUILDING;
                this->currentProductionCell = &this->getCellDescription(m, n);
                this->currentProduction = this->availableBuildings[buildingchoice];
                this->prod_needed_to_active = this->availableBuildings[buildingchoice]->prodSpent * this->getRound() / 100;
                this->round_needed_to_active = this->prod_needed_to_active / this->currentAttributes.prod + 1;
                this->totle_round_needed = this->round_needed_to_active;
                this->getCellDescription(m, n).buildingType = this->availableBuildings[buildingchoice];
                this->getCellDescription(m, n).IF_BUILDING = 1;

                break;
            }
            // this->currentProductionType = PRODUCTION_TYPE_BUILDING;
            // this->currentProductionCell = 0;
            // this->currentProduction = ;
            break;
        case 2:
            if (this->buffround >= 0)
            {
                std::cout << "Invalid input:\n You are in another activity's buff now" << std::endl;
                std::cout << "press any key to continue" << std::endl;
                std::cin.get();
                std::cin.get();
                goto label;
            }
            int activitychoice;
            while (1)
            {
                bool flag = false;
                this->activitySize = 0;
                std::cout << "please select one activity" << std::endl;
                bool if_activity[20] = { 0 };
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if (this->getCellDescription(i, j).buildingType != 0)
                        {
                            if_activity[this->getCellDescription(i, j).buildingType->num] = 1;
                        }
                    }
                }
                if (if_activity[1] == 1)
                {
                    this->new_availableActivities[this->activitySize] = this->availableActivities[0];
                    this->activitySize++;
                }
                if (if_activity[2] == 1)
                {
                    this->new_availableActivities[this->activitySize] = this->availableActivities[1];
                    this->activitySize++;
                }
                if (if_activity[4] == 1)
                {
                    this->new_availableActivities[this->activitySize] = this->availableActivities[2];
                    this->activitySize++;
                }
                for (int i = 0; i < this->activitySize; i++)
                {
                    std::cout << i + 1 << ". " << this->new_availableActivities[i]->name << std::endl;
                }
                std::cout << "input 0 to go back" << std::endl;
                std::cin >> activitychoice;
                if (activitychoice < 0 || activitychoice > this->activitySize)
                {
                    std::cout << "Invalid input: Out of range" << std::endl;
                    continue;
                }
                if (activitychoice == 0)
                {
                    goto label;
                }
                this->currentProductionType = PRODUCTION_TYPE_ACTIVITY;
                this->currentProduction = this->availableActivities[activitychoice];
                this->prod_needed_to_active = this->availableActivities[activitychoice]->prodSpent * this->getRound() / 100;
                this->round_needed_to_active = this->prod_needed_to_active / this->currentAttributes.prod + 1;
                this->totle_round_needed = this->round_needed_to_active;
                this->buffactivity = this->availableActivities[activitychoice];
                this->buffattr = this->availableActivities[activitychoice]->basicBonus * this->pop;

                break;
            }
            break;
        }
        clear();
    }
    else
    {
        if (this->currentProductionType == PRODUCTION_TYPE_BUILDING)
        {
            if (this->round_needed_to_active <= 0)
            {
                this->currentProductionCell->IF_BUILDING = 0;
                this->currentProductionType = 0;
                this->prod_needed_to_active = 0;
            }
            else
            {
                this->round_needed_to_active--;
            }
        }
        if (this->currentProductionType == PRODUCTION_TYPE_ACTIVITY)
        {
            if (this->round_needed_to_active <= 0)
            {
                this->currentProductionType = 0;
                this->prod_needed_to_active = 0;
                this->buffround = 5;
                this->currentAttributes += this->buffactivity->basicBonus * 1;
            }
            else
            {
                this->round_needed_to_active--;
            }
        }
    }
    return this->getRound();
}

Production* Controller::getProduction(int& productionType, Cell*& currentProductionCell)
{
    productionType = this->currentProductionType;
    currentProductionCell = this->currentProductionCell;
    return this->currentProduction;
}

/**
 *@brief check whether the population should update or not,
 *
 * @return int
 * 0: no need to update
 * 1: need to add pops
 * -1: need to remove pops
 */
int Controller::checkPop()
{
    if (int(this->workingPop) > this->pop)
        return -1; // you have to remove pops
    else if (int(this->workingPop) < this->pop)
        return 1; // you may add pops to work
    else
        return 0; // you may switch pops
}

/**
 *@brief update the population according to the current food
 *
 */
void Controller::updatePop()
{
    int maxpop = this->currentAttributes.food / 2;
    float popDelta = (maxpop - pop) * 0.2;
    if (popDelta > 1)
        popDelta = 1;
    else if (popDelta < -1)
        popDelta = -1;
    else
        popDelta = 0;
    this->pop += popDelta;
}

/**
 *@brief check whether the border should update or not,
 * and if so, cin player's choice of the new border and return the new culture threshold
 *
 * @param newX x coordinate of the new border
 * @param newY y coordinate of the new border
 * @param nextThres culture threshold of the new border
 * @return int
 */
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
        // 判断是否越界
        while (true)
        {
            if (newX > 40 || newY > 20 || newX < 2 || newY < 1)
                std::cout << "Invalid input: The expended coordinate is out of the map" << std::endl;
            else
                break;
            cin >> newX >> newY;
        }
        // 判断是否与现有边界相连
        while (true)
        {
            if (getCellDescription(newX / 2 - 1, newY).Pop == WILD && getCellDescription(newX / 2, newY - 1).Pop == WILD && getCellDescription(newX / 2 - 2, newY - 1).Pop == WILD && getCellDescription(newX / 2 - 1, newY - 2).Pop == WILD)
                std::cout << "Invalid input: The expended coordinate is out of your area" << std::endl;
            else
                break;
            cin >> newX >> newY;
        }
        while (true)
        {
            if (this->getCellDescription(newX / 2 - 1, newY - 1).Pop != WILD)
            {
                std::cout << "Invalid input: This cell has been expanded" << std::endl;
            }
            else
                break;
            cin >> newX >> newY;
        }
        this->getCellDescription(newX / 2 - 1, newY - 1).Pop = OWNED;
        clear();
        return 1;
    }
    clear();
    return 0;
}

/**
 *@brief check whether the pop should be added or removed, and if so, cin player's choice
 * and make the changes
 * cin player's choice of switch pops
 *
 * @return int
 */
int Controller::setPopAt()
{
    updatePop();
    // todo: add or remove the worker at (m, n), return 0 if the action is successful
    bool flag = this->checkPop();
    out();
    while (flag != 0)
    {
        switch (flag)
        {
        case -1:
            clear();
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
                    std::cout << "Invalid input: There is no pop at this cell" << std::endl;
                }
            }
            clear();
            break;
        case 1:
            clear();
            out();
            std::cout << "You may add pop to work" << std::endl;
            while (true)
            {
                std::cout << "Please input the coordinates of the pop you want to add" << std::endl;
                int x, y;
                std::cin >> x >> y;
                if (this->getCellDescription(x / 2 - 1, y - 1).Pop == OWNED && this->getCellDescription(x / 2 - 1, y - 1).landform != MOUNTAIN && this->getCellDescription(x / 2 - 1, y - 1).landform != OCEAN)
                {
                    this->getCellDescription(x / 2 - 1, y - 1).Pop = COLONIZED;
                    this->workingPop++;
                    break;
                }
                else if (this->getCellDescription(x / 2 - 1, y - 1).Pop == OWNED && (this->getCellDescription(x / 2 - 1, y - 1).landform != SEA || this->getCellDescription(x / 2 - 1, y - 1).landform == PLAIN || this->getCellDescription(x / 2 - 1, y - 1).landform == DESERT || this->getCellDescription(x / 2 - 1, y - 1).landform == HILLY))
                {
                    std::cout << "Invalid input: You cannot add pop to this landform" << std::endl;
                }
                else if (this->getCellDescription(x / 2 - 1, y - 1).Pop == COLONIZED)
                {
                    std::cout << "Invalid input: There has already been a pop at this cell" << std::endl;
                }
                else if (this->getCellDescription(x / 2 - 1, y - 1).Pop == WILD)
                {
                    std::cout << "Invalid input: This cell haven't been owned now" << std::endl;
                }
            }
            clear();
            break;
        }
        flag = this->checkPop();
        // display->DrawMap(grid);
    }
    out();
    while (true)
    {
        std::cout << "You may switch pops now" << std::endl;
        std::cout << "Please input the coordinates of the pop you want to switch \nor you may input '0' to skip this step" << std::endl;
        int x, y, newx, newy;
        std::cin >> x;
        if (x == 0)
            return 0;
        std::cin >> y >> newx >> newy;
        Cell arr = this->getCellDescription(newx / 2 - 1, newy - 1);
        Landform form = arr.landform;
        if (newx % 2 != 0 || form == SEA || form == OCEAN || form == MOUNTAIN)
        {
            cout << "invalid input\n";
            continue;
        }
        if (!(this->getCellDescription(x / 2 - 1, y - 1).Pop == COLONIZED))
        {
            std::cout << "Invalid input: There is no pop at this cell" << std::endl;
            continue;
        }
        if (this->getCellDescription(newx / 2 - 1, newy - 1).Pop == COLONIZED)
        {
            std::cout << "Invalid input: There has already been a pop at this cell" << std::endl;
            continue;
        }
        if (this->getCellDescription(newx / 2 - 1, newy - 1).Pop == WILD)
        {
            std::cout << "Invalid input: The cell haven't been owned now" << std::endl;
            continue;
        }
        this->getCellDescription(x / 2 - 1, y - 1).Pop = OWNED;
        this->getCellDescription(newx / 2 - 1, newy - 1).Pop = COLONIZED;
        std::cout << "Switch successfully" << std::endl;
        break;
        clear();
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
            if (this->getCellDescription(i, j).Pop == COLONIZED && this->getCellDescription(i, j).buildingType == 0)
            {
                this->currentAttributes.food += 1 * landformBuffs[this->getCellDescription(i, j).landform][0];
                this->currentAttributes.prod += 0.5 * landformBuffs[this->getCellDescription(i, j).landform][1];
            }
            if (this->getCellDescription(i, j).buildingType != 0 && this->getCellDescription(i, j).IF_BUILDING == 0 && this->getCellDescription(i, j).Pop == COLONIZED)
            {
                this->currentAttributes += this->getCellDescription(i, j).buildingType->basicBonus * 1;
            }
        }
    }
}

Cell** Controller::getAdjacentCells(int m, int n)
{ // todo: get the adjacent cells from cell (m, n)
    // you can use this as :Cell** adjacent=getAdjacentCells(m,n) to get the details of (m,n)'s up, left ,down and right
    // Cell adj=new Cell[1];

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
    return adjacent;
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