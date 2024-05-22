#ifndef ICON_HPP
#define ICON_HPP
#include <Utility/Utility.hpp>
#include "SFML/Graphics.hpp"
#include "Drawable.hpp"

class Icon: public Drawable
{
private:
    Vec2d position;
    Angle orientation;

public:

    /*!
    * @brief Constructor
    */
    Icon(Vec2d position, Angle orientation);

    /*!
    * @brief Getters specific for Icon
    */
    sf::Texture& getTexture();
    double getSize();
    Angle getOrientation();

    /*!
    * @brief drawing method
    */
    void drawOn(sf::RenderTarget& targetWindow) override;

    /*!
    * @brief Default Destructor
    */
    ~Icon()=default;
};

#endif // ICON_HPP
