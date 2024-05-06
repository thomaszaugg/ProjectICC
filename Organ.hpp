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

    //helper for the updateRepresentationAt function
    void setVertexes1(const std::vector<std::size_t>& indexes, int a_blood, int a_organ);

    //helpers initializeBloodNetwork
    virtual void generateArtery();
    void generateCapillary();

protected:
    virtual void generate();

    //helpers generate
    void reloadConfig();
    void initOrganTexture (); //initalize organTexture
     //createOrgan(); //create organ fragment
      void createBloodSystem(bool generateCapillaries=true); //create blood network

      //helper createBloodSystem
     virtual void generateCapillaryOneStep(CellCoord& current_position , const CellCoord& dir, int& nbCells, const int& maxLength);
    virtual void generateCapillaryFromPosition(CellCoord &current_position , CellCoord dir);


    virtual void updateCellsLayer(const CellCoord& pos, Kind kind);


public:

    Organ(bool generation = true);
    virtual ~Organ()=default;
    void update() ;
    void drawOn(sf::RenderTarget& target);

    void updateRepresentation(bool changed = true); //helper generate
    virtual void updateRepresentationAt(const CellCoord&);

    int getWidth () const;
    int getHeight() const;

    //4.2
    bool isOut(CellCoord position);

    virtual CellCoord toCellCoord(const Vec2d& position) const;


    void drawCells(std::string name_cell);


    void drawRepresentation();



};

#endif // ORGAN_HPP
