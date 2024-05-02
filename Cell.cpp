#include "Cell.hpp"
//#include "Cellslayer.hpp"

Cell::Cell(CellsLayer* cellsLayer)
    : cellsLayer(cellsLayer), substance(new Substance)
{}

Cell::~Cell(){
    delete substance;   //free up allocated memory
    // cellsLayer = nullptr; not needed
}


void Cell::addSubstance(Substance newSubstance){
    *substance += newSubstance;
}

double Cell::getQuantitiy(SubstanceId id){
    return (*substance)[id];
}

void Cell::uptakeSubstance(double fraction, Cell* cellType,  SubstanceId id){
    Substance& receiver = *(cellType->substance);
    substance->uptakeOnGradient(fraction, receiver, id);
}
