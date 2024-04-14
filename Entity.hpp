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

    virtual Vec2d getCenter() const override ; //3.1 -> changed name from getCenter to getPosition
    sf::Time getAge() ;
    Angle getOrientation() ;
    double getEnergy() const ; //3.1 const
    Cage* getCage() ;
    virtual sf::Time getLongevity();

     void drawEnergy(sf::RenderTarget& target);
     bool increaseAge(sf::Time time);
     void substractEnergy(double);

     //3.1
     void drawOn(sf::RenderTarget& targetWindow);

     virtual double getSize() const =0; //3.1 const
     virtual sf::Texture& getTexture()=0;

     virtual ~Entity()=default;
     virtual bool isAnimal(){return false;}

     /*
     virtual bool canBeConfined(Cage* cage);
*/





};

#endif // ENTITY_HPP
