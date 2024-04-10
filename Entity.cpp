#include "Entity.hpp"
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>
#include "Cage.hpp"

Entity::Entity(const Vec2d& position, double energy)
    : position(position), age(sf::Time::Zero), energy(energy), cage(nullptr){
    orientation = uniform(0.0, TAU);

}

Vec2d Entity::getPosition(){return position;}
sf::Time Entity::getAge(){return age;}
Angle Entity::getOrientation(){return orientation;}
double Entity::getEnergy(){return energy;}
Cage* Entity::getCage(){return cage;}

 void Entity::drawEnergy(sf::RenderTarget& target){
      if(isDebugOn()){
          auto text = buildText(to_nice_string(energy),
                                position,
                                getAppFont(),
                                getAppConfig().default_debug_text_size*5,   //why so small
                                sf::Color::Blue,
                                0 / DEG_TO_RAD); // if you want to rotate the text
          target.draw(text);
      }
 }

 bool Entity::increaseAge(sf::Time time){
     age+=time;
     return (age>= this->getLongevity() or getEnergy()<=0);
 }

 sf::Time Entity::getLongevity(){
     return sf::seconds(1E+9);
 }

 void Entity::substractEnergy(double e){
     energy -=e;
 }

 void Entity::drawOn(sf::RenderTarget& target){
     sf::Sprite  entitySprite = buildSprite( getPosition(), getSize(), getTexture(),getOrientation()/ DEG_TO_RAD); // conversion degree to radians becauce SFML uses these units
     target.draw(entitySprite);

     drawEnergy(target);
 }
