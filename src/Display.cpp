#include "Display.h"

#include <iostream>
using namespace std;

Display::Display()
{
    //ctor
}

Display::~Display()
{
    //dtor
}

void Display::DrawMap(Grid* grid){
    // TODO: draw the map
    
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
