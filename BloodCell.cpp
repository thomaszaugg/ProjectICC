#include "BloodCell.hpp"
#include "Cellslayer.hpp"

BloodCell::BloodCell(CellsLayer* cellslayer, TypeBloodCell)
    : Cell(cellslayer), type(ARTERY){}
