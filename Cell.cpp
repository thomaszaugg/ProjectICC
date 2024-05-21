#include "Cell.hpp"
#include "CellsLayer.hpp"

Cell::Cell(CellsLayer* cellsLayer)
    : cellsLayer(cellsLayer), substance(new Substance)
{}

Cell::~Cell(){
    delete substance;    //free up allocated memory
    substance = nullptr;
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
void Cell::takeSubstance(double fraction, Cell* donour, SubstanceId id){
    donour->uptakeSubstance(fraction, this, id);
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

void Cell::multiplySubstance(SubstanceId id, double multiplier) const{
   substance->update(id, multiplier);
}

Cell* Cell::getECM() const{
    return cellsLayer->getECM();
}

bool Cell::requestToDivide(bool hasCancer){
    return cellsLayer->requestToDivide(hasCancer);
}
