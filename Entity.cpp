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
                                getAppConfig().default_debug_text_size,
                                sf::Color::Blue,
                                0 / DEG_TO_RAD); // if you want to rotate the text
          target.draw(text);
      }
 }
