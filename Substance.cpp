#include "Types.hpp"
#include <Env/Substance.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <iostream>
#include "Application.hpp"
#include <math.h>

Substance::Substance()
    :totalCon(.0), vgef(.0), glucose(.0), bromopyruvate(.0){}

Substance::Substance(double VGEF, double GLUCOSE, double BROMOPYRUVATE){
    setSubstance(VGEF, GLUCOSE, BROMOPYRUVATE);
}

void Substance::checkCon(double& con){
    if(con > getAppConfig().substance_max_value){
        con = getAppConfig().substance_max_value;
    }
    if(con < SUBSTANCE_PRECISION){
        con=0;
    }}

void Substance::setSubstance(double VGEF, double GLUCOSE, double BROMOPYRUVATE){
    checkCon(VGEF);
    checkCon(GLUCOSE);
    checkCon(BROMOPYRUVATE);
    totalCon=VGEF+GLUCOSE+BROMOPYRUVATE;

    if (totalCon != 0){
        vgef = VGEF/totalCon;
        glucose = GLUCOSE/totalCon;
        bromopyruvate = BROMOPYRUVATE/totalCon;
    }
    if ((*this).isNull()){
        totalCon = 0;
        vgef = 0;
        glucose = 0;
        bromopyruvate = 0;
    }}

double Substance::getFractVGEF(){
    return vgef;}

double Substance::getFractGlucose(){
    return glucose;}

double Substance::getFractInhibitor(){
    return bromopyruvate;}

double Substance::getTotalConcentration(){
    return totalCon;}

bool Substance::isNull(){
    return ((*this)[VGEF] < SUBSTANCE_PRECISION and (*this)[GLUCOSE]
            < SUBSTANCE_PRECISION and (*this)[BROMOPYRUVATE] < SUBSTANCE_PRECISION);
}

void Substance::operator=(const Substance& sub){
    totalCon=sub.totalCon;
    vgef=sub.vgef;
    glucose=sub.glucose;
    bromopyruvate=sub.bromopyruvate;
}

bool Substance::operator==(const Substance& other) const {
    return ((fabs((*this)[VGEF]-other[VGEF])< SUBSTANCE_PRECISION) && (fabs((*this)[GLUCOSE]-other[GLUCOSE])< SUBSTANCE_PRECISION)
            && (fabs((*this)[BROMOPYRUVATE]-other[BROMOPYRUVATE]) < SUBSTANCE_PRECISION));
}

bool Substance::operator!=(const Substance& other) const {
    return !(*this == other);
}

double Substance::operator[](const SubstanceId index) const{
    if (GLUCOSE == index){
        return glucose * totalCon;
    }
    if (VGEF == index){
        return vgef * totalCon;
    }
    if (BROMOPYRUVATE == index){
        return bromopyruvate * totalCon;
    }
    else {
        return -1;
    }
}

Substance& Substance::operator+=(const Substance& other){
    double vf((*this)[VGEF]+other[VGEF]);
    double glu((*this)[GLUCOSE]+other[GLUCOSE]);
    double bro((*this)[BROMOPYRUVATE]+other[BROMOPYRUVATE]);
    setSubstance(vf, glu, bro);
    return *this;
}

Substance& Substance::operator-=(const Substance& other){
    double vf((*this)[VGEF]-other[VGEF]);
    double glu((*this)[GLUCOSE]-other[GLUCOSE]);
    double bro((*this)[BROMOPYRUVATE]-other[BROMOPYRUVATE]);
    setSubstance(vf, glu, bro);
    return *this;
}

Substance& Substance::operator*(double scalar){
    totalCon*=scalar;
    setSubstance((*this)[VGEF], (*this)[GLUCOSE], (*this)[BROMOPYRUVATE]);
    return *this;
}

std::ostream& operator<<(std::ostream& print, const Substance& sub){
    print << "[VGEF] : " << sub[VGEF] << std::endl;
    print << "[GLUCOSE] : " << sub[GLUCOSE] << std::endl;
    print << "[BROMOPYRUVATE] : " << sub[BROMOPYRUVATE] << std::endl;
    return print;
}


void Substance::update(SubstanceId subId, double c){
    if(c<=EPSILON)   c=0;

    double vf((*this)[VGEF]);
    double glu((*this)[GLUCOSE]);
    double bro((*this)[BROMOPYRUVATE]);

    if (GLUCOSE == subId){
        glu*=c;
    }
    if (VGEF == subId){
        vf*=c;
    }
    if (BROMOPYRUVATE == subId){
        bro*=c;}

    setSubstance(vf, glu, bro);

    return;
}

void Substance::uptakeOnGradient(double fraction, Substance& receiver, SubstanceId id){
    double take=(*this)[id]*fraction;
    if(take< SUBSTANCE_PRECISION) return;

    update(id, (1-fraction));

    double quot((take/receiver[id])+1);    //calculates the multiplier for the function update

    receiver.update(id, quot);
}
