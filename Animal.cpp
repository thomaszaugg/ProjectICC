#include "Animal.hpp"



bool Animal::isAnimal() {
    return true;
}

bool Animal::canBeConfined(Cage* cage){
    if (cage->isEmpty()){
        return true;
    }else{
        return false;
    }
}
