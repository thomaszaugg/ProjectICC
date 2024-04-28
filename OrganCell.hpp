#ifndef ORGANCELL_HPP
#define ORGANCELL_HPP
#include "Cell.hpp"

class CellsLayer;

class OrganCell : public Cell
{
public:
    OrganCell(CellsLayer* cellsLayer);
};

#endif // ORGANCELL_HPP
