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
    Icon(Vec2d position, Angle orientation);

    sf::Texture& getTexture();
    double getSize();
    Angle getOrientation();

    void drawOn(sf::RenderTarget& targetWindow) override;

    ~Icon()=default;
};

#endif // ICON_HPP
