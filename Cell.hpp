#ifndef CELL_HPP
#define CELL_HPP
#include "Substance.hpp"

class CellsLayer;

class Cell
{
private:
    CellsLayer* cellsLayer;
    Substance* substance;

protected:
    //Substance* getSubstance();

public:
    //Cell(); //default constructor

    Cell(CellsLayer* ptr);

    virtual ~Cell();

    void addSubstance(Substance newSubstance);

    double getQuantitiy(SubstanceId id);

    void uptakeSubstance(double fraction, Cell* cellType, SubstanceId id);

};

#endif // CELL_HPP
