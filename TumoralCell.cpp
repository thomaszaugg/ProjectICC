#include "TumoralCell.hpp"
#include "Application.hpp"

TumoralCell::TumoralCell(CellsLayer* cellsLayer)
    : OrganCell(cellsLayer){}



double TumoralCell::getFractUptake(){
    return getAppConfig().cancer_fract_uptake;
}

void TumoralCell::ATPSynthesis(sf::Time dt){
    glycolysis(dt);
}
void TumoralCell::Division(){

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
