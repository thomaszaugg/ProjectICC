#include "TumoralCell.hpp"
#include "Application.hpp"

TumoralCell::TumoralCell(CellsLayer* cellsLayer)
    : OrganCell(cellsLayer){}

 void TumoralCell::ATPSynthesis(sf::Time dt){
     glycolysis(dt);}





double TumoralCell::getFractUptake() const{
    return getAppConfig().cancer_fract_uptake;
}

bool TumoralCell::hasCancer(){
    return true;
}

double TumoralCell::getKrebsKm() const{
    return getAppConfig().cancer_km_glycolysis;
}

double TumoralCell::getKrebsVmax() const{
    return getAppConfig().cancer_km_max_glycolysis;
}

double TumoralCell::getFractGlu() const {
    return getAppConfig().cancer_glucose_usage;
}
 double TumoralCell::getDivisonEnergy() const {
    return getAppConfig().cancer_division_energy;
}

double TumoralCell::getMinNbCycles()const{
    return getAppConfig().cancer_time_next_division;
}

double TumoralCell::getNbCyclesRange()const{
    return getAppConfig().cancer_range_next_division ;
}
