#ifndef GRID_H
#define GRID_H
#include "Building.h"

// this enumerate type represents if the cell is a wild area or owned by a city, or covered with population
enum Civilized{WILD=0, OWNED, COLONIZED};

struct Cell{
    Landform landform = PLAIN;
    Civilized Pop = WILD;   // whether the cell has population
    Building* buildingType = 0;
    float prodAccumulated = 0.0;
    Cell(){}
    Cell(Landform landform):landform(landform){}
    ~Cell(){}
};

class Grid
{
    public:
        Grid();

        Grid(char* filename);

        ~Grid();

        Cell** getGrid();

        int getGridHeight();
        int getGridWidth();

        char* getRepresent(int m, int n);

    protected:

    private:
        Cell **grid;
        int height, width;
};

#endif // GRID_H
