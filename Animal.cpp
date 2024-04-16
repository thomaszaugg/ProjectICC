#include "Animal.hpp"
#include "Cage.hpp"
#include "Application.hpp"
#include "Random/Random.hpp"

//where to put them???
Intervals intervals = { -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
std::vector<double> probabilities = {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};


Animal::Animal(const Vec2d& position, double energy)
    : Entity(position, energy){
    }

Animal::~Animal() {
    if(getCage()!=nullptr) getCage()->reset();}

bool Animal::isAnimal() {
    return true;
}

bool Animal::canBeConfinedIn(Cage* cage){
     return cage->isEmpty() and cage->isPositionInside(getCenter());
}

bool Animal::update(sf::Time dt){
    updateEnergy(dt);       //has to come before increaseAge for correct functioning in lab(return value)
    updateState(dt);
    move(dt);
    return Entity::update(dt);
    }

void Animal::updateState(sf::Time dt){
    speed= this->getMaxSpeed();

}

void Animal::move(sf::Time dt){
    counter+=dt;
    if(counter > sf::seconds(getAppConfig().animal_rotation_delay)){    //since seconds are floats, we use comparison instead of egality
        setOrientation(getOrientation()+getNewRotation());
    }

    Vec2d step=getSpeedVector()*dt.asSeconds();
    if(inCollision(step+getCenter())){
        setOrientation((-getHeading()).angle());
    }

}


Vec2d Animal::getSpeedVector(){
    return getHeading()*speed;
}


Angle Animal::getNewRotation(){

    return piecewise_linear(intervals, probabilities)*DEG_TO_RAD;   //piecewise_linear works with degrees
}

void Animal::updateEnergy(sf::Time dt){
double energy_loss = getAppConfig().animal_base_energy_consumption + speed * getEnergyLoss() * dt.asSeconds();
setEnergy(this->getEnergy()- energy_loss);
}








 /*  switch (state) {
       case TARGETING_FOOD :

           break;
       case FEEDING:

           break;

       case WANDERING:

           break;
       case IDLE:

           break;
       }
}*/







