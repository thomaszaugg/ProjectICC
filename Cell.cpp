#include "Cell.hpp"
//#include "Cellslayer.hpp"

Cell::Cell(CellsLayer* cellsLayer)
    : cellsLayer(cellsLayer), substance(new Substance) //how should we initialize substance ?? new Substance or nullptr?
{}                                                      //@lisa exactly the way you did it, because then the substances are initialized as 0

Cell::~Cell(){
    delete substance;   //free up allocated memory
     // cellsLayer = nullptr; //so that the cellslayer doesn't habe this cell anymore
}   //@Lisa i don't think we need the line 10  because the CellsLayer doesn't care what this pointer is (it gets deleted anyway)


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
