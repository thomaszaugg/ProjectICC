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
    virtual void uptakeFromECM();


    //4
   virtual  void ATPSynthesis(sf::Time dt);

    //5
    void feedingLoss();

    //6
    bool isDead();

    //7
    virtual void Division();
    void canDivide();

    virtual bool hasCancer();

protected:
       virtual double getKrebsKm() const;
       virtual double getKrebsVmax() const;
    virtual double getFractUptake();
   protected: void glycolysis(sf::Time dt);

    //helper ATP
private:
        void ATP(sf::Time dt,double factor_glucoseUptake, double factor_inhibition=1.); //lisa i bruche no ne bessere name
    virtual double getFractGlu() const;
};

#endif // ORGANCELL_HPP
