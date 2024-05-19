#ifndef CELL_HPP
#define CELL_HPP
#include "SFML/System/Time.hpp"
#include "Substance.hpp"

class CellsLayer;

class Cell
{
private:

    /*!
    * @brief pointer to the CellLayer this Cell belongs to
    */
    CellsLayer* cellsLayer;

    /*!
    * @brief pointer to the Substance of this Cell
    */
    Substance* substance;

public:

    /*!
    * @brief Constructor
    */
    Cell(CellsLayer* ptr);

    /*!
    * @brief Destructor
    */
    virtual ~Cell();

    /*!
    * @brief adding of a Substance to the Substance of the Cell
    */
    void addSubstance(Substance newSubstance);

    /*!
    * @brief Getter
    * @return quantity of a Substance given by parameter
    */
    double getQuantitiy(SubstanceId id);

    /*!
    * @brief giving a part of the substance of this cell to the substance of another cell,
    *        using uptakeOnGradient function of Class Substance
    */
    void uptakeSubstance(double fraction, Cell* cellType, SubstanceId id);

    /*!
    * @brief taking a part of a substance from the donor cell given by parameter
    */
    void takeSubstance(double fraction, Cell* donour,SubstanceId id);

    /*!
    * @brief purely virtual update method, specified in the sub-classes
    */
    virtual void update(sf::Time dt)=0;

    /*!
    * @brief Getter
    * @return the CellLayer of this Cell
    */
    CellsLayer* getCellsLayer() const;

    /*!
    * @brief Getter
    * @return delta value of VGEF
    */
    double getDeltaVGEF() const;

    /*!
    * @brief Getter
    * @return delta value of Glucose
    */
    double getDeltaGlucose() const;

    /*!
    * @brief Getter
    * @return delta value of Bromopyruvate
    */
    double getDeltaBromo() const;

protected:

    /*!
    * @brief multiplication of a Substance, using update method of Substance Class
    */
    void multiplySubstance(SubstanceId id, double multiplier) const;

    /*!
    * @brief Getter
    * @return ECM Cell of the CellLayer this Cell belong to
    */
    Cell* getECM() const;


    bool requestToDivide(bool hasCancer);
};

#endif // CELL_HPP
