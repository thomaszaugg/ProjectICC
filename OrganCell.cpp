#include "OrganCell.hpp"
#include "Application.hpp"
#include "Random/Random.hpp"


OrganCell::OrganCell(CellsLayer* cellsLayer)
    : Cell(cellsLayer), atp(100)//(getAppConfig().initial_atp)
    {}
void OrganCell::update(sf::Time dt){
    naturalLoss(dt);
    uptakeSubstance();
    ATPSynthesis();
    feedingLoss();
    Division();
}

void OrganCell::naturalLoss(sf::Time dt){
    atp = atp *(1-exp(-getAppConfig().organ_decay_atp*dt.asSeconds()));
}

void OrganCell::uptakeSubstance(){

}

double OrganCell::getFractUptake(){
    return getAppConfig().organ_fract_uptake;
}

void OrganCell::ATPSynthesis(){

}

void OrganCell::feedingLoss(){
    double atp_min = getAppConfig().base_atp_usage;
    double atp_max = atp_min + getAppConfig().range_atp_usage;
    double feedingloss =uniform(atp_min, atp_max);
    atp = atp - feedingloss;
}

bool OrganCell::isDead(){
    return atp <= 0.0;
}

void OrganCell::Division(){

}

void OrganCell::canDivide(){

}

bool OrganCell::hasCancer(){
    return false;
}
