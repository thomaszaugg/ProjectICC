#ifndef CELLSLAYER_HPP
#define CELLSLAYER_HPP
#include "Cell.hpp"
#include "Utility/Utility.hpp"
#include "ECMCell.hpp"
#include "BloodCell.hpp"
#include "OrganCell.hpp"
#include "TumoralCell.hpp"

class Organ;

class CellsLayer
{
private:
    /*!
    * @brief position in Organ
    */
    CellCoord position;

    /*!
    * @brief pointer to the organ of this CellsLayer
    */
    Organ* organ;

    ECMCell* ecm;           //nullptr if not present
    OrganCell* organCell;   //nullptr if not present
    BloodCell* bloodCell;   //nullptr if not present

public:
    /*!
    * @brief Constructor: position, pointer to organ and the ECM Cell is initalized
    */
    CellsLayer(CellCoord position, Organ* organ);

    /*!
    * @brief Destructor: does delete and set back to nullptr all its cells
    */
    ~CellsLayer(); //why virtual

    /*!
    * @brief Checkers if the CellsLayer has the according Cell
    * @return true if its not a nullptr
    */
    bool hasECMCell() const;
    bool hasOrganCell() const;
    bool hasBloodCell() const;

    /*!
    * @brief Setter for a Cell, one possible to set if there is no cell yet (nullptr)
    */
    void setECMCell();
    void setOrganCell();
    void setBlood(TypeBloodCell type);

    /*!
    * @brief put Substance in ECM level using method addSubstance on Cell level
    */
    void updateSubstance(Substance substance);

    /*!
    * @brief Getters for Substance Quantity
    * @return Quantity, if the Cell does not exist the value 0 is returned
    */
    double getECMQuantity(SubstanceId id) const; //amound not fractions
    double getOrganCellQuantity(SubstanceId id) const;
    double getBloodCellQuantity(SubstanceId id) const;

    /*!
    * @brief Getter for position
    */
    CellCoord getPosition() const;

    /*!
    * @brief OrganCell taking from ECM Cell a specified fraction of a SubstanceId, using uptakeSubstance in Cell Class
    */
    void organCellTakeFromECM(SubstanceId id, double fraction); //with Substance::uptake On Gradient

    /*!
    * @brief checks whether a position is outside of the organ (square)
    * @return true if outside
    */
    bool isOut(const CellCoord& coord) const;

    /*!
    * @brief calls the update functions of each cell
    */
    void update(sf::Time dt); //has to be named like that

    /*!
    * @brief updates the diffused Substance on ECM level of this CellsLayer
    */
    void updateCellsLayerAt(const CellCoord& pos, const Substance& diffusedSubst);

    /*!
    * @brief Getters for the Delta
    */
    double getDeltaVGEF() const;
    double getDeltaGlucose() const;
    double getDeltaBromo() const;

    /*!
    * @brief checker with polymorphic method in OrganCell Class
    * @return true if the OrganCell of this CellsLayer has Cancer
    */
    bool hasCancer() const;

    /*!
    * @brief Setter for a TumoralCell at the position of the CellsLayer
    */
    void setCancer();

    /*!
    * @brief Getter for ECM Cell
    */
    Cell* getECM() const;

    /*!
    * @brief checks whether it is possible for a cell to divide
    * @return true if the cell has successfully divide
    */
    bool requestToDivide(bool hasCancer);
};

#endif // CELLSLAYER_HPP
