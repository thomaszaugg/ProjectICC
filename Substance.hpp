#include "Types.hpp"
#include <iostream>
#pragma once

class Substance{
private:
    double totalCon;
    //the 3 possible substances in the ECM:

    double vgef;                //Vascular Endothelial Growth Factor
    double glucose;
    double bromopyruvate;

    /*!
    * @brief Sets the fractions and the values in the bounderies
    */
    void setSubstance(double VGEF, double GLUCOSE, double BROMOPYRUVATE);

    /*!
    * @brief Sets the concentration in the correct boundary
    */
    void checkCon(double& con);

public:
    /*!
    * @brief Constructor by default
    */
    Substance();

    /*!
    * @brief Constuctor, including the initialization of the total Concentration and checks the values
    */
    Substance(double VGEF, double GLUCOSE, double BROMOPYRUVATE);

    /*!
    * @brief Default Copy Constructor & Destructor
    */
    Substance(const Substance& sub)=default;
    ~Substance()=default;

    /*!
    * @brief Getters
    */
    double getFractVGEF();
    double getFractGlucose();
    double getFractInhibitor();
    double getTotalConcentration();

    /*!
    * @brief checks if the concentrations of the substances is equal to zero (up to substance precision)
    *
    * @return returns true if they are equal to zero
    */
    bool isNull();

    /*!
    * @brief sets one substance as the other
    */
    void operator=(const Substance& sub);

    /*!
    * @brief checks if two substances are equal or not (up to substance precision)
    */
    bool operator==(const Substance& other) const;
    bool operator!=(const Substance& other) const;

    /*!
    * @brief operator to access the concentration of a SubstanceId
    *
    * @return concentration of the asked SubstanceId
    */
    double operator[](const SubstanceId index) const;

    /*!
    * @brief basic arithmetic operations in the Substance class
    *
    * @return Substance passed by reference
    */
    Substance& operator+=(const Substance& other);
    Substance& operator-=(const Substance& other);
    Substance& operator*(double scalar);

    /*!
    * @brief mulitply the quantity of a substance by c
    */
    void update(SubstanceId subId, double c);

    /*!
    * @brief updates the concentration of a receiver
    */
    void uptakeOnGradient(double fraction, Substance& receiver, SubstanceId id);

};

/*!
* @brief to cout the concentrations of a Substance
*/
std::ostream& operator<<(std::ostream& print, const Substance& sub);
