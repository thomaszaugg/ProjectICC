#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <Utility/Utility.hpp>
#include <SFML/Graphics.hpp>
#include "Cage.hpp"
#include "CircularBody.hpp"
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

    virtual Vec2d getCenter() const override ;
    sf::Time getAge() ;
    Angle getOrientation() ;
    double getEnergy() const ; //3.1 const
    Cage* getCage() ;
    virtual sf::Time getLongevity();

   void  setCage(Cage* c);

     void drawEnergy(sf::RenderTarget& target);

     void substractEnergy(double);

     //3.1
     void drawOn(sf::RenderTarget& targetWindow);

     virtual double getSize() const =0; //3.1 const
     virtual sf::Texture& getTexture()=0;
     double getRadius() const override;

     virtual bool isAnimal();

    virtual bool update(sf::Time dt);


     virtual bool canBeConfinedIn(Cage* cage);
     void adjustPostition();
     virtual ~Entity()=default;

     Vec2d getHeading();
     void  updatePosition(Vec2d step);


    bool inCollision(Vec2d position);
    void setOrientation(Angle angle);

    void setEnergy(double);


};

#endif // ENTITY_HPP
