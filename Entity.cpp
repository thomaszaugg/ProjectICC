#include "Entity.hpp"
#include <Utility/Utility.hpp>
#include <Random/Random.hpp>
#include "Cage.hpp"



Entity::Entity(const Vec2d& position, double energy)
    : position(position), age(sf::Time::Zero), energy(energy), cage(nullptr){
    orientation = uniform(0.0, TAU);
}

Vec2d Entity::getCenter() const {return position;}
sf::Time Entity::getAge(){return age;}
Angle Entity::getOrientation(){return orientation;}
double Entity::getEnergy() const {return energy;}
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
          //3.1
          auto circle(buildCircle(getCenter(), getRadius(), sf::Color(20,150,20,30)));
          target.draw(circle);
          //3.1
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
     sf::Sprite  entitySprite = buildSprite( getCenter(), 2*getRadius(), getTexture(),getOrientation()/ DEG_TO_RAD); // conversion degree to radians becauce SFML uses these units
     target.draw(entitySprite);

     drawEnergy(target);
 }

 bool Entity::isAnimal(){
     return false;
 }

 bool Entity::canBeConfined(Cage* cage){
     return true;
 }

 void Entity::adjustPostition(){
     double size(this->getSize());
     double x = position.x();
     double y = position.y();

     auto topWall(cage->getTopLimit(true));
     if (position.y() - size/2 < topWall){
         y = topWall + size/2 * 1.5;
     }
     auto bottomWall(cage->getBottomLimit(true));
     if (position.y() + size/2 > bottomWall){
         y = bottomWall - size/2 * 1.5;
     }
     auto rightWall(cage->getRightLimit(true));
     if (position.x() + size/2 > rightWall){
         x = rightWall - size/2 * 1.5;
     }
     auto leftWall(cage->getLeftLimit(true));
     if (position.x() - size/2 < leftWall){
         x = leftWall + size/2 * 1.5;
     }
     Vec2d newPosition (x,y);
     position = newPosition;
 }
