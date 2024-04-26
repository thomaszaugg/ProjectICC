#ifndef ORGAN_HPP
#define ORGAN_HPP
#include "Drawable.hpp"
#include "Updatable.hpp"

#pragma once


class Organ: public Drawable /*public Updatable*/
{
private:
    int nbCells;
    float cellSize;
    sf::RenderTexture organTexture;

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

};

#endif // ORGAN_HPP
