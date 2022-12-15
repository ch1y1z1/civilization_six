#include "Grid.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include<string>
using namespace std;
Grid::Grid()
{
    // default constructor is optional
    this->height = this->width = 0;
}


Grid::Grid(char *filename)
{
    // todo: open the file, read it and save the data to this->grid
    ifstream map;
    map.open("map.txt", ios::in);
    string *map_1 = new string[20];
    string a;
    getline(map, a);
    cout << a << endl;
    height = 10 * (a[0] - '0') + a[1] - '0';
    width = 10 * (a[3] - '0') + a[4] - '0';
    for (int i = 0; i < height; i++)
    {
        getline(map, map_1[i]);
        trim(map_1[i]);
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map_1[i][j] == 0)
                grid[i][j].landform =  OCEAN;
            if (map_1[i][j] == 1)
                grid[i][j].landform = SEA;
            if (map_1[i][j] == 2)
                grid[i][j].landform = PLAIN;
            if (map_1[i][j] == 3)
                grid[i][j].landform = HILLY;
            if (map_1[i][j] == 4)
                grid[i][j].landform = DESERT;
            if (map_1[i][j] == 5)
                grid[i][j].landform = MOUNTAIN;
            else
                grid[i][j].landform = NOTYPE;
        }
    }
}
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

char *Grid::getRepresent(int m, int n)
{
    // todo: make up the represent text
    return "repr";
}

Cell **Grid::getGrid()
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
