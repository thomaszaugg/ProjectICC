#ifndef ECMCELL_HPP
#define ECMCELL_HPP
#include "Cell.hpp"

class CellsLayer;

class ECMCell : public Cell
{
public:
    ECMCell(CellsLayer* cellsLayer);

    virtual void update(sf::Time dt) override;

    ~ECMCell()=default;
};

#endif // ECMCELL_HPP
