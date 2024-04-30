#ifndef ORGAN_HPP
#define ORGAN_HPP
#include "Drawable.hpp"
#include "Updatable.hpp"
#include "Utility/Utility.hpp"
#include "Cellslayer.hpp"
#include "Utility/Vertex.hpp"

#pragma once



class Organ: public Drawable /*public Updatable*/
{
private:
    int nbCells;
    float cellSize;
    sf::RenderTexture organTexture;
    std::vector<std::vector<CellsLayer*>> cellsLayers;

    std::vector<sf::Vertex> bloodVertexes;
    std::vector<sf::Vertex> organVertexes;

protected:
    virtual void generate();

    //helpers generate
    void reloadConfig();
    void initOrganTexture (); //initalize organTexture
     /*createOrgan(); //create organ fragment
      createBloodSystem(); //create blood network*/

public:
    Organ(bool generation = true);//maybe default value? @tom: yess written in enonce
    virtual ~Organ()=default;
    void update() ;
    void drawOn(sf::RenderTarget& target);

    void updateRepresentation(); //helper generate
    virtual void updateRepresentationAt(const CellCoord&);

    int getWidth ();
    int getHeight();

    //4.2
    bool isOut(CellCoord position);

    CellCoord toCellCoord(const Vec2d position);

    //wie machbar ohne code zu kopieren?
    void drawBloodCells();

    void drawOrganCells();

};

#endif // ORGAN_HPP
