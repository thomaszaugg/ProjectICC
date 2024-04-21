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
};
#endif // HAMSTER_HPP
