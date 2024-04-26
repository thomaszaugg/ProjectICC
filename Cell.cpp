#include "Cell.hpp"
#include CellsLayer;

Cell::Cell(CellsLayer* ptr)
    : substance(new Substance)
{

}

Cell::~Cell(){
    delete substance;
}
