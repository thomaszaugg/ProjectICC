#include "OrganCell.hpp"
#include "Application.hpp"
#include "Random/Random.hpp"


OrganCell::OrganCell(CellsLayer* cellsLayer)
    : Cell(cellsLayer), atp(100), N(100), counter(0)//(getAppConfig().initial_atp)
    {}

void OrganCell::update(sf::Time dt){
    ++counter;
    naturalLoss(dt);
    uptakeFromECM();
    ATPSynthesis(dt);
    feedingLoss();
    Division();
}

void OrganCell::naturalLoss(sf::Time dt){
    atp *=(1-exp(-getAppConfig().organ_decay_atp*dt.asSeconds()));
}

void OrganCell::uptakeFromECM(){
    double fractUptake=getFractUptake();
    Cell* ecm=getECM();     //using this getters allows us to make use of uptake substance function
    takeSubstance(fractUptake,ecm, GLUCOSE);
    takeSubstance(fractUptake,ecm, BROMOPYRUVATE);
}

double OrganCell::getFractUptake() const{
    return getAppConfig().organ_fract_uptake;
}

void OrganCell::ATPSynthesis(sf::Time dt){
    //Glycolysis
        glycolysis(dt);
    //KrebsCycle
       pathway_atp_production(dt, getKrebsKm(), getKrebsVmax(), 0.8);    //0.8 = KrebsGlucoseUptake getAppConfig
        }

void OrganCell::glycolysis(sf::Time dt){
    double factor_inhibition=(getQuantitiy(BROMOPYRUVATE)/0.6); //0.6=Ki move to getAppConfig()
    ++factor_inhibition;
    pathway_atp_production(dt, getGlycolysisKm(), getGlycolysisVmax(), getFractGlu(), factor_inhibition);

    // both organ and tumor
    multiplySubstance(BROMOPYRUVATE,0.6); //0.6 = lossOfInhibiorFactor move to getAppConfig()
}

void OrganCell::pathway_atp_production(sf::Time dt, double Km, double Vmax, double factor_glucoseUptake, double factor_inhibition){
    double S=getQuantitiy(GLUCOSE)*factor_glucoseUptake;
    multiplySubstance(GLUCOSE,factor_glucoseUptake);
    double dP=((Vmax*S)/(S+(Km*factor_inhibition)))*dt.asSeconds();
    atp+=dP;
}

double OrganCell::getGlycolysisKm() const{
    return getAppConfig().organ_km_glycolysis;}

double OrganCell::getGlycolysisVmax() const{
    return getAppConfig().organ_km_max_glycolysis;
}

double OrganCell::getKrebsKm()const{
    return getAppConfig().organ_km_krebs;
}

double OrganCell::getKrebsVmax()const{
    return getAppConfig().organ_km_max_krebs;
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
    if(atp>=getDivisonEnergy() and counter>N){
        if(requestToDivide(hasCancer())){
            atp-=getAppConfig().organ_division_cost;    //the same for organ and tumor cells
            counter=0;
            N = uniform(getMinNbCycles(), getMinNbCycles() + getNbCyclesRange());
        }
    }
}

double OrganCell::getMinNbCycles()const{
    return getAppConfig().organ_time_next_division;
}

double OrganCell::getNbCyclesRange()const{
    return getAppConfig().organ_range_next_division;
}

double OrganCell::getDivisonEnergy() const{
    return getAppConfig().organ_division_energy;
}

bool OrganCell::hasCancer(){
    return false;
}


