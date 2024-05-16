#include "CellsLayer.hpp"
#include "Organ.hpp"
#include "Application.hpp"


CellsLayer::CellsLayer(CellCoord position, Organ* organ)
    : position(position), organ(organ), ecm(new ECMCell(this)), organCell(nullptr), bloodCell(nullptr){}


CellsLayer::~CellsLayer(){
    if(ecm!=nullptr)delete ecm;
    ecm=nullptr;
    if(organCell!=nullptr)delete organCell;
    organCell=nullptr;
    if(bloodCell!=nullptr)delete bloodCell;
    bloodCell=nullptr;
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
    }
}

void CellsLayer::setOrganCell(){
    if (organCell==nullptr){
        organCell = (new OrganCell(this));
        organ->updateRepresentationAt(position);
    }
}

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
}// return 0 when there is no quantiy

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

CellCoord CellsLayer::getPosition() const {
    return position;
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

//5.1
void CellsLayer::update(sf::Time dt){
    ecm->update(dt);
    if (hasBloodCell()){
        bloodCell->update(dt);
    }
    if (hasOrganCell()){
        organCell->update(dt);
        if(organCell->isDead()){
            delete organCell;
            organCell = nullptr;
            organ->updateRepresentationAt(position); //after the cell is killed, the texture is updated
        }
    }
}

void CellsLayer::updateCellsLayerAt(const CellCoord& pos, const Substance& diffusedSubst){
    organ->updateCellsLayerAt( pos, diffusedSubst);
}

double CellsLayer::getDeltaVGEF() const{
   return organ->getDelta(VGEF);
}
double CellsLayer::getDeltaGlucose() const{
   return organ->getDelta(GLUCOSE);
}
double CellsLayer::getDeltaBromo() const{
   return organ->getDelta(BROMOPYRUVATE);
}
