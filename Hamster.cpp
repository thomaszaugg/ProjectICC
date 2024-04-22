#include "Hamster.hpp"
#include "Application.hpp"



Hamster::Hamster(Vec2d position)
    :Animal(position, getAppConfig().hamster_energy_initial){
}

sf::Time Hamster::getLongevity(){
    return getAppConfig().hamster_longevity;
}

double Hamster::getSize() const{
    return getAppConfig().hamster_size;
}

sf::Texture& Hamster::getTexture(){
    return getAppTexture(getAppConfig().hamster_texture_brown);
}

double Hamster::getMaxSpeed(){
    return getAppConfig().hamster_max_speed;
   }

double Hamster::getFatigueEnergy(){
    return 300;
}

double Hamster::getEnergyLoss(){
    return getAppConfig().hamster_energy_loss_factor;
}

bool Hamster::canConsume(Entity const* entity) const {
    return entity->consumableBy(this);
}

bool Hamster::consumableBy(Pellets const*)const{
    return false;
}

bool Hamster::consumableBy(Hamster const*) const {
    return false;
}

double Hamster::getMass()const{
    return getAppConfig().hamster_mass ;
}

double Hamster::getDeceleration() const {
    return 0.3; //getAppConfig().hamster_deceleration; how to add to AppConfig
}

double Hamster::getEnergyBite() const{
    return getAppConfig().hamster_energy_bite*0.01;
}

