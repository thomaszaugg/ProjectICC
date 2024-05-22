#ifndef ECMCELL_HPP
#define ECMCELL_HPP
#include "Cell.hpp"

class CellsLayer;

class ECMCell : public Cell
{
public:

    /*!
    * @brief Constructor of the ECM Cell
    */
    ECMCell(CellsLayer* cellsLayer);

    /*!
    * @brief update function: empty body, since ECM Cells do not change over time
    */
    virtual void update(sf::Time dt) override;

    /*!
    * @brief default destructor
    */
    ~ECMCell()=default;
};

#endif // ECMCELL_HPP
