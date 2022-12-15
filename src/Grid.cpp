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
    this->height = 10 * (a[0] - '0') + a[1] - '0';
    this->width = 10 * (a[3] - '0') + a[4] - '0';
    for (int i = 0; i < this->height; i++)
    {
        getline(map, map_1[i]);
        trim(map_1[i]);
    }
   this->grid=new Cell *[this->height];
   for(int i=0;i<this->height;i++){this->grid[i]=new Cell [this->width];}
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            if (map_1[i][j] == 0)
                this->grid[i][j].landform =  OCEAN;
            if (map_1[i][j] == 1)
               this->grid[i][j].landform = SEA;
            if (map_1[i][j] == 2)
                this->grid[i][j].landform = PLAIN;
            if (map_1[i][j] == 3)
                this->grid[i][j].landform = HILLY;
            if (map_1[i][j] == 4)
                this->grid[i][j].landform = DESERT;
            if (map_1[i][j] == 5)
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
