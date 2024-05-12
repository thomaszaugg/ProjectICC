#ifndef CELL_HPP
#define CELL_HPP
#include "SFML/System/Time.hpp"
#include "Substance.hpp"

class CellsLayer;

class Cell
{
private:
    CellsLayer* cellsLayer;
    Substance* substance;

public:
    Cell(CellsLayer* ptr);

    virtual ~Cell();

    void addSubstance(Substance newSubstance);

    double getQuantitiy(SubstanceId id);

    void uptakeSubstance(double fraction, Cell* cellType, SubstanceId id);

    virtual void update(sf::Time dt)=0;


};

#endif // CELL_HPP
