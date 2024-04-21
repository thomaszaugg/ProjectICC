#include "Animal.hpp"
#include "Cage.hpp"
#include "Application.hpp"
#include "Random/Random.hpp"
#include "Utility/Utility.hpp"


//used for the random orientation change
Intervals intervals = { -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
std::vector<double> probabilities = {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};

Animal::Animal(const Vec2d& position, double energy)
    : Entity(position, energy), speed(0){
    }

Animal::~Animal() {
    if(getCage()!=nullptr) getCage()->reset();
}

bool Animal::isAnimal() {
    return true;
}

bool Animal::canBeConfinedIn(Cage* cage){
    return cage->isEmpty() and cage->isPositionInside(getCenter());
}

void Animal::update(sf::Time dt){
 updateEnergy(dt);


    Entity* food(getAppEnv().getClosesedEatableEntity(getCage(), this));
     updateState( food);

    switch (state) {
       case TARGETING_FOOD :{
            Vec2d force=calculateForce(food);
            move(force, dt);
           break;}

       case FEEDING:{
            Vec2d force=calculateForce(food, getDeceleration());
            move(force, dt);
           break;}

       case WANDERING:{
        move(dt);
           break;}
       case IDLE:{;}

           break;
       }

}

void Animal::updateState( Entity* food){
    if(isHungry() and food!=nullptr){
        state=TARGETING_FOOD;
        if(this->isColliding(*food)){
            state=FEEDING;
        }
 } else{
        state=WANDERING;}

}



void Animal::move(sf::Time dt){     //Wandering

  changeOrientation(dt);        //happens when counter is high enough

  //change of position
    Vec2d step=getSpeedVector()*dt.asSeconds();
        if(inCollision(step+getCenter())){
            setOrientation((-getHeading()).angle());
        }
    updatePosition(step);
}

void Animal::changeOrientation(sf::Time dt){
  counter+=dt;
  if(counter >= sf::seconds(getAppConfig().animal_rotation_delay)){    //since seconds are floats, we use comparison instead of egality
      setOrientation(getOrientation()+getNewRotation());             //orientation can become negatif
      counter =sf::Time::Zero;
  }}

Vec2d Animal::getSpeedVector(){
    return getHeading()*speed;
}

Angle Animal::getNewRotation(){
    return piecewise_linear(intervals, probabilities)*DEG_TO_RAD;   //piecewise_linear works with degrees
}

void Animal::updateEnergy(sf::Time dt){
    double energy_loss = getAppConfig().animal_base_energy_consumption + speed * getEnergyLoss() * dt.asSeconds();
    setEnergy(this->getEnergy()- energy_loss);
    Entity::update(dt);
    speed= this->getAdjustedMaxSpeed();
}

double Animal::getFatigueFactor(){return 0.25;}

double Animal::getAdjustedMaxSpeed(){
    speed=getMaxSpeed();
    if(getEnergy()< getFatigueEnergy()) speed*= getFatigueFactor(); //adjust speed
    return speed;
}

void Animal::move(const Vec2d& force, sf::Time dt){     //TARGETING and FEEDING
     Vec2d acceleration = force / getMass();
    Vec2d speedVector = getSpeedVector() - acceleration * dt.asSeconds();
    setOrientation( speedVector.angle());
    if(speedVector.length()>getAdjustedMaxSpeed()){
        speedVector=getHeading()*getAdjustedMaxSpeed();
    }
    updatePosition( speedVector * dt.asSeconds());

}

bool Animal::isHungry(){
    if(state==FEEDING){
        return getEnergy()<getAppConfig().animal_satiety_max;
    } else{
        return getEnergy()<getAppConfig().animal_satiety_min;
    }
}

Vec2d Animal::calculateForce(Entity* food, double deceleration){
    Vec2d to_target(food->getCenter()- this->getCenter());
    if(to_target.length()==0){
         return to_target;}
     double speed = std::min(to_target.length()/deceleration, getAdjustedMaxSpeed());
    Vec2d v_wish= to_target.normal()*speed;
   return v_wish - getSpeedVector();}








