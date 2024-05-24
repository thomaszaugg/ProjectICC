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
    * @brief Constructor and virtual destructor
    */
    Hamster(Vec2d position);
    virtual ~Hamster()=default;

private:

    /*!
    * @brief Getters -> specific for hamsters
    */
    virtual sf::Time getLongevity() const override;
    virtual double getSize() const override;
    virtual sf::Texture& getTexture() const override;
    double getMaxSpeed() const override ;
    double getEnergyLoss() const override;
    double getFatigueEnergy() const override;
    double getMass() const override;
    double getDeceleration() const override;
    double getEnergyBite() const override;

    /*!
    * @brief return true if the entity can consume the entity passed as a parameter
    */
    bool canConsume(Entity const* entity) const override ;

    /*!
    * @brief Helpers for the canConsume function
    */
    bool consumableBy(Pellets const*) const override;
    bool consumableBy(Hamster const*) const override;

};
#endif // HAMSTER_HPP
