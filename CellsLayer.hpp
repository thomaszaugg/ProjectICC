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
    CellCoord position; //position in Organ
    Organ* organ; //damit die Zellen ihre Nachbaren finden können

    //nullptr if not present
    ECMCell* ecm;
    OrganCell* organCell;
    BloodCell* bloodCell;


public:
    CellsLayer(CellCoord position, Organ* organ);
    virtual ~CellsLayer(); //why virtual
    //hierarchy

    bool hasECMCell();
    bool hasOrganCell();
    bool hasBloodCell();

    //kann nur assigned werden wenn vorher nullptr
    void setECMCell();
    void setOrganCell();
    void setBlood(TypeBloodCell type); //achtung default value

    //put Substance in ECM level -> ev. funktion in ECM aufrufen/ += operator
    void updateSubstance(Substance substance);

    //if the cell type asked for doesn't exist: either throw error or return 0(to be decided)
    double getECMQuantity(SubstanceId id); //amound not fractions
    double getOrganCellQuantity(SubstanceId id);
    double getBloodCellQuantity(SubstanceId id);

    CellCoord getPosition() const;

    void organCellTakeFromECM(SubstanceId id, double fraction); //with Substance::uptake On Gradient

    bool isOut(const CellCoord& coord);

    Cell* topCell();

    void update(sf::Time dt); //has to be named like that
    void updateCellsLayerAt(const CellCoord& pos, const Substance& diffusedSubst);

    double getDeltaVGEF() const;
    double getDeltaGlucose() const;
    double getDeltaBromo() const;

    bool hasCancer();

    void setCancer();

    Cell* getECM() const;

    //helper divison
    bool requestToDivide(bool hasCancer);
};

#endif // CELLSLAYER_HPP
