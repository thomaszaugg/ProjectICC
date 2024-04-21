#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <Utility/Utility.hpp>
#include "Entity.hpp"
#pragma once

enum State{
               TARGETING_FOOD, // walks to food
               FEEDING,        // eats
               WANDERING,      // explores
               IDLE,           // strolls
              };

class Animal : public Entity
{


private:
   State state;
   double speed;
   sf::Time counter=sf::Time::Zero;

   void changeOrientation(sf::Time dt);

public:

    /*!
    * @brief Constructor
    */
    Animal(const Vec2d& position, double energy);

    /*!
    * @brief destructor
    */
    virtual ~Animal() ;

    /*!
    * @brief Getters
    */
    Vec2d getSpeedVector();
   virtual double getFatigueFactor();  //by default the same for all animals, possiblility to override
    Angle getNewRotation();
    double getAdjustedMaxSpeed();

    /*!
    * @brief purely virtual getters
    */
    virtual double getMaxSpeed()=0;
    virtual  double getFatigueEnergy()=0;   //energy at which the animal starts to slow down
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
    * @return true if cage is empty an animal is not placed on wall
    */
    bool canBeConfinedIn(Cage* c) override;

    /*!
    * @brief calls the 3 following update functions
    */
    void  update(sf::Time dt) override;

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


};



#endif // ANIMAL_HPP
