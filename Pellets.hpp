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
    * @brief Constructor and destructor
    */
    Pellets(Vec2d position);
    ~Pellets()=default;

    /*!
    * @brief calculating the new energy of a Pellet after the energy qte has been eaten
    *
    * @return Quantity (double) of energy of the Pellet
    */
    Quantity provideEnergy(Quantity qte) override;

    /*!
    * @brief Getters
    */
    virtual double getSize() const override;
    virtual sf::Texture& getTexture() override;

    /*!
    * @brief return true if the entity can consume the entity passed as a parameter
    */
bool canConsume(Entity const* entity) const override;

/*!
* @brief returns FOOD_PRIORITY
*/
DrawingPriority getDepth()override;

/*!
* @brief Helpers for the canConsume function
*/
bool consumableBy(Pellets const*) const override;
bool consumableBy(Hamster const*) const override;
};

#endif // PELLETS_HPP
