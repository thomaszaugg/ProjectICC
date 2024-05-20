#ifndef TUMORALCELL_HPP
#define TUMORALCELL_HPP
#include "OrganCell.hpp"


class TumoralCell : public OrganCell
{
private:

    virtual double getFractUptake() const override;
    virtual double getKrebsKm() const override;
    virtual double getKrebsVmax() const override;
    virtual double getFractGlu() const override;
    virtual double getDivisonEnergy() const override;

    virtual double getMinNbCycles()const override;
    virtual  double getNbCyclesRange()const override;


public:
    TumoralCell(CellsLayer* cellsLayer);

    virtual bool hasCancer() override;

};

#endif // TUMORALCELL_HPP
