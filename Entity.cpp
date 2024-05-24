#include "Entity.hpp"
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>
#include "Cage.hpp"
#include "Application.hpp"
#include "Hamster.hpp"
#include "Pellets.hpp"



Entity::Entity(const Vec2d& position, double energy)
    : position(position), age(sf::Time::Zero), energy(energy), cage(nullptr){
    orientation = uniform(0.0, TAU);
}
//getter Block
Vec2d Entity::getCenter() const {return position;}
sf::Time Entity::getAge() const{return age;}
Angle Entity::getOrientation() const{return orientation;}
double Entity::getEnergy() const {return energy;}
Cage* Entity::getCage() const{return cage;}

void Entity::drawDebug(sf::RenderTarget& target)const{
            //draws the energy
        auto text = buildText(to_nice_string(energy),
                    position,
                    getAppFont(),
                    getAppConfig().default_debug_text_size*5,   //why so small
                    sf::Color::Blue,
                    0 / DEG_TO_RAD); // if you want to rotate the text
        target.draw(text);
        CircularBody::drawOn(target);

}

sf::Time Entity::getLongevity() const{
    return sf::seconds(1E+9);
}

void Entity::substractEnergy(double e){
    energy -=e;
}

void Entity::drawOn(sf::RenderTarget& target)const{
    sf::Sprite  entitySprite = buildSprite( getCenter(), 2*getRadius(),        //getCenter, getRadius, getTexture all virtual
                                         getTexture(), getOrientation()/ DEG_TO_RAD); // conversion degree to radians becauce SFML uses these units
    target.draw(entitySprite);
    if(isDebugOn()) drawDebug(target);
}

bool Entity::isAnimal() const{
    return false;
}

bool Entity::canBeConfinedIn(Cage* cage) const{
    return cage->isPositionInside(getCenter()); //can be confinded if position is inside cage
}

double Entity::getRadius() const{
    return getSize()/2;
}

void  Entity::setCage(Cage* c){
    cage=c;
}

void Entity::adjustPostition(){
    double r = getRadius();
    double x = position.x();
    double y = position.y();

    //modularization not worth it because of the operator involved
    //using return type auto as suggensted in the instructions
    auto topWall(cage->getTopLimit(true));
    if (position.y() - r < topWall){
        y = topWall + r * 1.5;
    }
    auto bottomWall(cage->getBottomLimit(true));
    if (position.y() + r > bottomWall){
        y = bottomWall - r * 1.5;
    }
    auto rightWall(cage->getRightLimit(true));
    if (position.x() + r > rightWall){
        x = rightWall - r * 1.5;
    }
    auto leftWall(cage->getLeftLimit(true));
    if (position.x() - r < leftWall){
        x = leftWall + r * 1.5;
    }

    position = Vec2d(x,y);
}


Vec2d Entity::getHeading() const{
    return Vec2d::fromAngle(orientation);
}

void Entity::takeStep(Vec2d step){
    position+=step;
}

void Entity::setOrientation(Angle angle){
    orientation = angle;
}

bool Entity::inCollision(Vec2d p) const{
    return !getCage()->isPositionInside(p, getRadius());
}

void Entity::setEnergy(double e){
    energy=e;
}

void Entity::update(sf::Time dt){
    age+=dt;
}

bool Entity::isDead() const{
    return (age>= this->getLongevity() or getEnergy()<=0);
}

double Entity::provideEnergy(Quantity ){
    return 0;
}


