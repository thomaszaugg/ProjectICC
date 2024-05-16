#include "OrganCell.hpp"
#include "Application.hpp"
#include "Random/Random.hpp"


OrganCell::OrganCell(CellsLayer* cellsLayer)
    : Cell(cellsLayer), atp(100)//(getAppConfig().initial_atp)
    {}
void OrganCell::update(sf::Time dt){
//1
    double atp_min = getAppConfig().base_atp_usage;
    double atp_max = atp_min + getAppConfig().range_atp_usage;
    double feedingloss =uniform(atp_min, atp_max);

 //2
    //glucose consumption virtual

 //3
       //bromopyrubve

    //4
    //ATP synthése virtual
    //5
    atp = atp *(1-exp(-getAppConfig().organ_decay_atp*dt.asSeconds())) - feedingloss;

}

bool OrganCell::isDead(){
    return atp <= 0.0;
}
