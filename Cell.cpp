#include "Cell.hpp"
#include "CellsLayer.hpp"

Cell::Cell(CellsLayer* cellsLayer)
    : cellsLayer(cellsLayer), substance(new Substance)
{}

Cell::~Cell(){
    delete substance;   //free up allocated memory
    //std::cout << "I die";
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

CellsLayer* Cell::getCellsLayer() const{
    return cellsLayer;
}

double Cell::getDeltaVGEF() const{
    return cellsLayer->getDeltaVGEF();
}
double Cell::getDeltaGlucose() const{
    return cellsLayer->getDeltaGlucose();
}
double Cell::getDeltaBromo() const{
    return cellsLayer->getDeltaBromo();
}
