#ifndef CELL_HPP
#define CELL_HPP

class CellsLayer;

class Cell
{
private:
    CellsLayer* cellsLayer;
    Substance* substance;
public:
    Cell(CellsLayer* ptr);
     virutal ~Cell();
};

#endif // CELL_HPP
