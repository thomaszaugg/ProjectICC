#ifndef BLOODCELL_HPP
#define BLOODCELL_HPP
#include "Cell.hpp"
#include "Types.hpp"

class CellsLayer;

class BloodCell: public Cell
{
private:
    TypeBloodCell type;

public:
    BloodCell(CellsLayer* cellslayer, TypeBloodCell=ARTERY);

    virtual void update(sf::Time dt) override;
};

#endif // BLOODCELL_HPP
