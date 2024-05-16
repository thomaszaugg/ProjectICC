#ifndef ORGANCELL_HPP
#define ORGANCELL_HPP
#include "Cell.hpp"

class CellsLayer;

class OrganCell : public Cell
{
private:

    double atp; //energylevel of a cell

public:
    OrganCell(CellsLayer* cellsLayer);

    virtual void update(sf::Time dt) override;

    //1
    void naturalLoss(sf::Time dt);

    //2&3 -> one method is enough if a parameter indicates which substance is added
    virtual void uptakeSubstance();
    virtual double getFractUptake();

    //4
    virtual void ATPSynthesis();

    //5
    void feedingLoss();

    //6
    bool isDead();

    //7
    virtual void Division();
    void canDivide();

    virtual bool hasCancer();
};

#endif // ORGANCELL_HPP
