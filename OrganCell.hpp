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

    //Getters
    virtual double getFractGlu() const;
    virtual double getKrebsKm() const;
    virtual double getKrebsVmax() const;
    virtual double getFractUptake() const;//helper 2&3
    virtual double getDivisonEnergy() const;

    //helper division
    virtual double getMinNbCycles()const;
    virtual double getNbCyclesRange()const;

protected:
    //1
    void naturalLoss(sf::Time dt);

    //2&3 -> one method is enough if a parameter indicates which substance is added
    void uptakeFromECM();

    //4
    void ATPSynthesis(sf::Time dt);
    void glycolysis(sf::Time dt);
    void krebsCycle(sf::Time dt,double factor_glucoseUptake, double factor_inhibition=1.);

    //5
    void feedingLoss();

    //7
    void Division();


public:

    OrganCell(CellsLayer* cellsLayer);

    virtual ~OrganCell()=default;

    virtual void update(sf::Time dt) override;

    //6
    bool isDead();
    virtual bool hasCancer();

};

#endif // ORGANCELL_HPP
