#ifndef BLOODCELL_HPP
#define BLOODCELL_HPP
#include "Cell.hpp"
#include "Types.hpp"
#include "Utility/Utility.hpp"


class CellsLayer;

class BloodCell: public Cell
{
private:
    TypeBloodCell type;

void update(CellCoord const& pos_bloodcell, CellCoord const& pos_ecm_cell, Substance c0, double const& D, sf::Time  dt);
public:
    BloodCell(CellsLayer* cellslayer, TypeBloodCell type);

    virtual void update(sf::Time dt) override;
};

#endif // BLOODCELL_HPP
