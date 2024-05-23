#ifndef ORGAN_HPP
#define ORGAN_HPP
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
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

    int counter; //counter for updating the visual representation

    /*!
    * @brief helper for the updateRepresentationAt function
    */
    void setVertexes1(const std::vector<std::size_t>& indexes, int a_blood, int a_organ, int a_cancer, bool concentrationOn=false, double ratio=0.);

    //helpers initializeBloodNetwork
    virtual void generateArtery(int& leftColumn, int& rightColumn);
    void generateCapillary(int const& leftColumn, int const& rightColumn);
    void checkStep(bool& direction_step_possible, bool& empty_neighboor_found,CellCoord  current_position, CellCoord  dir);
    std::vector<CellCoord> const generateStartingPositions(int const& column);
    void generateOneSideCapillary(CellCoord const& direction, int const& column);

    /*!
    * @brief defintion of organ boundaries
    */
    bool organBoundaries(CellCoord pos) const;

    /*!
    * @brief evaluating of possible position for the division
    * @return vector with possible positions
    */
    std::vector<CellCoord> getPossiblePositions(CellCoord pos, bool hasCancer)const;

    /*!
    * @brief checks if the condition for a division are fullfilled
    * @return true if Cell can divide
    */
    bool isDivisonPossible(int x, int y,bool hasCancer) const;

    /*!
    * @brief checking whether a position is inside the organ boundaries
    */
    bool isInsideLiver(CellCoord pos) const;

    /*!
    * @brief Getters
    */
    int getWidth () const;
    int getHeight() const;

    /*!
    * @brief drawing of the according texture of the Cell
    */
    void drawCells(std::string name_cell);

    /*!
    * @brief drawing of the correct layers of the organ
    */
    void drawRepresentation();

protected:

    /*!
    * @brief generates the organ using helper functions
    */
    void generate();

    /*!
    * @brief initialization of attributs and construction of the CellsLayer grid
    */
    void reloadConfig();

    /*!
    * @brief initializing the vertex vectors
    */
    void initOrganTexture ();

    /*!
    * @brief creating of the OrganCells within the boundaries
    */
    void createOrgan();

    /*!
    * @brief creating of blood network
    */
    void createBloodSystem(bool generateCapillaries=true);

    //helper createBloodSystem
    virtual bool generateCapillaryOneStep(CellCoord& current_position , const CellCoord& dir, int& nbCells, const int& maxLength);
    virtual void generateCapillaryFromPosition(CellCoord &current_position , CellCoord dir);

    /*!
    * @brief updating the Cellslayer at a specified position with a specified type of Cell
    */
    virtual void updateCellsLayer(const CellCoord& pos, Kind kind);

public:

    /*!
    * @brief Constructor
    */
    Organ(bool generation = true);

    /*!
    * @brief Destructor
    */
    virtual ~Organ()=default;

    /*!
    * @brief updating of each Cell in the Organ
    */
    void update();

    /*!
    * @brief drawing of Organ
    */
    void drawOn(sf::RenderTarget& target) const override;

    /*!
    * @brief updating the visual representation of the organ
    */
    void updateRepresentation(bool changed = true);

    /*!
    * @brief updating the visual representation at a given position
    */
    virtual void updateRepresentationAt(const CellCoord&);

    /*!
    * @brief Checking if a position is outside of the organ
    * @return true if the positon is outside
    */
    bool isOut(CellCoord position) const;

    /*!
    * @brief changing from Vec2d to CellCoord
    * @return coordinate in type CellCoord
    */
    virtual CellCoord toCellCoord(const Vec2d& position) const;

    /*!
    * @brief updating of the substance at ECM level
    */
    void updateCellsLayerAt(const CellCoord& pos, const Substance& diffusedSubst);

    /*!
    * @brief Getter for Concentration of a given Substance on ECM level
    * @return Concentration of Substance
    */
    double getConcentrationAt(const CellCoord& pos, SubstanceId id);

    /*!
    * @brief switching to the next substance
    */
    void nextSubstance();

    /*!
    * @brief changing of the delta value of the current Substance
    */
    void changeDeltaSubstance(bool minus);//if minus, delta is substracted

    /*!
    * @brief Getter for delta of a SubstanceId
    */
    double getDelta(SubstanceId id);

    /*!
    * @brief Getter for Current Substance
    */
    SubstanceId getCurrentSubst();

    /*!
    * @brief Setter for a Cancer Cell
    */
    void setCancerAt(const Vec2d& pos);

    /*!
    * @brief checks with different helper function if a division is possible
    */
    bool requestToDivide(CellCoord pos, bool hasCancer);

};

#endif // ORGAN_HPP
