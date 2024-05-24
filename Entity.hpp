#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <Utility/Utility.hpp>
#include <SFML/Graphics.hpp>
#include "Cage.hpp"
#include "CircularBody.hpp"
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
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

    sf::Time getAge()  const;
    virtual sf::Time getLongevity() const;
    virtual double getSize() const =0;
    virtual sf::Texture& getTexture() const=0;


public:
    /*!
    * @brief Constuctor
    */
    Entity(const Vec2d& position, double energy);

    /*!
    * @brief  destructor
    */
    virtual ~Entity()=default;

    /*!
    * @brief Getters
    */
    virtual Vec2d getCenter() const override;
    double getRadius() const override;
    Angle getOrientation() const;
    Cage* getCage() const;

    /*!
    * @brief Setter for the Cage of the Entity
    */
    void setCage(Cage* c);

    /*!
    * @brief boolean function to indecate if the entity is an animal
    *
    * @return true if it contains an animal, false otherwise
    */
    virtual bool isAnimal() const;

    /*!
    * @brief drawing of entity
    */
    virtual void drawOn(sf::RenderTarget& targetWindow) const override;

    /*!
    * @brief draws the energy
    */
    virtual  void drawDebug(sf::RenderTarget& target)const;

    /*!
    * @brief updates the age of an entitiy by time dt
    */
    virtual void  update(sf::Time dt)override;

    /*!
    * @return returns false if the energy is smaller than 0 or the Longevity is reached
    */
    bool isDead() const;

    /*!
    * @brief checks whether an entity can be confined in a cage:
    *        entity not on wall
    */
    virtual bool canBeConfinedIn(Cage* cage) const;

    /*!
    * @brief adjusts position of the entity (so that no part of it is on the wall)
    */
    void adjustPostition();

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

protected:
    /*!
    * @brief Getter for energy level
    */
    double getEnergy() const;

    /*!
    * @brief Setters
    */
    void setOrientation(Angle angle);
    void setEnergy(double);

    /*!
    * @return Unit vector pointing in the direction of the entity
    */
    Vec2d getHeading() const;

    /*!
    * @brief adds step to the current position
    */
    void  takeStep(Vec2d step);

    /*!
    * @brief checks whether an entity is in collison with a cage wall
    *
    * @return returns true if it is collision
    */
    bool inCollision(Vec2d position) const;

    /*!
    * @brief substracts a certain amound of energy
    */
    void substractEnergy(double e);

};

#endif // ENTITY_HPP
