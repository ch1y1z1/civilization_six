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

Grid::Grid(char* filename){
    // todo: open the file, read it and save the data to this->grid
    ifstream infile1;
	infile1.open("map.txt", ios::in);
	if (!infile1.is_open())
	{
		cout << "读取文件失败" << endl;
		return ;
	}
	//第三种读取方法
	string buf;
	while (getline(infile1, buf))
	{
		cout << buf << endl;
	}
	return ;
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
