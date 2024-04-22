#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <Utility/Utility.hpp>
#include <SFML/Graphics.hpp>
#include "Cage.hpp"
#include "CircularBody.hpp"
#include "Drawable.hpp"
#include "Updatable.hpp"
#pragma once

class Hamster;
class Pellets;

class Entity: public CircularBody, public Drawable, public Updatable
{
private:
    Vec2d position;
    sf::Time age;
    Angle orientation;        //radians, negative okay
    double energy;
    Cage* cage;

public:
    /*!
    * @brief Constuctor
    */
    Entity(const Vec2d& position, double energy);

    /*!
    * @brief default destructor
    */
    virtual ~Entity()=default;

    /*!
    * @brief Getters
    */
    virtual Vec2d getCenter() const override;
    double getRadius() const override;
    sf::Time getAge() ;
    Angle getOrientation() ;
    double getEnergy() const ;
    Cage* getCage() ;
    virtual sf::Time getLongevity();
    virtual double getSize() const =0;
    virtual sf::Texture& getTexture()=0;


    /*!
    * @brief Setters
    */
    void setCage(Cage* c);
    void setOrientation(Angle angle);
    void setEnergy(double);

    /*!
    * @brief boolean function to indecate if the entity is an animal
    *
    * @return true if it contains an animal, false otherwise
    */
    virtual bool isAnimal();

    /*!
    * @brief substracts a certain amound of energy
    */
    void substractEnergy(double e);

    /*!
    * @brief drawing of entity
    */
    void drawOn(sf::RenderTarget& targetWindow) override;

    /*!
    * @brief draws the informations given by debug mode
    */
  virtual  void drawDebug(sf::RenderTarget& target);


    /*!
    * @brief updates the age of an entitiy by time dt
    */
    virtual void  update(sf::Time dt)override;

    /*!
    * @return returns false if the energy is smaller than 0 or the Longevity is reached
    */
    bool isDead();

    /*!
    * @brief checks whether an entity can be confined in a cage:
    *        entity not on wall
    */
    virtual bool canBeConfinedIn(Cage* cage);

    /*!
    * @brief adjusts position of the entity (so that no part of it is on the wall)
    */
    void adjustPostition();

protected:

    /*!
    * @return Unit vector pointing in the direction of the entity
    */
    Vec2d getHeading();

    /*!
    * @brief adds step to the current position
    */
    void  takeStep(Vec2d step);

    /*!
    * @brief checks whether an entity is in collison with a cage wall
    *
    * @return returns true if it is collision
    */
    bool inCollision(Vec2d position);


public:
    /*!
    * @brief return true if the entity can consume the entity passed as a parameter
    */
    virtual bool canConsume(Entity const* entity) const = 0;

    /*!
    * @brief Helpers for the canConsume function
    */
   virtual bool consumableBy(Pellets const*) const =0;
   virtual bool consumableBy(Hamster const*) const =0;


    /*!
    * @brief empty function that can be changed in subclasses for implementation of eating
    */
    virtual double provideEnergy(Quantity qte);
};

#endif // ENTITY_HPP
