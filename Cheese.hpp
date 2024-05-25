#ifndef CHEESE_HPP
#define CHEESE_HPP
#include <Utility/Utility.hpp>
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class Cheese : public Entity
{
public:
    /*!
    * @brief Constructor
    */
    Cheese (Vec2d position);

    /*!
    * @brief Destructor
    */
    ~Cheese()=default;

    /*!
    * @brief calculating the new energy of a Pellet after the energy qte has been eaten
    * @return Quantity of energy of the Pellet that was actually eaten
    */
    Quantity provideEnergy(Quantity qte) override;

    virtual bool isCheese() const override;

private:

    /*!
    * @brief Getters
    */
    virtual double getSize() const override;
    virtual sf::Texture& getTexture() const override;

    /*!
    * @brief return true if the entity can consume the entity passed as a parameter
    */
    bool canConsume(Entity const* entity) const override;

    /*!
    * @brief returns FOOD_PRIORITY
    */
    DrawingPriority getDepth() const override;

    /*!
    * @brief Helpers for the canConsume function
    */
    bool consumableBy(Pellets const*) const override;
    bool consumableBy(Hamster const*) const override;
    bool consumableBy(Cheese const*) const override;
};


#endif // CHEESE_HPP