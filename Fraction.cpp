//
//  Fraction.cpp
//  
//
//  Created by Stephen Beardslee on 2/8/16.
//
//


#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include "Fraction.hpp"

Fraction::Fraction(long n, long d)
{
    m_numerator = n;
    m_denominator = d;
    
    simplify();
}



void Fraction::set_Numerator( long n )
{
    m_numerator = n;
    simplify();
}

void Fraction::set_Denominator( long d )
{
    m_denominator = d;
    simplify();
}


void Fraction::simplify( void )
{
    
    long factor = labs((m_numerator > m_denominator) ? m_numerator : m_denominator);
    long devisor = labs((m_numerator > m_denominator) ? m_denominator : m_numerator);
    
    if ((factor>0) && (devisor>0))
    {   // Simplify fraction using Euclid's algorithm for finding largest common factor
        do
        {
            long remainder = factor % devisor;
            factor = devisor;
            devisor = remainder;
        } while (devisor > 0);

        m_numerator /= factor;
        m_denominator /= factor;
    }
    
    // TODO: Question - should we force -x/-y to be stored as x/y?
    //if (m_numerator < 0) && (m_denominator < 0))
    //{   // force both to positive
    //    m_numerator = labs(m_numerator);
    //    m_denominator = labs(m_denominator);
    //}
}

// returns string with numerator / denominator (e.g. "1/2")
const std::string Fraction::asString( void )
{
    std::stringstream outStream;
    
    if (isValid())
        outStream << numerator() << "/" << denominator();
    else
        outStream << "Nan";
    
    return std::string( outStream.str() );
}

// returns string with numerator / denominator (e.g. "1/2")
const std::string Fraction::asDoubleAsString( void )
{
    std::stringstream outStream;
    
    if (isValid())
        outStream << asDouble();
    else
        outStream << "Nan";
        
    return std::string( outStream.str() );
}

const double Fraction::asDouble( void )
{
    // if !isValid() (i.e. m_denominator == 0 will result in Nan
        return (double) m_numerator / (double) m_denominator;
}

// assume values stored in simplied form
const bool Fraction::operator==(const Fraction &f) const
{
    return (m_numerator == f.m_numerator) && (m_denominator == f.m_denominator);
}

const bool Fraction::operator!=(const Fraction &f) const
{
    return !(*this == f);
}

const bool Fraction::operator>(const Fraction &f) const
{
    long left = m_numerator * f.m_denominator;
    long right = f.m_numerator * m_denominator;
    
    return (left > right);
}

const bool Fraction::operator<(const Fraction &f) const
{
    long left = m_numerator * f.m_denominator;
    long right = f.m_numerator * m_denominator;
    
    return (left < right);
}

const bool Fraction::operator>=(const Fraction &f) const
{
    long left = m_numerator * f.m_denominator;
    long right = f.m_numerator * m_denominator;
    
    return (left >= right);
}

const bool Fraction::operator<=(const Fraction &f) const
{
    long left = m_numerator * f.m_denominator;
    long right = f.m_numerator * m_denominator;
    
    return (left <= right);
}

Fraction Fraction::operator+=(const Fraction &f)
{
    if (!isValid() || !f.isValid())
    {
        m_numerator = 0;
        m_denominator = 0;
    }
    else
    {
        m_numerator = (m_numerator * f.m_denominator) + (f.m_numerator * m_denominator);
        m_denominator = (m_denominator * f.m_denominator);
        simplify();
    }
    
    return *this;
}

Fraction Fraction::operator+(const Fraction &f)
{
    Fraction result( m_numerator, m_denominator );
    result += f;
    return result;
}

Fraction Fraction::operator-=(const Fraction &f)
{
    if (!isValid() || !f.isValid())
    {
        m_numerator = 0;
        m_denominator = 0;
    }
    else
    {
        m_numerator = (m_numerator * f.m_denominator) - (f.m_numerator * m_denominator);
        m_denominator = (m_denominator * f.m_denominator);
        simplify();
    }
    
    return *this;
}

Fraction Fraction::operator-(const Fraction &f)
{
    Fraction result( m_numerator, m_denominator );
    result -= f;
    return result;
}

Fraction Fraction::operator-(void)
{
    return Fraction( -m_numerator, m_denominator );
}

Fraction Fraction::operator*=(const Fraction &f)
{
    if (!isValid() || !f.isValid())
    {
        m_numerator = 0;
        m_denominator = 0;
    }
    else
    {
        m_numerator = (m_numerator * f.m_numerator);
        m_denominator = (m_denominator * f.m_denominator);
        simplify();
    }
    
    return *this;
}

Fraction Fraction::operator*(const Fraction &f)
{
    Fraction result( m_numerator, m_denominator );
    result *= f;
    return result;
}

Fraction Fraction::operator/=(const Fraction &f)
{
    if (!isValid() || !f.isValid())
    {
        m_numerator = 0;
        m_denominator = 0;
    }
    else
    {
        m_numerator = (m_numerator * f.m_denominator);
        m_denominator = (m_denominator * f.m_numerator);
        simplify();
    }
    
    return *this;
}

Fraction Fraction::operator/(const Fraction &f)
{
    Fraction result( m_numerator, m_denominator );
    result /= f;
    return result;
}