#ifndef TUMORALCELL_HPP
#define TUMORALCELL_HPP
#include "OrganCell.hpp"


class TumoralCell : public OrganCell
{
public:
    TumoralCell(CellsLayer* cellsLayer);

    virtual  void ATPSynthesis(sf::Time dt) override;

    virtual double getFractUptake() override;

    virtual void Division() override;

    virtual bool hasCancer() override;

    virtual double getKrebsKm() const override;
    virtual double getKrebsVmax() const override;
      virtual double getFractGlu() const override;
};

#endif // TUMORALCELL_HPP
