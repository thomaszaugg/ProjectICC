#ifndef UPDATABLE_HPP
#define UPDATABLE_HPP
#include <SFML/Graphics.hpp>

class Updatable
{
public:
    virtual void  update(sf::Time dt) =0;
};

#endif // UPDATABLE_HPP
