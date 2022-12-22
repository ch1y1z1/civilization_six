#include "Display.h"
using namespace std;
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
// 画地图
void Display::DrawMap(Grid *grid)
{
    // TODO: draw the map
    cout << "012345678901234567890X\n"
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
            cout << landformNames[form_int];
        }
    }

    go(0, 22);
}

int Display::DrawAttributes(Controller *controller, Grid *grid)
{
    // TODO: draw the attributes, population, and the distribution of workers, return the population绘制属性、人口和工人的分布，返回人口
    int pop = controller->getPop();
    int max_pop = controller->getAttributes().food;
    go(25, 0);
    cout << "当前人口为 " << pop;
    go(25, 1);
    cout << "最大人口为 " << max_pop;
    go(25, 2);
    cout << "预计\t回合内人口改变为";
    go(25, 3);
    cout << "分布:";
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
    cout << "科技:" << controller->getAttributes().tech;
    go(50, 23);
    cout << "文化:" << controller->getAttributes().cul;
    go(50, 24);
    cout << "分数:" << controller->getAttributes().prod;
    return pop;
}

void Display::DrawWorkersChange(Controller *controller, int pop)
{
    // TODO: draw the change of workers, and receive the input for changing the distribution of workers绘制工人的变化，并接收改变工人分布的输入
    go(0, 22);
    cout << "工人移动实例:(1 1)到(2 3)(数字间以空格分隔)";

    go(0, 23);
    cout << "是否要移动人口：(y代表是,n代表否)";
    char s;
    cin >> s;
    if (s == 'y' || 'Y')
    {
        go(0, 24);
        cout << "工人变化为:从("; //(12,22)
        go(19, 24);
        cout << ")到( ";
        go(25, 24);
        cout << ")";
        go(15, 24);
        int x0, y0;
        cin >> x0 >> y0;
        go(23, 24);
        int x1, y1;
        cin >> x1 >> y1;
    }
    else
    {
        go(50, 23);
        cout << "您选择了不移动人口";
    }
}

void Display::DrawProduction(Controller *controller, Building **buildings)
{
    // TODO: draw the current production, and receive the input for changing the current production绘制当前产量，并接收改变当前产量的输入
    go(0, 25);
    cout << "当前正在生产      ，已生产    %";
    go(14, 26);
    cout << "请选择是否该改变生产:";
    string product;
    
    go(0, 27);
    cout << "     提供的加成剩余  回合";
    go(0, 27);

    go(0, 28);
}

void Display::MainProcess(Controller *controller, Grid *grid, Building **buildings, Activity **activities)
{
    controller->reset(3);
    controller->bindGrid(grid);
    this->DrawMap(grid);
    cout << "Select your city center coords:" << endl;
    int x, y;
    cin >> x >> y;
    controller->SetProductionBuilding(x, y, buildings[0]);
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
        int pop = DrawAttributes(controller,grid);
        DrawProduction(controller, buildings);
        DrawWorkersChange(controller, pop);
        cout << "\n\nRound: " << controller->getRound() << endl;
    }
}
