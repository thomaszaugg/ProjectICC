#ifndef PELLETS_HPP
#define PELLETS_HPP
#include <Utility/Utility.hpp>
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#pragma once

class Pellets : public Entity
{
public:
    /*!
    * @brief Constructor
    */
    Pellets(Vec2d position);

    /*!
    * @brief calculating the new energy of a Pellet after the energy qte has been eaten
    *
    * @return Quantity (double) of energy of the Pellet
    */
    Quantity provideEnergy(Quantity qte);

    /*!
    * @brief Getters
    */
    virtual double getSize() const override; //3.1 const
    virtual sf::Texture& getTexture() override;


};

#endif // PELLETS_HPP
