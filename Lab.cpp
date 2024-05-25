#include "Lab.hpp"
#include "Application.hpp"
#include <Utility/Utility.hpp>
#include "Hamster.hpp"
#include "Pellets.hpp"
#include "Config.hpp"
#include "Icon.hpp"
#include <algorithm>
#include "Cheese.hpp"

unsigned int Lab::maxCageNumber(){
    double min_size(getAppConfig().simulation_lab_min_box_size);
    min_size = std::min(min_size, 2*getAppConfig().hamster_size ); //makes sure the cage is big enough for the hamster

     int maxNumber(getAppConfig().simulation_lab_size/min_size);
    return std::max(maxNumber, 1); //makes sure there is at least one cage
}

void Lab::CageNumberCheck(unsigned int& nbCagesPerRow){
     nbCagesPerRow= std::min( nbCagesPerRow, maxCageNumber());  //makes sure its within the bounds

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


Lab::Lab()
{
    makeBoxes(getAppConfig().simulation_lab_nb_boxes);
    animal=nullptr;
}

unsigned int Lab::getNbCagesPerRow() const{
    return cages.size();
}


void Lab::changeNumberOfCages(int i){
    unsigned int newNumber(cages.size()+i);
    CageNumberCheck(newNumber);

    clearCages();
    makeBoxes(newNumber);

}
void Lab::addCageToRow(){
    changeNumberOfCages(1);
}

void Lab::removeCageFromRow(){
    changeNumberOfCages(-1);

}


void Lab::update(sf::Time dt){
    for (auto& entity: entities){   //itterate through all the entities
        if(entity!=nullptr){
            entity->update(dt);
                if(entity->isDead()){   //if its dead, delete it
                    if(entity==animal)animal=nullptr;   //check the animal attribute
                    delete entity;
                    entity = nullptr;}
        }
    }
    entities.erase(std::remove(entities.begin(),       //removing nullptrs only after iteration finished
                               entities.end(), nullptr), entities.end());
}


void Lab::drawOn(sf::RenderTarget& targetWindow) const{

        drawOnCages(targetWindow);
        drawOnEntities(targetWindow);

    }

void Lab::drawOnCages(sf::RenderTarget& targetWindow) const{
    for (auto& row: cages){
        for (auto& ele: row){
            (*ele).drawOn(targetWindow);
        }
    }
}
void Lab::drawOnEntities(sf::RenderTarget& targetWindow) const{
        // Copy of Entities in a list
    std::list<Entity*> sorted( entities.begin(), entities.end());

        // order redefined based on getDepth():
    auto comp([](Entity* a, Entity* b)->bool{ return int(a->getDepth()) < int(b->getDepth()); });

        // list sorted
    sorted.sort (comp);

        //draw the new list
    for (const auto& entity: sorted){
        if(entity!=nullptr){
            entity->drawOn(targetWindow);
        }
    }

    if(animal!=nullptr) drawTracker(targetWindow);  //draws tracker if an animal is tracked
}

void Lab::reset(bool reset){
    if(isDebugOn()) getAppConfig().switchDebug();
    if (reset){
        clearCages();
        makeBoxes(getAppConfig().simulation_lab_nb_boxes);  //starts from default settings
    }else{
        clearEntities();
    }
}

void Lab::clearEntities(){
    for (auto& entity: entities){
        delete entity;
    }
    entities.clear();
    animal=nullptr;
}

void Lab::clearCages(){
    clearEntities();
    for (unsigned int i(0); i < cages.size(); ++i){
        for (unsigned int j(0); j < cages.size(); ++j){
            delete cages[i][j]; //since the vector is cleared, nullptr assignment not necessary
        }
        cages[i].clear();
    }
    cages.clear();
}

Lab::~Lab(){
    clearCages();
}

bool Lab::addEntity(Entity* e){
    if (e!=nullptr and declareEntityCage(e) //first checks in which case and then if it can go into the cage
        and  e->canBeConfinedIn(e->getCage())){
            e->adjustPostition();   //so animal isn't on the walls
            entities.push_back(e);
            return true;
    }
    return false;
}

bool Lab::declareEntityCage(Entity* e){
    Vec2d center = e->getCenter();
    for (auto& row: cages){         //itterates through the cages to check in which cage the animal belongs
        for (auto& ele: row){
            if(ele->isPositionInside(center) or ele->isPositionOnWall(center)){
                e->setCage(ele);        //sets the cage for the entity
                return true;
            }
        }
    }
    return false;
}

bool Lab::addAnimal(Hamster* h){
    if(addEntity(h)){
        h->getCage()->addOccupant();
        return true;
    }else{
        return false;}
}

bool Lab::addFood(Pellets* p){
    return addEntity(p);
}

bool Lab::addCheese(Cheese* c){
    return addEntity(c);
}

Entity* Lab::getClosesedEatableEntity(Cage* c, Entity* const& e) const{

    Entities vecEntities;   //creates the vector of entites that are in the same cage and eatable for entity e
    for(auto const& entity: entities){
        if(entity!=nullptr and entity->getCage()== c and entity!=e and e->canConsume(entity)) vecEntities.push_back(entity);
    }

    if(vecEntities.empty()) return nullptr;     //for the case where there is no eatable entity

        unsigned int index(0);                  //searches the closest (of all the ones that are eatable and in the same cage
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


void Lab::trackAnimal(const Vec2d& position){
    for (auto& entity: entities){
        if (entity->isAnimal() && entity->isPointInside(position) && animal==nullptr){
            trackAnimal(dynamic_cast<Animal*>(entity));
        }
    }
}

void Lab::trackAnimal(Animal* a){
    animal=a;
}

bool Lab::isAnyTrackedAnimal() const{
    return animal != nullptr;
}

void Lab::switchToView(View view){
    if (isAnyTrackedAnimal()){
        getApp().switchToView(view);
    }
}

void Lab::stopTrackingAnyEntity(){
   animal=nullptr;
}

void Lab::drawTracker(sf::RenderTarget& target) const{
    if(animal!=nullptr) {
        Vec2d  a= animal->getSpeedVector().normalised();      //better placement of icon
        Icon icon(animal->getCenter()+ (a+a.normal())*(-55), animal->getOrientation());
        icon.drawOn(target);
    }
}

void Lab::updateTrackedAnimal(){
    if(animal!=nullptr) animal->updateOrgan();
}

void Lab::drawCurrentOrgan(sf::RenderTarget& target) const{
    if(animal!=nullptr){
        animal->drawOrgan(target);
    }
}

void Lab::nextSubstance(){
    if(isAnyTrackedAnimal()) animal->nextSubstance();
}

void Lab::increaseCurrentSubst(){
    if(isAnyTrackedAnimal()) animal->increaseCurrentSubst();
}

void Lab::decreaseCurrentSubst(){
    if(isAnyTrackedAnimal()) animal->decreaseCurrentSubst();
}

double Lab::getDelta(SubstanceId id) const{
    double delta(0);
    if(isAnyTrackedAnimal()) delta=animal->getDelta(id);
    return delta;
}

SubstanceId Lab::getCurrentSubst() const{
    if(animal!=nullptr) return animal->getCurrentSubst();
    return GLUCOSE;
}

void Lab::setCancerAt(const Vec2d& pos){
    if(isAnyTrackedAnimal()) animal->setCancerAt(pos);
}
