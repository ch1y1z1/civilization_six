#include "Display.h"
using namespace std;
char landformNames[8] = { 'O', 'S', 'P', 'H', 'D', 'M', 'N' };
// 移动光标位置至(x,y);
// 隐藏光标;
void Display::go(float x, float y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a, coord);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(a, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(a, &CursorInfo);
}
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
// 划分输入区
void Display::out()
{
    go(0, 22);
    cout << "--------------------------------------------\n";
    cout << "              INTERACT HERE\n";
    go(0, 24);
}
// 清空输入区
void Display::clear()
{
    go(0, 24);
    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 50; i++)
        {
            cout << " ";
        }
        cout << endl;
    }
}
// 画地图
void Display::DrawMap(Grid* grid)
{
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
            go(i, j);
            cout << landformNames[form_int] << " ";
        }
    }

    go(0, 22);
}

int Display::DrawAttributes(Controller* controller, Grid* grid)
{
    // TODO: draw the attributes, population, and the distribution of workers, return the population绘制属性、人口和工人的分布，返回人口
    int pop = controller->getPop();
    int max_pop = controller->getAttributes().food;
    go(25, 0);
    cout << "population now:" << pop;
    go(25, 1);
    cout << "max population:" << max_pop;
    go(25, 2);
    cout << "expected that the population will change to    in Round  ";
    go(25, 3);
    cout << "distribution:";
    static int pop_num = 0;
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 21; j++)
        {
            Cell arr = grid->getRepresent(i - 1, j - 1);
            if (arr.Pop != 0)
            {
                pop_num++;
                go(25, 3 + pop_num);
                cout << "( " << i << " , " << j << " )";
            }
        }
    }
    go(50, 22);
    cout << "technology:" << controller->getAttributes().tech;
    go(50, 23);
    cout << "culture:" << controller->getAttributes().cul;
    go(50, 24);
    cout << "score:" << controller->getAttributes().prod;
    return pop;
}

void Display::DrawWorkersChange(Controller* controller, int pop)
{
    // TODO: draw the change of workers, and receive the input for changing the distribution of workers绘制工人的变化，并接收改变工人分布的输入
    go(0, 22);
    cout << "For example : from (1 1) to (2 3) ";

    go(0, 23);
    cout << "choose whether to change (y means yes,n means no)";
    char s;
    cin >> s;
    if (s == 'y' || 'Y')
    {

    }
    else
    {
        go(50, 23);
        cout << "you choose not to change the workers";
    }
}

void Display::DrawProduction(Controller* controller, Building** buildings)
{
    // TODO: draw the current production, and receive the input for changing the current production绘制当前产量，并接收改变当前产量的输入
    // go(50, 25);
    // cout << "当前正在生产      ，已生产    %";
    // go(50, 26);
    // cout << "请选择是否该改变生产:";
    // string product;

    go(50, 27);
    cout << "     provided bonus remaining      rounds ";
    go(50, 27);

    go(50, 28);
}

void Display::MainProcess(Controller* controller, Grid* grid, Building** buildings, Activity** activities)
{
    controller->reset(3);
    controller->bindGrid(grid);
    this->DrawMap(grid);
    cout << "Select your city center coords:" << endl;
    int x, y;
    cin >> x >> y;
    controller->getCellDescription(x, y).Pop = OWNED;
    controller->getCellDescription(x - 1, y).Pop = OWNED;
    controller->getCellDescription(x, y - 1).Pop = OWNED;
    controller->getCellDescription(x + 1, y).Pop = OWNED;
    controller->getCellDescription(x, y + 1).Pop = OWNED;
    controller->SetProductionBuilding(x, y, buildings[0]);
    this->DrawMap(grid);

    while (true)
    {
        int newX, newY;
        float nextThres;
        if (controller->nextRound(newX, newY, nextThres))
        {
            cout << "You win." << endl;
            return;
        }
        else if (newX != -1)
        {
            cout << "Border expanded at (" << newX << ", " << newY << "), when culture reaches " << nextThres << " border will expand again." << endl;
        }
        DrawMap(grid);
        int pop = DrawAttributes(controller, grid);
        DrawProduction(controller, buildings);
        DrawWorkersChange(controller, pop);
        cout << "\n\nRound: " << controller->getRound() << endl;
    }
}
