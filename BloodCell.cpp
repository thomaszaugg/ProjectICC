#include "BloodCell.hpp"
#include "CellsLayer.hpp"

BloodCell::BloodCell(CellsLayer* cellslayer, TypeBloodCell type)
    : Cell(cellslayer), type(type){}        //@lisa ha hie no type drzegfügt dasme o öpis angers cha drigäh

void BloodCell::update(sf::Time dt){

}
