#ifndef ORGANCELL_HPP
#define ORGANCELL_HPP
#include "Cell.hpp"

class CellsLayer;

class OrganCell : public Cell
{
private:

    double atp; //energylevel of a cell
    double N; //for cell divison
    int counter;

    /*!
    * @brief polymorphic getters
    */
    virtual double getFractGlu() const;
    virtual double getKrebsKm() const;
    virtual double getKrebsVmax() const;
    virtual double getFractUptake() const;//helper 2&3
    virtual double getDivisonEnergy() const;

    /*!
    * @brief polymorphic getters for the division
    */
    virtual double getMinNbCycles()const;
    virtual double getNbCyclesRange()const;

    /*!
    * @brief calculation of atp gain during krebs cycle
    */
    void pathway_atp_production(sf::Time dt,double factor_glucoseUptake, double factor_inhibition=1.);

    /*!
    * @brief loss of atp while eating, attribut updated within this method
    */
    void feedingLoss();

    /*!
    * @brief Divison of a Cell
    */
    void Division();

    /*!
    * @brief natural loss of atp, attribut is updated within this method
    */
    void naturalLoss(sf::Time dt);

    /*!
    * @brief uptake of Glucose and Bromopyruvate from ECM cell, using take Substance method of Cell class
    */
    void uptakeFromECM();

protected:

    /*!
    * @brief polymorphic method calling the helper functions : glycolysis & pathway_atp_production
    */
    virtual void ATPSynthesis(sf::Time dt);

    /*!
    * @brief calculation of atp gain during glycolysis
    */
    void glycolysis(sf::Time dt);

public:
    /*!
    * @brief Constructor
    */
    OrganCell(CellsLayer* cellsLayer);

    /*!
    * @brief Default destructor
    */
    virtual ~OrganCell()=default;

    /*!
    * @brief updating the OrganCell, use of multiple helperfuctions in protected part of this class
    */
    virtual void update(sf::Time dt) override;

    /*!
    * @brief checking if atp level is below zero
    * @return true if the atp < 0, which means that the cell is dead
    */
    bool isDead();

    /*!
    * @brief polymorphic boolean function indicating whether the Cell has Cancer
    * @return false
    */
    virtual bool hasCancer();

};

#endif // ORGANCELL_HPP
