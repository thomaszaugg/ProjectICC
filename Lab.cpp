#include "Lab.hpp"
#include "Application.hpp"
#include <Utility/Utility.hpp>
#include "Hamster.hpp"
#include "Pellets.hpp"
#include "Config.hpp"
#include <algorithm>

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

    std::vector<Cage*> vCage;       //every row of cages is first stored in vCages before making a pushback on the attribut cages
    for (unsigned int i(0); i < nbCagesPerRow; ++i){
        vCage.clear();
        for (unsigned int j(0); j < nbCagesPerRow; ++j){
            Vec2d position (widthBox/2 + i*widthBox, widthBox/2 + j*widthBox);
            Cage* ptr(new Cage(position, widthBox, widthBox , 0.025*widthBox));
            vCage.push_back(ptr);
        }
        cages.push_back(vCage);
    }
}


Lab::Lab(){
    makeBoxes(getAppConfig().simulation_lab_nb_boxes);
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

//3.1
void Lab::update(sf::Time dt){
    for (auto& entity: entities){
            if(entity!=nullptr){
                entity->update(dt);
                    if(entity->isDead()){
                        /*if(entity->getTracked()){
                            entity->setTracked(false);
                            animal=nullptr;
                        }*/
                        delete entity;
                        entity = nullptr;}
            }}

    entities.erase(std::remove(entities.begin(),            //removing nullptrs only after iteration finished
                  entities.end(), nullptr), entities.end());
}

void Lab::drawOn(sf::RenderTarget& targetWindow){
    drawOnCages(targetWindow);

                // Copy of Entities in a list
          std::list<Entity*> sorted( entities.begin(), entities.end());
                // order redefined based on getDepth():
        auto comp([](Entity* a, Entity* b)->bool{ return int(a->getDepth()) < int(b->getDepth()); });
                // list sorted
        sorted.sort (comp);

    for (const auto& entity: sorted){
        if(entity!=nullptr){
            entity->drawOn(targetWindow);
        }
    }
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
    for (auto& entity: entities){
        if (entity->getTracked()){  //4.1
            entity->setTracked(false);
            animal=nullptr;
        }
        delete entity;
    }
    entities.clear();
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


bool Lab::addEntity(Entity* e){
    if (e!=nullptr and declareEntityCage(e)
       and  e->canBeConfinedIn(e->getCage())){
            e->adjustPostition();
            entities.push_back(e);
            return true;
        }
        return false;
    }

bool Lab::declareEntityCage(Entity* e){
    Vec2d center = e->getCenter();
    for (auto& row: cages){
        for (auto& ele: row){
            if(ele->isPositionInside(center) or ele->isPositionOnWall(center)){
                e->setCage(ele);
                return true;
            }
        }
}
return false;}


bool Lab::addAnimal(Hamster* h){
    if( addEntity(h)){
        h->getCage()->addOccupant();
        return true;
    }else{
        return false;}
}

bool Lab::addFood(Pellets* p){
    return addEntity(p);
}

Entity* Lab::getClosesedEatableEntity(Cage* c, Entity* const& e){

    Entities vecEntities;   //creates the vector of entites that are in the same cage and eatable for entity e
    for(auto const& entity: entities){
        if(entity->getCage()== c and entity!=e and e->canConsume(entity)) vecEntities.push_back(entity);
    }

    if(vecEntities.empty()) return nullptr;     //for the case there is no eatable entity

        unsigned int index(0);
        double MINdistance( (vecEntities[0]->getCenter()- e->getCenter()).length());
        double distance(0);
    for(unsigned int i(1); i<vecEntities.size();++i){
        distance=(vecEntities[i]->getCenter()- e->getCenter()).length();
        if(distance<MINdistance){
            MINdistance=distance;
            index=i;
        }
    }
     return vecEntities[index];}


//4.1
void Lab::trackAnimal(const Vec2d& position){
    for (auto& entity: entities){
        if (entity->isAnimal() && entity->isPointInside(position) && animal==nullptr){
            trackAnimal(dynamic_cast<Animal*>(entity));
        }
    }
}

void Lab::trackAnimal(Animal* a){
    a->setTracked(true);
    animal=a;
}

bool Lab::isAnyTrackedAnimal(){
    /*for (auto& entity: entities){
        if (entity->isAnimal() && entity->getTracked()){
            return true;
        }
    }*/
    return !(animal==nullptr);

}

void Lab::switchToView(View view){
    if (isAnyTrackedAnimal()){
        getApp().switchToView(view);
    }
}

void Lab::stopTrackingAnyEntity(){
    for (auto& entity: entities){
        if (entity->getTracked()){
            entity->setTracked(false);
        }
    }
    delete animal;;
    animal=nullptr; //desallocation
}

void Lab::updateTrackedAnimal(){

}

void Lab::drawCurrentOrgan(sf::RenderTarget& target){

}
