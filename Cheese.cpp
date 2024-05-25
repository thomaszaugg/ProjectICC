#include "Cheese.hpp"
#include "Application.hpp"

Cheese::Cheese(Vec2d position)
    : Entity(position, getAppConfig().cheese_initial_energy)
{}

double Cheese::getSize() const{
    return getEnergy()*10;
}

sf::Texture& Cheese::getTexture() const{
    return getAppTexture(getAppConfig().cheese_texture);
}

bool Cheese::canConsume(Entity const* entity) const {
    return entity->consumableBy(this);
}

bool Cheese::consumableBy(Pellets const*) const {
    return false;
}

bool Cheese::consumableBy(Hamster const*) const {
    return true;
}

bool Cheese::consumableBy(Cheese const*) const{
    return false;
}

DrawingPriority Cheese::getDepth() const{
    return DrawingPriority::FOOD_PRIORITY;
}

Quantity Cheese::provideEnergy(Quantity qte){
    if(qte>getEnergy()){qte=getEnergy();}
    substractEnergy(qte);
    return qte;
}

bool Cheese::isCheese() const{
    return true;
}
