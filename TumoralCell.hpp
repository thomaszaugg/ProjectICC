#ifndef TUMORALCELL_HPP
#define TUMORALCELL_HPP
#include "OrganCell.hpp"


class TumoralCell : public OrganCell
{
public:
    TumoralCell(CellsLayer* cellsLayer);

    virtual  void ATPSynthesis(sf::Time dt) override;

    virtual double getFractUptake() override;



    virtual bool hasCancer() override;

    virtual double getKrebsKm() const override;
    virtual double getKrebsVmax() const override;
      virtual double getFractGlu() const override;
    virtual double getDivisonEnergy() const override;

    virtual double getMinNbCycles()const override;
   virtual  double getNbCyclesRange()const override;
};

#endif // TUMORALCELL_HPP
