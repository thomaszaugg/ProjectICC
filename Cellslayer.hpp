#ifndef CELLSLAYER_HPP
#define CELLSLAYER_HPP
#include "Cell.hpp"
#include "Utility/Utility.hpp"
//#include "Organ.hpp"
#include "ECMCell.hpp"
#include "BloodCell.hpp"
#include "OrganCell.hpp"

//enum type for how many layers possible
enum Layers{
    SINGLE,
    TWO,
    THREE,
};

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
    virtual ~CellsLayer();
    //hierarchy

    bool hasECMCell();
    bool hasOrganCell();
    bool hasBloodCell();

    //kann nur assigned werden wenn vorher nullptr
    void setECMCell();
    void setOrganCell();
    void setBloodCell(TypeBloodCell type); //achtung default value

    //put Substance in ECM level -> ev. funktion in ECM aufrufen/ += operator
    void updateSubstance(Substance substance);

    //if the cell type asked for doesn't exist: either throw error or return 0(to be decided)
    double getECMQuantity(SubstanceId id); //amound not fractions
    double getOrganCellQuantity(SubstanceId id);
    double getBloodCellQuantity(SubstanceId id);

    void organCellTakeFormECM(SubstanceId id, double fraction); //with Substance::uptake On Gradient

};

#endif // CELLSLAYER_HPP
