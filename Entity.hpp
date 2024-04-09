#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <Utility/Utility.hpp>
#include <SFML/Graphics.hpp>
#include "Cage.hpp"
#include "Application.hpp"

class Entity
{
private:
    Vec2d position;
    sf::Time age;
    Angle orientation;        //radians
    double energy;
    Cage* cage;

public:
    Entity(const Vec2d& position, double energy);

    Vec2d getPosition() ;
    sf::Time getAge() ;
    Angle getOrientation() ;
    double getEnergy() ;
    Cage* getCage() ;

     void drawEnergy(sf::RenderTarget& target);

};

#endif // ENTITY_HPP
