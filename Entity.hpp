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


    /*!
    * @brief Setter for attribut Cage
    */
    void  setCage(Cage* c);

    /*!
    * @brief draws the informations given by debug mode
    */
    void drawEnergy(sf::RenderTarget& target);

    /*!
    * @brief substracts a certain amound of energy from the energy of an entity
    */
    void substractEnergy(double e);

    /*!
    * @brief drawing of entity
    */
    void drawOn(sf::RenderTarget& targetWindow);

    /*!
    * @brief boolean function to indecate if the entity is an animal
    *
    * @return returns true if it is an animal
    */
    virtual bool isAnimal();

    /*!
    * @brief updates the age of an entitiy by time dt
    *
    * @return returns false if the energy is bigger than 0 and the Longevity is not yet reached
    */
    virtual bool update(sf::Time dt);

    /*!
    * @brief checks whether an entity can be confined in a cage
    */
    virtual bool canBeConfinedIn(Cage* cage);

    /*!
    * @brief adjusts position of the entity (so that no part of it is on the wall)
    */
    void adjustPostition();
    virtual ~Entity()=default;

    Vec2d getHeading();
    void  updatePosition(Vec2d step);


    bool inCollision(Vec2d position);
    void setOrientation(Angle angle);

    void setEnergy(double);


};

#endif // ENTITY_HPP
