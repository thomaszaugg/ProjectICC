#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <Utility/Utility.hpp>
#include <SFML/Graphics.hpp>
#include "Cage.hpp"
#include "CircularBody.hpp"
#include "Application.hpp"
#pragma once

class CircularBody;

class Entity: public CircularBody
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
    virtual sf::Time getLongevity();

     void drawEnergy(sf::RenderTarget& target);
     bool increaseAge(sf::Time time);
     void substractEnergy(double);

     //3.1
     void drawOn(sf::RenderTarget& targetWindow);

     virtual double getSize() =0;
     virtual sf::Texture getTexture()=0;

     virtual ~Entity()=default;




};

#endif // ENTITY_HPP
