#ifndef TUMORALCELL_HPP
#define TUMORALCELL_HPP
#include "OrganCell.hpp"


class TumoralCell : public OrganCell
{
public:
    TumoralCell(CellsLayer* cellsLayer);

    virtual void uptakeSubstance() override;
    virtual double getFractUptake() override;
    virtual void ATPSynthesis() override;
    virtual void Division() override;

    virtual bool hasCancer() override;
};

#endif // TUMORALCELL_HPP
