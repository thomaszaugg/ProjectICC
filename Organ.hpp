#ifndef ORGAN_HPP
#define ORGAN_HPP
#include "Drawable.hpp"
#include "Updatable.hpp"
#include "Utility/Utility.hpp"
#include "CellsLayer.hpp"
#include "Utility/Vertex.hpp"

#pragma once


class Organ: public Drawable /*public Updatable*/ //how to solve this?
{
public:
    //should only be usable by the organ

    enum class Kind : short { ECM, Organ, Artery, Capillary };

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

    virtual void updateCellsLayer(const CellCoord& pos, Kind kind);

public:

    Organ(bool generation = true);
    virtual ~Organ()=default;
    void update() ;
    void drawOn(sf::RenderTarget& target);

    void updateRepresentation(bool changed = true); //helper generate
    virtual void updateRepresentationAt(const CellCoord&);

    int getWidth ();
    int getHeight();

    //4.2
    bool isOut(CellCoord position);

    virtual CellCoord toCellCoord(const Vec2d& position) const;

    //wie machbar ohne code zu kopieren?
    void drawBloodCells();

    void drawOrganCells();

    void drawRepresentation();



};

#endif // ORGAN_HPP
