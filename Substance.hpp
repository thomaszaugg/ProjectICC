/*
 * prjsv 2016-2024
 * Marco Antognini
 * PROVIDED CORRECTION
 */
#pragma once

#include <Types.hpp>
#include <limits>
#include <iostream>


class Substance
{
	public:
	
	Substance();
    /*!
     * @brief constructs a substance using vgef, glucose and bormopyruvate quantities
     */
	Substance(double,double,double);

	Substance(const Substance&);

	~Substance();
    /*!
     * @brief add to this the quantities of other
     * (quantity by quantity)
     */
    Substance& operator+=(const Substance& other);

    Substance& operator=(const Substance& other);
    /*!
     * @brief deduce from this the quantities of other
     * (quantity by quantity)
     */
	Substance& operator-=(const Substance&);
    /*!
     * @brief returns the quantity of a given substance (VGEF, GLUCOSE or BROMOPYRUVATE)
     *
     */
	double operator[] (const SubstanceId) const;
    /*!
     * @brief returns the VGEF fraction (quantity / sum of all quantities)
     */
	double getFractVGEF() const {return m_fract_vgef;}
    /*!
     * @brief returns the GLUCOSE fraction (quantity / sum of all quantities)
     */
	double getFractGlucose() const {return m_fract_glucose;}
    /*!
     * @brief returns the BORMOPYRUVATE fraction (quantity / sum of all quantities)
     */
	double getFractInhibitor() const {return m_fract_bromopyruvate;}
    /*!
     * @brief returns the sum of all quantities
     */
	double getTotalConcentration() const {return m_total_concentration;}

    /*!
     * @brief multiplies by factor the quantity identied by id
     */
    void update(SubstanceId id, double factor);

    /*!
     * @brief return tue if all the quantities are zero up to SUBSTANCE_PRECISION
     */
	bool isNull() const;
	
    /*!
     * @brief takes a fraction of the product identified by id from this and adds it to receiver
     */
	void uptakeOnGradient(double fraction, Substance& receiver, SubstanceId id);
	
	private:
	double m_fract_vgef;
	double m_fract_glucose;
	double m_fract_bromopyruvate;
	
	double m_total_concentration;
	
};
double check(double, double minValue = 0.0);

/*!
 * @brief return val clamped between minValue and maxValue
 */
double check(double val, double minValue , double maxValue);
Substance operator*(const Substance&,double);
bool operator==(const Substance&, const Substance&);
bool operator!=(const Substance&,const Substance&);

std::ostream& operator<<(std::ostream&,const Substance&);

