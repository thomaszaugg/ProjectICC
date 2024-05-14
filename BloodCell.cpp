#include "BloodCell.hpp"
#include "CellsLayer.hpp"
#include "Application.hpp"
#include <cmath>

BloodCell::BloodCell(CellsLayer* cellslayer, TypeBloodCell type)
    : Cell(cellslayer), type(type){}        //@lisa ha hie no type drzegfügt dasme o öpis angers cha drigäh

void BloodCell::update(sf::Time dt) {
    if(type==ARTERY) return; //do nothing if its an artery

    Substance c0(0., getAppConfig().base_glucose, getAppConfig().base_bromo);

    CellCoord position_bloodcell=getCellsLayer()->getPosition(); //main cell that is diffusing its substances
    int x=position_bloodcell.x;
    int y=position_bloodcell.y;
    double D=getAppConfig().substance_diffusion_radius;

    for(int i(x-D);i<=D+x; ++i){ //iteration trought all the cells in the diffusion radius
        for(int j(y-D);j<=D+y; ++j){
            CellCoord pos_ecm_cell(i,j);
            update(position_bloodcell, pos_ecm_cell, c0, D, dt);
    }}
}

void BloodCell::update(CellCoord const& pos_bloodcell, CellCoord const& pos_ecm_cell, Substance c0, double const& D, sf::Time  dt){
    if(getCellsLayer()->isOut(pos_ecm_cell)) return;
    Substance c(0.,0.,0.);
    double i = pos_bloodcell.x - pos_ecm_cell.x;
    double j = pos_bloodcell.x - pos_ecm_cell.y;
    Vec2d distance(i,j);
    double r=distance.length();
    double function = 0.5* (1-erf(r/sqrt(4*D*dt.asSeconds())));
    c = c0 * function;

    if(!c.isNull()){
        getCellsLayer()->updateCellsLayerAt(pos_ecm_cell, c);
    }
}
