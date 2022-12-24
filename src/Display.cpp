#include "Display.h"
using namespace std;
char landformNames[8] = { 'O', 'S', 'P', 'H', 'D', 'M', 'N' };
char architecture[6] = { 'C', 'A', 'T', 'W', 'I' };
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
void Display::DrawMap(Grid* grid)
{
    go(0, 0);
    // TODO: draw the map
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

    // enum Landform{OCEAN=0, SEA, PLAIN, HILLY, DESERT, MOUNTAIN, NOTYPE};
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
            else
            {
                turn_blue();
                cout << architecture[arr.buildingType->num];
                turn_white();
            }
        }
    }
    go(0, 22);
}

int Display::DrawAttributes(Controller* controller, Grid* grid)
{
    // TODO: draw the attributes, population, and the distribution of workers, return the population绘制属性、人口和工人的分布，返回人口
    go(0, 22);
    cout << "\n\nRound: " << controller->getRound() << endl;
    int pop = controller->getPop();
    int max_pop = controller->getAttributes().food;
    go(50, 0);
    cout << "population now:" << pop;
    go(50, 1);
    cout << "max population:" << max_pop;
    go(50, 2);
    cout << "expected that the population will change to    in Round  ";
    go(50, 3);
    cout << "distribution:";
    static int pop_num = 0;
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 21; j++)
        {
            Cell arr = grid->getRepresent(i - 1, j - 1);
            if (arr.Pop == COLONIZED)
            {
                pop_num++;
                go(50, 3 + pop_num);
                cout << "( " << 2 * i << " , " << j << " )";
            }
        }
    }
    go(65, 23);
    cout << "technology:" << controller->getAttributes().tech;
    go(65, 24);
    cout << "culture:" << controller->getAttributes().cul;
    go(65, 25);
    cout << "score:" << controller->getAttributes().prod;
    return pop;
}

void Display::DrawWorkersChange(Controller* controller, int pop)
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

void Display::DrawProduction(Controller* controller, Building** buildings)
{
    // TODO: draw the current production, and receive the input for changing the current production绘制当前产量，并接收改变当前产量的输入
    // go(50, 25);
    // cout << "当前正在生产      ，已生产    %";
    // go(50, 26);
    // cout << "请选择是否该改变生产:";
    // string product;

    go(65, 27);
    cout << "     provided bonus remaining      rounds ";
    go(65, 27);

    go(65, 28);
}

void Display::MainProcess(Controller* controller, Grid* grid, Building** buildings, Activity** activities)
{
    controller->reset(3);
    controller->bindGrid(grid);
    controller->availableBuildings = buildings;
    this->DrawMap(grid);
    out();
    cout << "Select your city center coords:" << endl;
    int x, y;
    cin >> x >> y;
    if (x % 2 != 0)
    {
        cout << "invalid input";
    }
    else
    {
        controller->getCellDescription(x / 2 - 1, y - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1 - 1, y - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1, y - 1 - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1 + 1, y - 1).Pop = OWNED;
        controller->getCellDescription(x / 2 - 1, y + 1 - 1).Pop = OWNED;
        controller->SetProductionBuilding(x / 2 - 1, y - 1, buildings[0]);
    }
    clear();
    this->DrawMap(grid);
    while (true)
    {
        int newX, newY;
        float nextThres;
        if (controller->nextRound(newX, newY, nextThres, this))
        {
            cout << "You win." << endl;
            return;
        }
        DrawMap(grid);
        int pop = DrawAttributes(controller, grid);
        DrawProduction(controller, buildings);
        DrawWorkersChange(controller, pop);
    }
}
