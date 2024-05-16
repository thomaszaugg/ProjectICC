#include "TumoralCell.hpp"
#include "Application.hpp"

TumoralCell::TumoralCell(CellsLayer* cellsLayer)
    : OrganCell(cellsLayer){}

void TumoralCell::uptakeSubstance(){

}

double TumoralCell::getFractUptake(){
    return getAppConfig().cancer_fract_uptake;
}

void TumoralCell::ATPSynthesis(){

}

void TumoralCell::Division(){

}

bool TumoralCell::hasCancer(){
    return true;
}
