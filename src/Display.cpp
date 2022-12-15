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
    go(0, 22);
}

int Display::DrawAttributes(Controller* controller){
    // TODO: draw the attributes, population, and the distribution of workers, return the population绘制属性、人口和工人的分布，返回人口
}

void Display::DrawWorkersChange(Controller* controller, int pop){
    // TODO: draw the change of workers, and receive the input for changing the distribution of workers绘制工人的变化，并接收改变工人分布的输入
}

void Display::DrawProduction(Controller* controller, Building** buildings){
    // TODO: draw the current production, and receive the input for changing the current production绘制当前产量，并接收改变当前产量的输入
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
