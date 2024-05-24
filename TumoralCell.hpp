#ifndef TUMORALCELL_HPP
#define TUMORALCELL_HPP
#include "OrganCell.hpp"


class TumoralCell : public OrganCell
{
private:

    /*!
    * @brief polymorphic getters
    */
    virtual double getFractUptake() const override;
    virtual double getKrebsKm() const override;
    virtual double getKrebsVmax() const override;
    virtual double getFractGlu() const override;
    virtual double getDivisonEnergy() const override;

    /*!
    * @brief polymorphic getters for the division
    */
    virtual double getMinNbCycles()const override;
    virtual  double getNbCyclesRange()const override;

public:

    /*!
    * @brief Constructor
    */
    TumoralCell(CellsLayer* cellsLayer);

    /*!
    * @brief Destructor
    */
    ~TumoralCell()=default;

    /*!
    * @brief polymorphic boolean function indicating whether the Cell has Cancer
    * @return true
    */
    virtual bool hasCancer() override;

protected:

    /*!
    * @brief polymorphic method calling the helper functions : glycolysis
    */
    virtual void ATPSynthesis(sf::Time dt) override;
};

#endif // TUMORALCELL_HPP
