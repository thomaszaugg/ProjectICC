#include "Lab.hpp"
#include "Application.hpp"
#include <Utility/Utility.hpp>
#include "Hamster.hpp"
#include "Pellets.hpp"
#include "Config.hpp"

unsigned int Lab::maxCageNumber(){
    double min_size(getAppConfig().simulation_lab_min_box_size);
    if(min_size < 2*getAppConfig().hamster_size) {
        min_size=2*getAppConfig().hamster_size;
    }
    unsigned int maxNumber(getAppConfig().simulation_lab_size/min_size);
    if (maxNumber < 1){
        maxNumber=1;
    }

    return maxNumber;
}

void Lab::CageNumberCheck(unsigned int& nbCagesPerRow){
    if(maxCageNumber() < nbCagesPerRow){
        nbCagesPerRow=maxCageNumber();
    }
    if(nbCagesPerRow==0){
        throw std::invalid_argument("Zero Cages not possible");
    }
}

void Lab::makeBoxes(unsigned int nbCagesPerRow){
    cages.clear();
    CageNumberCheck(nbCagesPerRow);
    double widthBox(getAppConfig().simulation_lab_size/nbCagesPerRow);
    std::vector<Cage*> vCage;
    for (unsigned int i(0); i < nbCagesPerRow; ++i){
        vCage.clear();
        for (unsigned int j(0); j < nbCagesPerRow; ++j){     //assumption: empty vector
            Vec2d position (widthBox/2 + i*widthBox, widthBox/2 + j*widthBox);
            Cage* ptr(new Cage(position, widthBox, widthBox , 0.025*widthBox));
            vCage.push_back(ptr);
        }
        cages.push_back(vCage);
    }
}


Lab::Lab(){
    makeBoxes(getAppConfig().simulation_lab_nb_boxes); //does the argument has to be in the constructer
}

unsigned int Lab::getNbCagesPerRow(){
    return cages.size();
}


void Lab::addCageToRow(){
    unsigned int newNumber(cages.size()+1);
    CageNumberCheck(newNumber);

    clearCages();
    makeBoxes(newNumber);

}

void Lab::removeCageFromRow(){
    unsigned int newNumber(cages.size()-1);
    CageNumberCheck(newNumber);

    clearCages();
    makeBoxes(newNumber);

}

void Lab::update(sf::Time dt){
    if(hamster!=nullptr) {
        if(hamster->increaseAge(dt)){
        delete hamster;
        hamster=nullptr;
        }
    if(pellet!=nullptr) {
        if(pellet->increaseAge(dt)){
            delete pellet;
            pellet = nullptr;
        }
    }


}}

void Lab::drawOn(sf::RenderTarget& targetWindow){
    drawOnCages(targetWindow);

    if(hamster!=nullptr) hamster->drawOn(targetWindow);
    if(pellet!=nullptr) pellet->drawOn(targetWindow);
}

void Lab::drawOnCages(sf::RenderTarget& targetWindow){

    for (auto& row: cages){
        for (auto& ele: row){
            (*ele).drawOn(targetWindow);
        }
    }
}

void Lab::reset(bool reset){
    if(isDebugOn()) getAppConfig().switchDebug();
    if (reset){
        clearCages();
        makeBoxes(getAppConfig().simulation_lab_nb_boxes);
    }else{
     clearEntities();
    }
}

void Lab::clearEntities(){
    delete hamster;
    hamster=nullptr;

    delete pellet;
    pellet=nullptr;
}
void Lab::clearCages(){
    clearEntities();
    for (unsigned int i(0); i < cages.size(); ++i){
        for (unsigned int j(0); j < cages.size(); ++j){
            delete cages[i][j];
        }
        cages[i].clear();
    }
    cages.clear();
}

Lab::~Lab(){
    clearCages();
};

bool Lab::addAnimal(Hamster* h){
     if(h!=nullptr and hamster==nullptr){
         hamster=h;
         return true;}

         return false;
 }

 bool Lab::addFood(Pellets* p){
 if(pellet==nullptr and p!=nullptr){
     pellet=p;
     return true;}
 return false;
 }
