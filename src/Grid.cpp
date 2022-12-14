#include "Grid.h"
#include <fstream>
#include <iostream>

using namespace std;
Grid::Grid()
{
    // default constructor is optional
    this->height = this->width = 0;
}


Grid::Grid(const char* filename)
{
    // todo: open the file, read it and save the data to this->grid
    ifstream map;
    map.open("../resource/map.txt", ios::in);
    string* map_1 = new string[20];
    string a;
    getline(map, a);
    this->height = 10 * (a[0] - '0') + a[1] - '0';
    this->width = 10 * (a[3] - '0') + a[4] - '0';
    for (int i = 0; i < this->height; i++)
    {
        getline(map, map_1[i]);
        trim(map_1[i]);
    }
    this->grid = new Cell * [this->height];
    for (int i = 0; i < this->height; i++) { this->grid[i] = new Cell[this->width]; }
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            if (map_1[i][j] == '0')
                this->grid[i][j].landform = OCEAN;
            else if (map_1[i][j] == '1')
                this->grid[i][j].landform = SEA;
            else if (map_1[i][j] == '2')
                this->grid[i][j].landform = PLAIN;
            else if (map_1[i][j] == '3')
                this->grid[i][j].landform = HILLY;
            else if (map_1[i][j] == '4')
                this->grid[i][j].landform = DESERT;
            else if (map_1[i][j] == '5')
                this->grid[i][j].landform = MOUNTAIN;
            else
                this->grid[i][j].landform = NOTYPE;
        }
    }
}
//delete all space in string objects
void trim(string& s)
{
    int index = 0;
    if (!s.empty())
    {
        while ((index = s.find(' ', index)) != string::npos)
        {
            s.erase(index, 1);
        }
    }
}

Grid::~Grid()
{
    // delete this->grid
    for (int i = 0; i < this->height; i++)
        delete[] this->grid[i];
    delete[] this->grid;
}

Cell& Grid::getRepresent(int m, int n)
{
    // todo: make up the represent text
    return this->grid[m][n];
}

Cell** Grid::getGrid()
{
    return this->grid;
}

int Grid::getGridHeight()
{
    return this->height;
}

int Grid::getGridWidth()
{
    return this->width;
}
