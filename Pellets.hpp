#ifndef PELLETS_HPP
#define PELLETS_HPP
#include <Utility/Utility.hpp>
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#pragma once

class Pellets : public Entity
{
public:
    Pellets(Vec2d position);
    Quantity provideEnergy(Quantity qte);

    virtual double getSize() const override; //3.1 const
    virtual sf::Texture& getTexture() override;
    virtual double getRadius() const override; //3.1 const


};

#endif // PELLETS_HPP
