#include "OrganCell.hpp"
#include "Application.hpp"
#include "Random/Random.hpp"


OrganCell::OrganCell(CellsLayer* cellsLayer)
    : Cell(cellsLayer), atp(100), N(0), counter(0)//(getAppConfig().initial_atp)
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
    if(atp>=getDivisonEnergy() and counter>N){

        if(requestToDivide(hasCancer())){
        atp-=getAppConfig().organ_division_cost;    //the same for organ and tumor cells
        counter=0;
        N = uniform(getMinNbCycles(), getMinNbCycles() + getNbCyclesRange());
        }

}}


    double OrganCell::getMinNbCycles()const{
   return getAppConfig().organ_time_next_division;
}

    double OrganCell::getNbCyclesRange()const{
       return     getAppConfig().organ_range_next_division;
    }

double OrganCell::getDivisonEnergy() const{
return getAppConfig().organ_division_energy;
}

bool OrganCell::hasCancer(){
    return false;
}

/*  i ha kes internet drum spicheri d antwort zur frag hie:
 *
 *  copy to divison method!
 *
 *  [Question 6.6] What method(s) do you introduce and in which class(es) to implement cell division of the organ fragment (always avoiding introducing overly intrusive getters like getOrgan or getCellsLayers) ? Answer this question in your REPONSES file, justifying your choices and completing the code accordingly.
    We coded the method division that handles divison for both organ and tumor cells using polymorphic getters
    If a cell is ready to divide, it sends a request to divide using the requestToDivide(bool hasCancer) method
    that is passed up to Cell, then CellsLayer and finally Organ where the neccessary checks are made
    If there is a free position, the organ sets a new cell and returns a bool (back through the cascade)
    the cell thereby knows if it has diveded and then resets the counter and substracts the energy

  */

