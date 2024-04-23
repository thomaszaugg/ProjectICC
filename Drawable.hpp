#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include "DrawingPriority.h"
#include <SFML/Graphics.hpp>


class Drawable
{
public:
    /*!
    * @brief Virtual drawing function
    */
    virtual void drawOn(sf::RenderTarget& targetWindow)=0;

    /*!
    * @brief Virtual getter for drawing priority
    * @return DEFAULT_PRIORITY
    */
    virtual DrawingPriority getDepth();
};

#endif // DRAWABLE_HPP
