#include "CellsLayer.hpp"
#include "Organ.hpp"



CellsLayer::CellsLayer(CellCoord position, Organ* organ)
    : position(position), organ(organ), ecm(new ECMCell(this)), organCell(nullptr), bloodCell(nullptr){}


CellsLayer::~CellsLayer(){
    delete ecm;
    delete organCell;
    delete bloodCell;

}

bool CellsLayer::hasECMCell(){
    return ecm!=nullptr;
}

bool CellsLayer::hasOrganCell(){
    return organCell!=nullptr;
}

bool CellsLayer::hasBloodCell(){
    return bloodCell!=nullptr;
}

void CellsLayer::setECMCell(){
    if (ecm==nullptr){
            ecm = new ECMCell(this);
           }}

void CellsLayer::setOrganCell(){
    if (organCell==nullptr){
        organCell = (new OrganCell(this));
        organ->updateRepresentationAt(position);
    }}


void CellsLayer::setBlood(TypeBloodCell type){
    if (bloodCell==nullptr){
        bloodCell = new BloodCell(this, type);
        organ->updateRepresentationAt(position);
    }
}

void CellsLayer::updateSubstance(Substance substance){
    if (hasECMCell()){
        ecm->addSubstance(substance); //method on Cell level
    }
}

double CellsLayer::getECMQuantity(SubstanceId id){
    if (hasECMCell()){
        return ecm->getQuantitiy(id);
    } else {return 0;}
}// is it okay with return 0 ? or throw error ?
//@lisa I think that is something to ask the TA, either way, comment it in the hpp file

double CellsLayer::getOrganCellQuantity(SubstanceId id){
    if (hasOrganCell()){
        return organCell->getQuantitiy(id);
    } else {return 0;}
}

double CellsLayer::getBloodCellQuantity(SubstanceId id){
    if (hasBloodCell()){
        return bloodCell->getQuantitiy(id);
    } else {return 0;}
}

void CellsLayer::organCellTakeFromECM(SubstanceId id, double fraction){
    if (hasOrganCell() && hasECMCell()){
        ecm->uptakeSubstance(fraction, organCell,  id);
    }
}

bool CellsLayer::isOut(const CellCoord& coord){
    return organ->isOut(coord);
}

Cell* CellsLayer::topCell(){
    if (hasBloodCell()){
        return bloodCell;
    }else if (hasOrganCell()){
        return organCell;
    }else {return ecm;}
}
