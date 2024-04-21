#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <Utility/Utility.hpp>
#include "Entity.hpp"
#pragma once

enum State{
               TARGETING_FOOD, // se dirige vers la nourriture
               FEEDING,        // en train de manger (là en principe il arrête de se déplacer)
               WANDERING,      // déambule
               IDLE,           // au repos
              };

class Animal : public Entity
{


private:
   State state;
   double speed;
   sf::Time counter=sf::Time::Zero;

public:

    /*!
    * @brief Consturctor
    */
    Animal(const Vec2d& position, double energy);

    /*!
    * @brief Getters
    */
    Vec2d getSpeedVector();
    double getFatigueFactor();
    Angle getNewRotation();

    /*!
    * @brief purely virtual getters
    */
    virtual double getMaxSpeed()=0;
    virtual  double getFatigueEnergy()=0;
    virtual double getEnergyLoss() = 0;

    /*!
    * @brief boolean function to indecate if the entity is an animal
    *
    * @return true
    */
    bool isAnimal() override;

    /*!
    * @brief checks whether an animal can be confined in a cage
    *
    * @return true if cage empty an animal not on wall
    */
    bool canBeConfinedIn(Cage* c) override;

    /*!
    * @brief calls the 3 following update functions
    *
    * @return boolean value of entity::update(dt) function -> true if animal has enough energy to live
    */
    bool update(sf::Time dt) override;

    /*!
    * @brief updates the speed
    */
    void updateState(sf::Time dt);

    /*!
    * @brief changes the orientation and the position
    */
    void move(sf::Time dt);

    /*!
    * @brief calculates the new energy of the animal after time dt
    */
    void updateEnergy(sf::Time dt);

    /*!
    * @brief destructor
    */
    virtual ~Animal() ;

};

#endif // ANIMAL_HPP
