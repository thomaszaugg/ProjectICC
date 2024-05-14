#include "Animal.hpp"
#include "Cage.hpp"
#include "Application.hpp"
#include "Random/Random.hpp"
#include "Utility/Utility.hpp"
#include "Pellets.hpp"
#include "Random/Random.hpp"

//used for the random orientation change
Intervals intervals = { -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
std::vector<double> probabilities = {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};

Animal::Animal(const Vec2d& position, double energy)
    : Entity(position, energy), speed(0), organ(new Organ()){ //does every animal have an organ?
    }

Animal::~Animal() {
    if(getCage()!=nullptr) getCage()->reset();
    delete organ;
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
    updateState( dt, food);

    switch (state){
       case TARGETING_FOOD :{
            Vec2d force=calculateForce(food);
            move(force, dt, false);
           break;}

       case FEEDING:{
            Vec2d force=calculateForce(food, getDeceleration());
            move(force*getDeceleration(), dt, true);
            eatFood(food);
           break;}

       case WANDERING:{
        move(dt);
           break;}
       case IDLE:{

           break;}
    }
}

void Animal::updateState(sf::Time dt, Entity* food){
    if(state==IDLE and counter < sf::seconds(getAppConfig().animal_rotation_delay*3 )){
            counter+=dt;
    }else if(isHungry() and food!=nullptr){
        state=TARGETING_FOOD;
        if(this->isColliding(*food)){
            state=FEEDING;
        }
    }else{
        state=WANDERING;
       if(bernoulli(0.005)) {
           state=IDLE;
           counter=sf::Time::Zero;
       }
    }
}

void Animal::move(sf::Time dt){     //Wandering
    changeOrientation(dt);        //happens when counter is high enough

  //change of position
    Vec2d step=getSpeedVector()*dt.asSeconds();
        if(inCollision(step+getCenter())){
            setOrientation((-getHeading()).angle());
        }
    takeStep(step);
}

void Animal::changeOrientation(sf::Time dt){
    counter+=dt;
    if(counter >= sf::seconds(getAppConfig().animal_rotation_delay)){    //since seconds are floats, we use comparison instead of egality
        setOrientation(getOrientation()+getNewRotation());             //orientation can become negatif
        counter =sf::Time::Zero;
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
    Entity::update(dt);
    speed= this->getAdjustedMaxSpeed();
}

double Animal::getFatigueFactor(){return 0.25;}

double Animal::getAdjustedMaxSpeed(){
    speed=getMaxSpeed();
    if(getEnergy()< getFatigueEnergy()) speed*= getFatigueFactor(); //adjust speed
    return speed;
}

void Animal::move(const Vec2d& force, sf::Time dt, bool feeding){     //TARGETING and FEEDING
    if(feeding){
        if(force.length()>0.5){
            setOrientation(force.angle());
            takeStep(force*dt.asSeconds());
        }
    }else{
        Vec2d acceleration = force / getMass();
        setOrientation(force.angle());
        Vec2d speedVector = getSpeedVector() + acceleration * dt.asSeconds();
        if(speedVector.length()>getAdjustedMaxSpeed()){
            speedVector=getHeading()*getAdjustedMaxSpeed();
        }
        takeStep( speedVector * dt.asSeconds());
    }
}

bool Animal::isHungry(){
    if(state==FEEDING){
        return getEnergy()<getAppConfig().animal_satiety_max;
    }else{
        return getEnergy()<getAppConfig().animal_satiety_min;
    }
}

Vec2d Animal::calculateForce(Entity* food, double deceleration){
    Vec2d to_target(food->getCenter()- this->getCenter());

    if(to_target.length()<70) return to_target*0.;

    double speed = std::min(to_target.length()/deceleration, getAdjustedMaxSpeed());
    Vec2d v_wish= to_target.normalised()*speed;
    return v_wish ;//- getSpeedVector();
}

void Animal::eatFood(Entity* food){
   if(this->canConsume(food)) setEnergy((getEnergy()+getAppConfig().animal_meal_retention*food->provideEnergy(getEnergyBite())));
}

void Animal::drawDebug(sf::RenderTarget& target) {
    Entity::drawDebug(target);

    Vec2d pos(-120,-120);

    auto text = buildText(getStateString(),
                getCenter()+pos,
                getAppFont(),
                getAppConfig().default_debug_text_size*2.5,   //why so small
                sf::Color::Blue,
                0 / DEG_TO_RAD); // if you want to rotate the text
    target.draw(text);
    CircularBody::drawOn(target);
}

std::string Animal::getStateString(){

    switch (state) {
       case TARGETING_FOOD :{
            return "TARGETING_FOOD";
       break;}

       case FEEDING:{
            return "FEEDING";
           break;}

       case WANDERING:{
            return "WANDERING";
           break;}
       case IDLE:{
            return "IDLE";
           break;}
    default:{
    return "";}
    }
}

DrawingPriority Animal::getDepth(){
    return DrawingPriority::ANIMAL_PRIORITY;
}

void Animal::updateOrgan(){
    if(organ!=nullptr){
        organ->update();
    }
}
void Animal::drawOrgan(sf::RenderTarget& target){
    if(organ!=nullptr){
        organ->drawOn(target);
    }
}

void Animal::initializeOrgan(){
    organ=(new Organ(true));
}

void Animal::deleteOrgan(){
    delete organ;
    organ=nullptr;
}


void Animal::transplant(Organ* o){
    delete organ;
    organ = o;
}


void Animal::nextSubstance(){
   organ->nextSubstance();
}

void Animal::increaseCurrentSubst(){
    organ->changeDeltaSubstance(false);
}
void Animal::decreaseCurrentSubst(){
    organ->changeDeltaSubstance(true);
}

double Animal::getDelta(SubstanceId id){
   return organ->getDelta(id);
}
SubstanceId Animal::getCurrentSubst(){
    return organ->getCurrentSubst();
}
