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
    Angle orientation;        //radians, negative okay
    double energy;
    Cage* cage;

public:
    /*!
    * @brief Constuctor
    */
    Entity(const Vec2d& position, double energy);

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
    Vec2d getHeading();

    /*!
    * @brief Setters
    */
    void setCage(Cage* c);
    void setOrientation(Angle angle);
    void setEnergy(double);

    /*!
    * @brief boolean function to indecate if the entity is an animal
    *
    * @return returns false in entity, returns true if the one in animal is called
    */
    virtual bool isAnimal();

    /*!
    * @brief substracts a certain amound of energy from the energy of an entity
    */
    void substractEnergy(double e);

    /*!
    * @brief drawing of entity
    */
    void drawOn(sf::RenderTarget& targetWindow);

    /*!
    * @brief draws the informations given by debug mode
    */
    void drawEnergy(sf::RenderTarget& target);


    /*!
    * @brief updates the age of an entitiy by time dt
    *
    * @return returns false if the energy is smaller than 0 and the Longevity is reached
    */
    virtual bool update(sf::Time dt);

    /*!
    * @brief checks whether an entity can be confined in a cage:
    *        entity not on wall
    */
    virtual bool canBeConfinedIn(Cage* cage);

    /*!
    * @brief adjusts position of the entity (so that no part of it is on the wall)
    */
    void adjustPostition();

    /*!
    * @brief updates the position attribut of an entitiy
    */
    void  updatePosition(Vec2d step);

    /*!
    * @brief checks whether an entity is in collison with a cage wall
    *
    * @return returns true if it is collision
    */
    bool inCollision(Vec2d position);

    /*!
    * @brief default destructor
    */
    virtual ~Entity()=default;

};

#endif // ENTITY_HPP
