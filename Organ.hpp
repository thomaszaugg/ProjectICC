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
    std::vector<sf::Vertex> concentrationVertexes;
    std::vector<sf::Vertex> organCancerVertexes;

    SubstanceId currentSubst;

    //initialized as a vector to not use too unneccesary switch statements
    std::array<double,3> deltas; //glucose=0, .... (like enumerate type)

    //helper for the updateRepresentationAt function
    void setVertexes1(const std::vector<std::size_t>& indexes, int a_blood, int a_organ, int a_cancer, bool concentrationOn=false, double ratio=0.);

    //helpers initializeBloodNetwork
    virtual void generateArtery(int& leftColumn, int& rightColumn);
    void generateCapillary(int const& leftColumn, int const& rightColumn);
    void checkStep(bool& direction_step_possible, bool& empty_neighboor_found,CellCoord  current_position, CellCoord  dir);
    std::vector<CellCoord> const generateStartingPositions(int const& column);
    void generateOneSideCapillary(CellCoord const& direction, int const& column);

protected:
     void generate(); //virtual (only in debug removed

    //helpers generate
    void reloadConfig();
    void initOrganTexture (); //initalize organTexture
    void createOrgan(); //create organ fragment
    bool organBoundaries(CellCoord pos) const; //helper create organ
    void createBloodSystem(bool generateCapillaries=true); //create blood network

    //helper createBloodSystem
    virtual bool generateCapillaryOneStep(CellCoord& current_position , const CellCoord& dir, int& nbCells, const int& maxLength);
    virtual void generateCapillaryFromPosition(CellCoord &current_position , CellCoord dir);

    virtual void updateCellsLayer(const CellCoord& pos, Kind kind);


public:

    Organ(bool generation = true);

    virtual ~Organ()=default;

    void update(); //written in part 5.1

    void drawOn(sf::RenderTarget& target);

    void updateRepresentation(bool changed = true); //helper generate

    virtual void updateRepresentationAt(const CellCoord&);

    int getWidth () const;
    int getHeight() const;

    //4.2
    bool isOut(CellCoord position) const;

    virtual CellCoord toCellCoord(const Vec2d& position) const;

    void drawCells(std::string name_cell);

    void drawRepresentation();

    //5.2
   void updateCellsLayerAt(const CellCoord& pos, const Substance& diffusedSubst);
   //for test at 5
   double getConcentrationAt(const CellCoord& pos, SubstanceId id);

   //6
   void nextSubstance();
   void changeDeltaSubstance(bool minus);//if minus, delta is substracted

   double getDelta(SubstanceId id) ;
   SubstanceId getCurrentSubst();

   void setCancerAt(const Vec2d& pos);

   //division
    bool requestToDivide(CellCoord pos, bool hasCancer);
    std::vector<CellCoord> getPossiblePositions(CellCoord pos, bool hasCancer)const;
    bool isDivisonPossible(int x, int y,bool hasCancer) const;
    bool isInsideLiver(CellCoord pos) const;
};

#endif // ORGAN_HPP
