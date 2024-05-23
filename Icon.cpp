#include "Icon.hpp"
#include "Application.hpp"


Icon::Icon(Vec2d position, Angle orientation)
    :position(position), orientation(orientation){}

sf::Texture& Icon::getTexture() const{
    return getAppTexture(getAppConfig().entity_texture_tracked);
}

double Icon::getSize() const{
    return getAppConfig().hamster_size/4; //Size von Icon noch nicht gefunden -> doing it on step 6 (extension)
}

Angle Icon::getOrientation() const{
    return orientation;
}

void Icon::drawOn(sf::RenderTarget& target) const{
    sf::Sprite  Icon = buildSprite(position, getSize(),
                                          getTexture(), getOrientation());
    target.draw(Icon);
}
