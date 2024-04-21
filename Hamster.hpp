#ifndef HAMSTER_HPP
#define HAMSTER_HPP
#include <Utility/Utility.hpp>
#include "Animal.hpp"
#pragma once

class Animal;

class Hamster : public Animal
{
public:
    /*!
    * @brief Constructor
    */
    Hamster(Vec2d position);

    /*!
    * @brief Getters -> specific for hamsters
    */
    virtual sf::Time getLongevity() override;
    virtual double getSize() const override; //3.1 const
    virtual sf::Texture& getTexture() override;

    double getMaxSpeed() override ;
    double getEnergyLoss() override;
    double getFatigueEnergy() override;

    bool canConsume(Entity const* entity) const override ;
    bool consumableBy(Pellets const*) const override;
    bool consumableBy(Hamster const*) const override;
    double getMass() const override;
     double getDeceleration() const override;
     double getEnergyBite() const override;
};
#endif // HAMSTER_HPP
