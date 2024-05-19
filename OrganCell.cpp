#include "OrganCell.hpp"
#include "Application.hpp"
#include "Random/Random.hpp"


OrganCell::OrganCell(CellsLayer* cellsLayer)
    : Cell(cellsLayer), atp(100)//(getAppConfig().initial_atp)
    {}
void OrganCell::update(sf::Time dt){
    naturalLoss(dt);
    uptakeFromECM();
    ATPSynthesis(dt);
    feedingLoss();
    Division();
}

void OrganCell::naturalLoss(sf::Time dt){
    atp = atp *(1-exp(-getAppConfig().organ_decay_atp*dt.asSeconds()));
}

void OrganCell::uptakeFromECM(){
    double fractUptake=getFractUptake();
    Cell* ecm=getECM();
    takeSubstance(fractUptake,ecm, GLUCOSE);
    takeSubstance(fractUptake,ecm, BROMOPYRUVATE);
}

double OrganCell::getFractUptake(){
    return getAppConfig().organ_fract_uptake;
}

void OrganCell::ATPSynthesis(sf::Time dt){

    //Glycolysis
        glycolysis(dt);
    //KrebsCycle
        ATP(dt,0.8);    //0.8 = KrebsGlucoseUptake getAppConfig
        }
void OrganCell::glycolysis(sf::Time dt){
        double factor_inhibition=(1+ getQuantitiy(BROMOPYRUVATE)/0.6); //0.6=Ki move to getAppConfig()

        ATP(dt,getFractGlu(),factor_inhibition);

            //only organ cells or both?
        multiplySubstance(BROMOPYRUVATE,0.6); //0.6 = lossOfInhibiorFactor move to getAppConfig()

}

double OrganCell::getKrebsKm() const{
    return getAppConfig().organ_km_glycolysis;}
double OrganCell::getKrebsVmax() const{
    return getAppConfig().organ_km_max_glycolysis;
}
void OrganCell::ATP(sf::Time dt, double factor_glucoseUptake, double factor_inhibition){
    double S=getQuantitiy(GLUCOSE)*factor_glucoseUptake;
   multiplySubstance(GLUCOSE,factor_glucoseUptake);

   double dP=((getKrebsVmax()*S)/(S+(getKrebsKm()*factor_inhibition)))*dt.asSeconds();
   atp+=dP;

}
double OrganCell::getFractGlu() const{
        return getAppConfig().organ_glucose_usage;
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


