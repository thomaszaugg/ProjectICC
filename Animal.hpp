#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <Utility/Utility.hpp>
#include "Entity.hpp"
#include "Organ.hpp"
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
   Organ* organ;

   void changeOrientation(sf::Time dt);

public:

    /*!
    * @brief Constructor
    */
    Animal(const Vec2d& position, double energy);

    /*!
    * @brief destructor and desactivated copy constructor
    */
    virtual ~Animal() ;
    Animal(Animal& )=delete;    //to prevent cage pointer


    /*!
    * @brief purely virtual getters
    */
    virtual double getMaxSpeed() const=0;
    virtual double getFatigueEnergy() const=0;   //energy at which the animal starts to slow down
    virtual double getEnergyLoss() const = 0;
    virtual double getMass() const =0;
    virtual double getDeceleration() const =0;
    virtual double getEnergyBite() const=0;

    /*!
    * @brief boolean function to indicate if the entity is an animal
    * @return true
    */
    bool isAnimal() const override;

    /*!
    * @brief checks whether an animal can be confined in a cage
    * @return true if cage is empty and animal is not placed on wall
    */
    bool canBeConfinedIn(Cage* c) const override;

    /*!
    * @brief updtes the energy and state  of the animal and then acts according to the state
    */
    void  update(sf::Time dt) override;

    /*!
    * @brief updates the organ
    */
    void updateOrgan();

    /*!
    * @return speed Vector of the animal
    */
    Vec2d getSpeedVector() const;

    /*!
    * @brief draws the organ
    */
    void drawOrgan(sf::RenderTarget& target) const;

    /*!
    * @return bool indicating whether or not the animal is hungry
    * @attention two different threshholds depending on if the animal is feeding or not
    */
    bool isHungry() const;


    /*!
    * @return ANIMAL_PRIORITY
    */
    DrawingPriority getDepth() const override;

    /*!
    * @brief change the organ to newOrgan (needed for tests)
    */
    void transplant(Organ* newOrgan);

    /*!
    * @brief increasing of the Substance Id of currentSubst in Organ by 1
    */
    void nextSubstance();

    /*!
    * @brief increasing the delta of the currentSubst
    */
    void increaseCurrentSubst();

    /*!
    * @brief decreasing the delta of the currentSubst
    */
    void decreaseCurrentSubst();

    /*!
    * @brief Getter
    * @return delta value of currently observed Substance
    */
    double getDelta(SubstanceId id) const;

    /*!
    * @brief Getter
    * @return SubstanceId of the current Substance
    */
    SubstanceId getCurrentSubst() const;

    /*!
    * @brief setting of a Cancer Cell at the position given with the parameter
    */
    void setCancerAt(const Vec2d& pos);

private:
    /*!
    * @brief Internal getters
    */
    virtual double getFatigueFactor() const;  //by default the same for all animals, possiblility to override
    Angle getNewRotation() const;
    double getAdjustedMaxSpeed() ;
    std::string getStateString() const;

    /*!
    * @brief delets the organ
    */
    void deleteOrgan();

    /*!
    * @brief calculates the force, possibly taking into accout deceleration
    */
    Vec2d calculateForce(Entity* food, double deceleration=1) ;

    /*!
    * @brief modularized eat function
    */
    void eatFood(Entity* food);

    /*!
    * @brief draws energy, state and the circle for the debug mode
    */
    void drawDebug(sf::RenderTarget& target) const override;

    /*!
    * @brief switches to the right state
    */
    void updateState(sf::Time dt, Entity* food);

    /*!
    * @brief changes the orientation and the position (STATE: WANDERING)
    */
    void move(sf::Time dt);

    /*!
    * @brief changes the orientation and the position (STATE: TARGETING AND FEEDING)
    */
    void move(const Vec2d& force, sf::Time dt, bool feeding);

    /*!
    * @brief calculates the new age and energy of the animal after time dt
    */
    void updateEnergy(sf::Time dt);
};

#endif // ANIMAL_HPP
