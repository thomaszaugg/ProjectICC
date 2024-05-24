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
    : Entity(position, energy), speed(0), organ(new Organ()){
    }

Animal::~Animal() {
    if(getCage()!=nullptr) getCage()->reset();
    delete organ;
}

bool Animal::isAnimal() const {
    return true;
}

bool Animal::canBeConfinedIn(Cage* cage) const{
    return cage->isEmpty() and cage->isPositionInside(getCenter());
}

void Animal::update(sf::Time dt){

    updateEnergy(dt);   //the animal loses by default energy

    Entity* food(getAppEnv().getClosesedEatableEntity(getCage(), this));   //gets the closest food entity
    updateState( dt, food); //updates the state so the correct action is taken

    switch (state){
       case TARGETING_FOOD :{   //animal moves to food
            Vec2d force=calculateForce(food);
            move(force, dt, false);
           break;}

       case FEEDING:{       //animal decelerates to food
            Vec2d force=calculateForce(food, getDeceleration());    //the Deceleration will make sure the animal
            move(force*getDeceleration(), dt, true);                //doesn't walk over his food
            eatFood(food);
           break;}

       case WANDERING:{     //animal moves arbitrarily
            move(dt);
           break;}
       case IDLE:{          //animal sits still
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
            if(bernoulli(0.005)) {   //if the hamster is wandering, there is a small chance
               state=IDLE;          // that the animal will stay idle for a while
               counter=sf::Time::Zero;
            }

}}

void Animal::move(sf::Time dt){     //Wandering
    changeOrientation(dt);          //happens when counter is high enough

    //change of position
    Vec2d step=getSpeedVector()*dt.asSeconds();
        if(inCollision(step+getCenter())){
            setOrientation((-DEG_TO_RAD*getHeading()).angle());
        }
    takeStep(step);
}

void Animal::changeOrientation(sf::Time dt){
    counter+=dt;
    if(counter >= sf::seconds(getAppConfig().animal_rotation_delay)){    //since seconds are floats, we use comparison instead of egality
        setOrientation(getOrientation()+getNewRotation());               //orientation can become negatif
        counter =sf::Time::Zero;
    }
}

Vec2d Animal::getSpeedVector() const{
    return getHeading()*speed;
}

Angle Animal::getNewRotation() const{
    return piecewise_linear(intervals, probabilities)*DEG_TO_RAD;   //piecewise_linear works with degrees
}

void Animal::updateEnergy(sf::Time dt){ //animal loses energy according to base consumption and its speed
    double energy_loss = getAppConfig().animal_base_energy_consumption + speed * getEnergyLoss() * dt.asSeconds();
    setEnergy(this->getEnergy()- energy_loss);
    Entity::update(dt);           //energy is an attribute of superclass entity
    speed= this->getAdjustedMaxSpeed(); //speed depends on energy
}

double Animal::getFatigueFactor() const{return 0.25;} //move to json

double Animal::getAdjustedMaxSpeed(){
    speed=getMaxSpeed();
    if(getEnergy()< getFatigueEnergy()) speed*= getFatigueFactor(); //adjust speed
    return speed;
}

void Animal::move(const Vec2d& force, sf::Time dt, bool feeding){     //TARGETING and FEEDING
    if(feeding){        //additional checking to allow smooth slowing down
        if(force.length()>70){        //so the animal stops before shooting the object
            setOrientation(force.angle());
            takeStep(force*dt.asSeconds());
        }
    }else{
        Vec2d acceleration = force / getMass(); //calculate acceleration
        setOrientation(force.angle());          //sets the right orientation
        Vec2d speedVector = getSpeedVector() + acceleration * dt.asSeconds();  //calculates speedVector
        if(speedVector.length()>getAdjustedMaxSpeed()){     //adjusts the speedVector to the possible values
            speedVector=getHeading()*getAdjustedMaxSpeed();
        }
        takeStep( speedVector * dt.asSeconds());        //takes the step
    }
}

bool Animal::isHungry() const{
    if(state==FEEDING){
        return getEnergy()<getAppConfig().animal_satiety_max;
    }else{
        return getEnergy()<getAppConfig().animal_satiety_min;
    }
}

Vec2d Animal::calculateForce(Entity* food, double deceleration) {
    Vec2d to_target(food->getCenter()- this->getCenter());

    double speed = std::min(to_target.length()/deceleration, getAdjustedMaxSpeed());
    Vec2d v_wish= to_target.normalised()*speed; //normalised (length=1), not normal(orthogonal)!

    return v_wish ;
}

void Animal::eatFood(Entity* food){ //can only partially absorb the eaten foods energy
   if(this->canConsume(food)) setEnergy((getEnergy()+getAppConfig().animal_meal_retention*food->provideEnergy(getEnergyBite())));
}

void Animal::drawDebug(sf::RenderTarget& target) const{
        //draws the energy
    Entity::drawDebug(target);
        //draws the state
    auto text = buildText(getStateString(),
                getCenter()+ Vec2d(-120,-120),  //displaced for better optics
                getAppFont(),
                getAppConfig().default_debug_text_size*2.5,
                sf::Color::Blue,
                0 / DEG_TO_RAD); // to rotate the text
    target.draw(text);

        //draws the circularBody
    CircularBody::drawOn(target);
}

std::string Animal::getStateString() const{

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

DrawingPriority Animal::getDepth() const{
    return DrawingPriority::ANIMAL_PRIORITY;
}

void Animal::updateOrgan(){
    if(organ!=nullptr){
        organ->update();
    }
}
void Animal::drawOrgan(sf::RenderTarget& target) const{
    if(organ!=nullptr){
        organ->drawOn(target);
    }
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

double Animal::getDelta(SubstanceId id) const{
    return organ->getDelta(id);
}

SubstanceId Animal::getCurrentSubst() const{
    return organ->getCurrentSubst();
}

void Animal::setCancerAt(const Vec2d& pos){
    return organ->setCancerAt(pos);
}
