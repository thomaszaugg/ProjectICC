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

bool CellsLayer::hasECMCell() const{
    return ecm!=nullptr;
}

bool CellsLayer::hasOrganCell() const{
    return organCell!=nullptr;
}

bool CellsLayer::hasBloodCell() const{
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

double CellsLayer::getECMQuantity(SubstanceId id) const{
    if (hasECMCell()){
        return ecm->getQuantitiy(id);
    } else {return 0;}
}// return 0 when there is no quantiy

double CellsLayer::getOrganCellQuantity(SubstanceId id) const{
    if (hasOrganCell()){
        return organCell->getQuantitiy(id);
    } else {return 0;}
}

double CellsLayer::getBloodCellQuantity(SubstanceId id) const{
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

bool CellsLayer::isOut(const CellCoord& coord) const{
    return organ->isOut(coord);
}

void CellsLayer::update(sf::Time dt){
    ecm->update(dt);
    if (hasBloodCell()){
        bloodCell->update(dt);
    }
    if (hasOrganCell()){
        organCell->update(dt);
        if(organCell->isDead()){
            if(organCell->hasCancer()){
                organ->decreaseCounter();
            }
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

bool CellsLayer::hasCancer() const{
    if (hasOrganCell()){
        return organCell->hasCancer();
    }
    else {return false;}
}

void CellsLayer::setCancer(){
    if (organCell != nullptr){
        if(organCell->hasCancer()){
            organ->decreaseCounter();
        }
        delete organCell;
        organCell = nullptr;
    }
    organCell = (new TumoralCell(this));
    organ->updateRepresentationAt(position);
    organ->increaseCounter();
}

Cell* CellsLayer::getECM() const{
    return ecm;
}

bool CellsLayer::requestToDivide(bool hasCancer){
    return organ->requestToDivide(position, hasCancer); //here it is possible to access the position
}
