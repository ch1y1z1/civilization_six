#include "Display.h"
#include<Controller.h>
using namespace std;
char landformNames[80] = {'O', 'S', 'P', 'H', 'D', 'M', 'N'};
char architecture[60] = {'C', 'A', 'T', 'W', 'I'};
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
// 画地图
void Display::DrawMap(Grid *grid, Controller *controller)
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
    cout<< "BLUE means building";
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
                turn_blue();
                cout << architecture[arr.buildingType->num];
                turn_white();
            }
        }
    }
}

int Display::DrawAttributes(Controller *controller, Grid *grid)
{
    // TODO: draw the attributes, population, and the distribution of workers, return the population绘制属性、人口和工人的分布，返回人口
    int pop = controller->getPop();
    int max_pop = controller->getAttributes().food;
    go(50, 0);
    cout << "population now:" << pop;
    go(50, 1);
    cout << "max population:" << max_pop;
    go(50, 3);
    cout << "expected that the population will change to    in Round  ";
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
    cout << "technology:" << controller->getAttributes().tech;
    go(65, 24);
    cout << "culture:" << controller->getAttributes().cul;
    go(65, 25);
    cout << "production:" << controller->getAttributes().prod;
    go(65, 26);
    cout << "score:" << controller->getAttributes().prod + 10 * pop + controller->getAttributes().cul / 2.0 + controller->getAttributes().tech/2.0;
    return pop;
}

void Display::DrawWorkersChange(Controller *controller, int pop)
{
    // TODO: draw the change of workers, and receive the input for changing the distribution of workers绘制工人的变化，并接收改变工人分布的输入
    // go(0, 22);
    // cout << "For example : from (1 1) to (2 3) ";

    // go(0, 23);
    // cout << "choose whether to change (y means yes,n means no)";
    // char s;
    // cin >> s;
    // if (s == 'y' || 'Y')
    // {

    // }
    // else
    // {
    //     go(50, 23);
    //     cout << "you choose not to change the workers";
    // }
}

void Display::DrawProduction(Controller *controller)
{
    // TODO: draw the current production, and receive the input for changing the current production绘制当前产量，并接收改变当前产量的输入
    go(65, 27);
    cout << " provided bonus remaining "<<     " rounds        ";
    go(65, 28);
    cout << "now " << controller->currentProduction->name<<  " is in production             \n";
    int round = controller->getRound();
    go(65, 29);
    cout << "you have done "  ;
}

void Display::MainProcess(Controller *controller, Grid *grid, Building **buildings, Activity **activities)
{
    controller->reset(2);
    controller->bindGrid(grid);
    controller->availableBuildings = buildings;
    this->DrawMap(grid, controller);
    out();
    cout << "Select your city center coords:" << endl;
    while (1)
    {
        int x, y;
        cin >> x >> y;
        Cell arr = grid->getRepresent(x / 2 - 1, y - 1);
        Landform form = arr.landform;
        if (x % 2 != 0 || form == SEA || form == OCEAN || form == MOUNTAIN)
        {
            cout << "invalid input or this place cannot be a center\n";
            continue;
        }
        controller->getCellDescription(x / 2 - 1, y - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1 - 1, y - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1, y - 1 - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1 + 1, y - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1, y + 1 - 1).Pop = OWNED;
        controller->SetProductionBuilding(x / 2 - 1, y - 1, buildings[0]);
        break;
        clear();
    }
    this->DrawMap(grid, controller);
    while (true)
    {
        int newX, newY;
        float nextThres;
        if (controller->nextRound(newX, newY, nextThres))
        {
            cout << "You win." << endl;
            return;
        }
        this->DrawMap(grid, controller);
        int pop = DrawAttributes(controller, grid);
        DrawProduction(controller);
        DrawWorkersChange(controller, pop);
    }
}
