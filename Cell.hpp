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
    void takeSubstance(double fraction, Cell* donour,SubstanceId id);
    virtual void update(sf::Time dt)=0;

    CellsLayer* getCellsLayer() const;

double getDeltaVGEF() const;
double getDeltaGlucose() const;
double getDeltaBromo() const;

protected:
 void multiplySubstance(SubstanceId id, double multiplier) const;
Cell* getECM() const;

};

#endif // CELL_HPP
