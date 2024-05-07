#ifndef ORGANCELL_HPP
#define ORGANCELL_HPP
#include "Cell.hpp"

class CellsLayer;

class OrganCell : public Cell
{
private:

    double atp; //energylevel of a cell

public:

    OrganCell(CellsLayer* cellsLayer);

    virtual void update(sf::Time dt) override;

    bool isDead();

};

#endif // ORGANCELL_HPP
