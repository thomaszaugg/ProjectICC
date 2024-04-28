#ifndef ORGAN_HPP
#define ORGAN_HPP
#include "Drawable.hpp"
#include "Updatable.hpp"
#include "Utility/Utility.hpp"
#include "Cellslayer.hpp"

#pragma once



class Organ: public Drawable /*public Updatable*/
{
private:
    int nbCells;
    //size_t nbCells;
    float cellSize;
    sf::RenderTexture organTexture;
    std::array<std::array<CellsLayer*, 10>, 10> cellsLayers_; // how does it work with the variable nbCells as parameter for the size ???????


protected:
    virtual void generate();

    //helpers generate
     void reloadConfig();
    void initOrganTexture (); //initalize organTexture
     /*createOrgan(); //create organ fragment
      createBloodSystem(); //create blood network*/

public:
    Organ(bool generation);//maybe default value?
    virtual ~Organ()=default;
    void update() ;
    void drawOn(sf::RenderTarget& target);

    void updateRepresentation(); //helper generate
   // void updateRepresentationAt(const CellCoord&);

    int getWidth ();
    int getHeight();

    //4.2
    bool isOut(CellCoord position);

    CellCoord toCellCoord(const Vec2d position);



};

#endif // ORGAN_HPP
