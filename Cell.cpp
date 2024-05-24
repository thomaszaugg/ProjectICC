#include "Cell.hpp"
#include "CellsLayer.hpp"

Cell::Cell(CellsLayer* cellsLayer)
    : cellsLayer(cellsLayer), substance(new Substance)
{}

Cell::~Cell(){
  //  uptakeSubstance(1, getECM(),BROMOPYRUVATE);// after death of a cell, release the inhibitor
    delete substance;    //free up allocated memory
    substance = nullptr;
}

void Cell::addSubstance(Substance newSubstance){
    *substance += newSubstance;
}

double Cell::getQuantitiy(SubstanceId id) const{
    return (*substance)[id];
}

void Cell::uptakeSubstance(double fraction, Cell* receiverCell,  SubstanceId id){
    Substance& receiver = *(receiverCell->substance);
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

bool Cell::requestToDivide(bool hasCancer) const{
    return cellsLayer->requestToDivide(hasCancer);
}
