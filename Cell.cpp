#include "Cell.hpp"
//#include "Cellslayer.hpp"

Cell::Cell(CellsLayer* cellsLayer)
    : cellsLayer(cellsLayer), substance(new Substance) //how should we initialize substance ?? new Substance or nullptr?
{}

Cell::~Cell(){
    delete substance;
    cellsLayer = nullptr; //so that the cellslayer doesn't habe this cell anymore
}

/*
Substance* Cell::getSubstance(){
    return substance;
}*/

void Cell::addSubstance(Substance newSubstance){
    *substance += newSubstance; //is the value of the pointer really updated?
}

double Cell::getQuantitiy(SubstanceId id){
    return (*substance)[id];
}

void Cell::uptakeSubstance(double fraction, Cell* cellType,  SubstanceId id){
    Substance& receiver = *(cellType->substance);
    substance->uptakeOnGradient(fraction, receiver, id);
}
