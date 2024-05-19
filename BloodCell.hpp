#ifndef BLOODCELL_HPP
#define BLOODCELL_HPP
#include "Cell.hpp"
#include "Types.hpp"
#include "Utility/Utility.hpp"


class CellsLayer;

class BloodCell: public Cell
{
private:
    TypeBloodCell type;

    /*!
    * @brief second part of update method, updating the concentration of one blood cell
    */
    void update(CellCoord const& pos_bloodcell, CellCoord const& pos_ecm_cell, Substance c0, double const& D, sf::Time  dt);

public:

    /*!
    * @brief Constructor
    */
    BloodCell(CellsLayer* cellslayer, TypeBloodCell type);

    /*!
    * @brief first part of update method, reading of constants and iterating trought the blood Cells in the diffusion radius
    */
    virtual void update(sf::Time dt) override;



};

#endif // BLOODCELL_HPP
