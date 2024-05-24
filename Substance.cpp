#include <algorithm>
#include <Env/Substance.hpp>
#include <Utility/Utility.hpp>
#include <Utility/Constants.hpp>
#include <iostream>
#include <Application.hpp>



Substance::Substance() :
    m_fract_vgef(0.0),
    m_fract_glucose(0.0),
    m_fract_bromopyruvate(0.0),
    m_total_concentration(0)
{
}

Substance::Substance(double v, double g,double i) :
    m_fract_vgef(check(v)),
    m_fract_glucose(check(g)),
    m_fract_bromopyruvate(check(i))

{
    m_total_concentration = m_fract_vgef+m_fract_glucose+m_fract_bromopyruvate;

    if 	(!isEqual(m_total_concentration, 0, SUBSTANCE_PRECISION))
    {
        m_fract_vgef /= m_total_concentration;
        m_fract_glucose /= m_total_concentration;
        m_fract_bromopyruvate  /= m_total_concentration;
    }
    else
    {
        m_fract_vgef = 0;
        m_fract_glucose = 0;
        m_fract_bromopyruvate = 0;
    }

}
Substance::Substance(const Substance& n) :
    m_fract_vgef(n.getFractVGEF()),
    m_fract_glucose(n.getFractGlucose()),
    m_fract_bromopyruvate(n.getFractInhibitor()),
    m_total_concentration(n.getTotalConcentration())
{
}


Substance& Substance::operator = (const Substance& n)
{
    m_fract_vgef = n.getFractVGEF();
    m_fract_glucose = n.getFractGlucose();
    m_fract_bromopyruvate = n.getFractInhibitor();
    m_total_concentration = n.getTotalConcentration();
    return (*this);
}

Substance::~Substance()
{
}

double Substance::operator [] (const SubstanceId n) const
{
    switch(n)
    {
    case VGEF : return m_total_concentration*m_fract_vgef;
    case GLUCOSE : return m_total_concentration*m_fract_glucose;
    case BROMOPYRUVATE : return m_total_concentration*m_fract_bromopyruvate;
    default : return -1.0;
    }
}



Substance operator*(const Substance& n, double c)
{
    double temp_vgef = n[VGEF]*c;
    double temp_glucose = n[GLUCOSE]*c;
    double temp_bromopyruvate = n[BROMOPYRUVATE]*c;
    Substance temp(temp_vgef,temp_glucose,temp_bromopyruvate);

    return temp;
}

Substance& Substance::operator +=(const Substance& rhs)
{

    double temp_vgef = check(m_fract_vgef*m_total_concentration + rhs[VGEF]);
    double temp_glucose = check(m_fract_glucose*m_total_concentration + rhs[GLUCOSE]);
    double temp_bromopyruvate = check(m_fract_bromopyruvate*m_total_concentration + rhs[BROMOPYRUVATE]);
    double temp_total = (temp_glucose+temp_vgef+temp_bromopyruvate);
    if ((!isEqual(temp_total, 0, SUBSTANCE_PRECISION)))
    {
        m_fract_vgef = (temp_vgef)/temp_total;
        m_fract_glucose = (temp_glucose)/temp_total;
        m_fract_bromopyruvate = (temp_bromopyruvate)/temp_total;
        m_total_concentration = temp_total;
    }
    else
    {
        m_fract_vgef = 0;
        m_fract_glucose = 0;
        m_fract_bromopyruvate = 0;
        m_total_concentration = 0;
    }
    return (*this);
}

Substance& Substance::operator -= (const Substance& rhs)
{
    double temp_vgef = check(m_fract_vgef*m_total_concentration - rhs[VGEF]);
    double temp_glucose = check(m_fract_glucose*m_total_concentration - rhs[GLUCOSE]);
    double temp_bromopyruvate = check(m_fract_bromopyruvate*m_total_concentration - rhs[BROMOPYRUVATE]);
    double temp_total = (temp_glucose+temp_vgef+temp_bromopyruvate);
    if ((!isEqual(temp_total, 0, SUBSTANCE_PRECISION)))
    {
        m_fract_vgef = (temp_vgef)/temp_total;
        m_fract_glucose = (temp_glucose)/temp_total;
        m_fract_bromopyruvate = (temp_bromopyruvate)/(temp_total);
        m_total_concentration = temp_total;
    }
    else
    {
        m_fract_vgef = 0;
        m_fract_glucose = 0;
        m_fract_bromopyruvate = 0;
        m_total_concentration = 0;
    }
    return (*this);
}

void Substance::update(SubstanceId f, double c)
{
    double temp_glucose = m_total_concentration*m_fract_glucose;
    double temp_bromopyruvate = m_total_concentration*m_fract_bromopyruvate;
    double temp_vgef = m_total_concentration*m_fract_vgef;
    double temp_total =0;
    switch(f)
    {
    case GLUCOSE :
        if (isEqual(c, 0, EPSILON)){
            temp_glucose = 0;
        }
        else
            temp_glucose *=c;
        break;
    case BROMOPYRUVATE :
        if (isEqual(c, 0, EPSILON)){
            temp_bromopyruvate = 0;
        }
        else
            temp_bromopyruvate *=c;
        break;
    case VGEF :
        if (isEqual(c, 0, EPSILON)){
            temp_vgef = 0;
        }
        else temp_vgef *=c;
        break;
    default: /*nothing to do*/
        break;
    }

    temp_glucose = check(temp_glucose);
    temp_bromopyruvate = check(temp_bromopyruvate);
    temp_vgef = check(temp_vgef);
    temp_total = temp_glucose + temp_bromopyruvate + temp_vgef;

    if (!isEqual(temp_total, 0, SUBSTANCE_PRECISION))
    {
        m_fract_vgef = (temp_vgef)/temp_total;
        m_fract_glucose = (temp_glucose)/temp_total;
        m_fract_bromopyruvate = (temp_bromopyruvate)/temp_total;
        m_total_concentration = temp_total;
    }

    else {
        m_fract_vgef = 0;
        m_fract_glucose = 0;
        m_fract_bromopyruvate = 0;
        m_total_concentration = 0;
    }

}



std::ostream& operator<<(std::ostream& out,const Substance& s)
{
    out << "[VGEF] = " << s[VGEF] << "\n"
        << "[GLUCOSE] = " << s[GLUCOSE] << "\n"
        << "[BROMOPYRUVATE] = " << s[BROMOPYRUVATE] << "\n";
    return out;
}

bool operator==(const Substance& lhs,const Substance& rhs)
{
    return  isEqual(lhs[VGEF], rhs[VGEF], SUBSTANCE_PRECISION)
           &&
           isEqual(lhs[BROMOPYRUVATE], rhs[BROMOPYRUVATE], SUBSTANCE_PRECISION)
           &&
           isEqual (lhs[GLUCOSE], rhs[GLUCOSE], SUBSTANCE_PRECISION);
}

bool operator!=(const Substance& lhs,const Substance& rhs)
{
    return !(rhs==lhs);
}

double check(double value, double minValue, double maxValue)
{
    value = std::max(minValue, value);
    value = std::min(value, maxValue);

    if (value < SUBSTANCE_PRECISION) return 0.;
    return value;
}

double check(double value, double minValue)
{
    return check(value, minValue, getAppConfig().substance_max_value);
}

void Substance::uptakeOnGradient(double fraction, Substance& receiver, SubstanceId i)
{
    //assert(fraction > 0 && fraction < 1);

    if ((*this)[i] < SUBSTANCE_PRECISION) { // to avoid floating point issues
        return;
    }
    Substance temp;
    switch(i)
    {
    case GLUCOSE : temp = Substance(0,(fraction)*((*this)[i]),0);break;
    case BROMOPYRUVATE : temp = Substance(0,0,(fraction)*((*this)[i]));break;
    case VGEF : temp = Substance((fraction)*((*this)[i]),0,0);break;
    default   : /*nothing to do*/ break;
    }
    receiver+=temp;
    Substance temp2 = (*this);
    temp2.update(i,1-fraction);
    (*this) -= temp;
}

bool Substance::isNull() const
{
    return ( (m_fract_vgef*m_total_concentration < SUBSTANCE_PRECISION)
            &&
            (m_fract_glucose*m_total_concentration < SUBSTANCE_PRECISION)
            &&
            (m_fract_bromopyruvate * m_total_concentration < SUBSTANCE_PRECISION));
}
