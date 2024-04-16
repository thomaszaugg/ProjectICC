#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <Utility/Utility.hpp>
#include "Entity.hpp"
#pragma once

enum State{
               TARGETING_FOOD, // se dirige vers la nourriture
               FEEDING,       // en train de manger (là en principe il arrête de se déplacer)
               WANDERING,     // déambule
               IDLE,          // au repos
              };

class Animal : public Entity
{


private:
   State state;
   double speed;
   sf::Time counter=sf::Time::Zero;

public:
    Animal(const Vec2d& position, double energy);

    bool isAnimal() override;

    bool canBeConfinedIn(Cage* c) override;

    virtual ~Animal() ;

    public:
        bool update(sf::Time dt) override;
        void updateState(sf::Time dt);


        Vec2d getSpeedVector();

       virtual double getMaxSpeed()=0;
        double getSpeed();

       void move(sf::Time dt);
        Angle getNewRotation();
        void updateEnergy(sf::Time);
      virtual double getEnergyLoss() = 0;

};

#endif // ANIMAL_HPP
