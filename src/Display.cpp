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
//构造
Display::Display()
{
    //ctor
}
//析构
Display::~Display()
{
    //dtor
}
//画地图
void Display::DrawMap(Grid* grid){
    // TODO: draw the map
    cout << "012345678901234567890X\n"
            "1NNNNNNNNNNNNNNNNNNNN\n"
            "2NNNNNNNNNNNNNNNNNNNN\n"
            "3NNNNNNNNNNNNNNNNNNNN\n"
            "4NNNNNNNNNNNNNNNNNNNN\n"
            "5NNNNNNNNNNNNNNNNNNNN\n"
            "6NNNNNNNNNNNNNNNNNNNN\n"
            "7NNNNNNNNNNNNNNNNNNNN\n"
            "8NNNNNNNNNNNNNNNNNNNN\n"
            "9NNNNNNNNNNNNNNNNNNNN\n"
            "0NNNNNNNNNNNNNNNNNNNN\n"
            "1NNNNNNNNNNNNNNNNNNNN\n"
            "2NNNNNNNNNNNNNNNNNNNN\n"
            "3NNNNNNNNNNNNNNNNNNNN\n"
            "4NNNNNNNNNNNNNNNNNNNN\n"
            "5NNNNNNNNNNNNNNNNNNNN\n"
            "6NNNNNNNNNNNNNNNNNNNN\n"
            "7NNNNNNNNNNNNNNNNNNNN\n"
            "8NNNNNNNNNNNNNNNNNNNN\n"
            "9NNNNNNNNNNNNNNNNNNNN\n"
            "0NNNNNNNNNNNNNNNNNNNN\n"
            "Y\n";
            
    char *arr= grid->getRepresent();

    go(0, 22);
}

int Display::DrawAttributes(Controller* controller){
    // TODO: draw the attributes, population, and the distribution of workers, return the population绘制属性、人口和工人的分布，返回人口
    go(25, 0);
    cout << "当前人口为";
    go(25, 1); //(36,0)
    cout << "最大人口为";
    go(25, 2); //(36,1)
    cout << "预计\t回合内人口改变为";
    go(25, 3);       //(50,2)(30,2)
    cout << "分布:"; //(36,0)     
    go(50, 22);
    cout << "科技:";
    go(50, 23);
    cout << "文化:";
    go(50, 24);
    cout << "分数:";
    return 0;
}

void Display::DrawWorkersChange(Controller* controller, int pop){
    // TODO: draw the change of workers, and receive the input for changing the distribution of workers绘制工人的变化，并接收改变工人分布的输入
    go(0, 22);
    cout << "工人移动实例:(1 1)到(2 3)(数字间以空格分隔)";
    go(0, 23);
    cout << "工人变化为:从(";//(12,22)
    go(18, 23);
    cout << ")到( ";
    go(28, 23);
    cout << ")";
    go(12, 23);
    int x0, y0;
    cin >> x0 >> y0;
    go(22, 23);
    int x1, y1;
    cin >> x1 >> y1;
}

void Display::DrawProduction(Controller* controller, Building** buildings){
    // TODO: draw the current production, and receive the input for changing the current production绘制当前产量，并接收改变当前产量的输入
    go(0, 24);
    cout << "当前正在生产      ，已生产    %";
    go(14, 24);
    cout << "";
    go(0, 25);
    cout << "     提供的加成剩余  回合";
    go(0, 25);

    go(20, 25);
}

void Display::MainProcess(Controller* controller, Grid* grid, Building** buildings, Activity** activities){
    controller->reset(3);
    controller->bindGrid(grid);
    this->DrawMap(grid);
    cout << "Select your city center coords:" << endl;
    int x, y;
    cin >> x >> y;
    controller->SetProductionBuilding(x, y, buildings[0]);
    while(true){
        int newX, newY;
        float nextThres;
        if(controller->nextRound(newX, newY, nextThres)){
            cout << "You win." << endl;
            return;
        }
        else if (newX != -1){
            cout << "Border expanded at (" << newX << ", " << newY << "), when culture reaches " << nextThres << " border will expand again." << endl;
        }
        DrawMap(grid);
        int pop = DrawAttributes(controller);
        DrawProduction(controller, buildings);
        DrawWorkersChange(controller, pop);
        cout << "\n\nRound: " << controller->getRound() << endl;
    }
}
