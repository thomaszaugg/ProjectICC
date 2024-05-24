#ifndef ICON_HPP
#define ICON_HPP
#include <Utility/Utility.hpp>
#include "SFML/Graphics.hpp"
#include "Interface/Drawable.hpp"

class Icon: public Drawable
{
private:
    Vec2d position;
    Angle orientation;

    /*!
    * @brief Getters specific for Icon
    */
    sf::Texture& getTexture() const;
    double getSize() const;
    Angle getOrientation() const;

public:

    /*!
    * @brief Constructor
    */
    Icon(Vec2d position, Angle orientation);

    /*!
    * @brief drawing method
    */
    void drawOn(sf::RenderTarget& targetWindow) const override;

    /*!
    * @brief Default Destructor
    */
    ~Icon()=default;
};

#endif // ICON_HPP
