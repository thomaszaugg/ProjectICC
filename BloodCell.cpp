#include "BloodCell.hpp"
#include "CellsLayer.hpp"
#include "Application.hpp"
#include <cmath>

BloodCell::BloodCell(CellsLayer* cellslayer, TypeBloodCell type)
    : Cell(cellslayer), type(type){}        //@lisa ha hie no type drzegfügt dasme o öpis angers cha drigäh

void BloodCell::update(sf::Time dt) {
    if(type==ARTERY) return; //do nothing if its an artery

   Substance c0(0., getAppConfig().base_glucose, getAppConfig().base_bromo);
   Substance c(0.,0.,0.);
   CellCoord position_bloodcell=getCellsLayer()->getPosition(),j;
   int x=position_bloodcell.x;
   int y=position_bloodcell.y;
   double D=getAppConfig().substance_diffusion_radius;
   int RAYON_DIFFUSION=getAppConfig().substance_diffusion_radius;

    for(int i(x-RAYON_DIFFUSION);i<=RAYON_DIFFUSION+x; ++i){
        for(int j(y-RAYON_DIFFUSION);j<=RAYON_DIFFUSION+y; ++j){

            update(position_bloodcell, {i,j}, c0, D, dt);
  }}
}

void BloodCell::update(CellCoord const& pos_bloodcell, CellCoord const& pos_ecm_cell, Substance c, double const& D, sf::Time  dt){
    if(getCellsLayer()->isOut(pos_ecm_cell)) return;
    Vec2d distanceV=pos_bloodcell,position_othercell;
    double r=distanceV.length();
     c=c*(0.5*( 1-erf(r/sqrt(4*D*dt.asSeconds()))));
    if(!c.isNull()){
        getCellsLayer()->updateCellsLayerAt(pos_ecm_cell, c);
    }
}
