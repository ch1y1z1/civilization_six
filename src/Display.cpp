#include "Display.h"
#include <Controller.h>

using namespace std;
char landformNames[80] = { 'O', 'S', 'P', 'H', 'D', 'M', 'N' };
char architecture[60] = { 'C', 'A', 'T', 'W', 'I' };
// 构造
Display::Display()
{
    // ctor
}
// 析构
Display::~Display()
{
    // dtor
}
/**
 * @brief draw the map and make it colorful
 *
 * @param grid
 * @param controller
 */
void Display::DrawMap(Grid* grid, Controller* controller)
{
    go(0, 0);
    cout << "0 2 4 6 8 10121416182022242628303234363840X\n"
        "1\n"
        "2\n"
        "3\n"
        "4\n"
        "5\n"
        "6\n"
        "7\n"
        "8\n"
        "9\n"
        "0\n"
        "1\n"
        "2\n"
        "3\n"
        "4\n"
        "5\n"
        "6\n"
        "7\n"
        "8\n"
        "9\n"
        "0\n"
        "Y\n";
    go(0, 22);
    cout << "Round: " << controller->getRound();
    // enum Landform{OCEAN=0, SEA, PLAIN, HILLY, DESERT, MOUNTAIN, NOTYPE};
    go(85, 0);
    cout << "RED means owned";
    go(85, 1);
    cout << "GREEN means people";
    go(85, 2);
    cout << "BLUE means building";
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 21; j++)
        {
            Cell arr = grid->getRepresent(i - 1, j - 1);
            Landform form = arr.landform;
            int form_int = (int)form;
            go(2 * i, j);
            if (arr.Pop == WILD)
            {
                cout << "N"
                    << " ";
            }
            else if (arr.Pop == OWNED && arr.buildingType == 0)
            {
                turn_red();
                cout << landformNames[form_int] << " ";
                turn_white();
            }
            else if (arr.buildingType == 0)
            {
                turn_green();
                cout << landformNames[form_int] << " ";
                turn_white();
            }
            else
            {
                if (controller->getCellDescription(i - 1, j - 1).IF_BUILDING == 0)
                    turn_blue();
                else
                    turn_white();
                cout << architecture[arr.buildingType->num];
                turn_white();
            }
        }
    }
}
/**
 * @brief draw the attributes, population, and the distribution of workers, return the population
 *
 * @param controller
 * @param grid
 * @return int pop
 */
int Display::DrawAttributes(Controller* controller, Grid* grid)
{
    int pop = controller->getPop();
    int max_pop = sqrt(controller->getAttributes().food) ;
    go(50, 0);
    cout << "population now:" << pop;
    go(50, 1);
    cout << "max population:" << max_pop;
    go(50, 3);
    float popDelta = (max_pop - pop) * 0.1;
    if (popDelta > 1)
    {
        popDelta = 1;
        pop++;
    }
    else if (popDelta < -1)
    {
        popDelta = -1;
        pop--;
    }
    cout << "expected that the population will change to " << pop << " in Round " << controller->getRound() + 1;
    go(50, 4);
    cout << "distribution:";
    int pop_num = 0;
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 21; j++)
        {
            Cell arr = grid->getRepresent(i - 1, j - 1);
            if (arr.Pop == COLONIZED)
            {
                pop_num++;
                go(50, 4 + pop_num);
                cout << "( " << 2 * i << " , " << j << " )";
            }
        }
    }
    go(65, 23);
    cout << "food:" << controller->getAttributes().food;
    go(65, 24);
    cout << "                         ";
    go(65, 24);
    cout << "technology:" << controller->getAttributes().tech;
    go(65, 25);
    cout << "                         ";
    go(65, 25);
    cout << "culture:" << controller->getAttributes().cul;
    go(65, 26);
    cout << "                         ";
    go(65, 26);
    cout << "production:" << controller->getAttributes().prod;
    go(65, 27);
    cout << "score:" << (controller->getAttributes().prod) + 10 * pop + controller->getAttributes().cul / 2.0 + controller->getAttributes().tech / 2.0;
    return pop;
}
/**
 * @brief draw the current production
 *
 * @param controller
 */
void Display::DrawProduction(Controller* controller)
{
    go(65, 28);
    cout << " provided bonus remaining "
        << " rounds        ";
    go(65, 29);
    cout << "                                     ";
    go(65, 29);
    char a[4] = "cen";
    char b[4] = "cam";
    char c[4] = "the";
    char d[4] = "won";
    char e[4] = "ind";
    int zi = controller->get_round_needed_to_active();
    int mu = controller->get_totle_round_needed();
    if (mu == -1)
    {
        cout << "no production";
    }
    else
    {
        if (strcmp(controller->currentProduction->name, a) == 0)
            cout << "now center is in production \n";
        else if (strcmp(controller->currentProduction->name, b) == 0)
            cout << "now campus is in production \n";
        else if (strcmp(controller->currentProduction->name, c) == 0)
            cout << "now theater is in production \n";
        else if (strcmp(controller->currentProduction->name, d) == 0)
            cout << "now wonder is in production \n";
        else if (strcmp(controller->currentProduction->name, e) == 0)
            cout << "now industry is in production \n";
        go(65, 30);
        cout << "                                         ";
        go(65, 30);
        float percent = (float)zi / mu;
        cout << "you have done " << (1 - percent) * 100 << " % "
            << " TOTAL: " << mu;
    }
}

void Display::MainProcess(Controller* controller, Grid* grid, Building** buildings, Activity** activities)
{
    controller->availableActivities = activities;
    controller->currentAttributes.prod = 0;
    controller->reset(2);
    controller->currentAttributes.prod = 0;
    controller->bindGrid(grid);
    controller->availableBuildings = buildings;
    controller->new_availableActivities = new Activity * [3];
    this->DrawMap(grid, controller);
    DrawAttributes(controller, grid);
    out();
    cout << "Select your city center coords:" << endl;
    while (1)
    {
        int x, y;
        cin >> x >> y;
        Cell arr = grid->getRepresent(x / 2 - 1, y - 1);
        Landform form = arr.landform;
        if (x % 2 != 0 || form == SEA || form == OCEAN || form == MOUNTAIN || x > 40 || y > 20 || x < 2 || y < 1)
        {
            cout << "Invalid input or this place cannot be a center\n";
            continue;
        }
        controller->getCellDescription(x / 2 - 1, y - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1 - 1, y - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1, y - 1 - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1 + 1, y - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1, y + 1 - 1).Pop = OWNED;
        controller->SetProductionBuilding(x / 2 - 1, y - 1, buildings[0]);
        break;
    }
    clear();
    this->DrawMap(grid, controller);
    while (true)
    {
        int newX, newY;
        float nextThres;
        if (controller->getRound()==100)
        {
            if (controller->checkWin())
            {
                cout <<"YOU WIN!!!"<<endl;
                return;
            }
            else {
                 cout <<"YOU LOSE!!!"<<endl;
                 return;
            }            
        }
        else if (controller->nextRound(newX, newY, nextThres))
        {
            cout <<"YOU WIN!!!"<<endl;
            return;
        }
        this->DrawMap(grid, controller);
        DrawAttributes(controller, grid);
        DrawProduction(controller);
    }
}
