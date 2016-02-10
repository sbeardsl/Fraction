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

// TODO: bigger list, how to handle values over max saved value?
// const list of primes


// this is a bounded solution, if we need to factor a value above out highest prime
// we fail to properly reduce the fraction...
static const long init_primes[] =
{
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29
 // , 31, 37, 41, 43, 47, 53, 59, 61, 67, 71
};

const static long numPrimes = sizeof(init_primes)/sizeof(long);

const static std::vector<long> vPrimes( init_primes, &init_primes[numPrimes] );


// if both values are positive, fraction is positive
// if either values are negative, the fraction is negative
// we signal fraction is negative by making the numerator negative but NOT the denominator

// TODO: how to better handle case when both are negative?
Fraction::Fraction(long n, long d)
{
    m_numerator = n;
    m_denominator = d;
    
    standardize_values();
    
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


// reduce fraction to simplifiest common values
void Fraction::simplify( void )
{
    standardize_values();
    
    // now TRY to reduce the fraction by common factors
    // we will walk the prime table from smallest to largest
    // reducing the numerator and denominator by common factors when we find them.
    // until we run out of primes or the next prime is larger than the smaller of our two values.
    
    for( std::vector<long>::const_iterator iPrime = vPrimes.begin(); iPrime != vPrimes.end(); iPrime++ )
    {
        // If the current prime is larger than both our values, we are done
        if ( ((*iPrime) > m_numerator) && ((*iPrime) > m_denominator) )
            break;
        
        while ( ((m_numerator % (*iPrime)) == 0) && ((m_denominator % (*iPrime)) == 0) )
        {   // keep looping until current iPrime is no longer a common factor (e.g. 8 loops three times 2 * 2 * 2 )
            m_numerator = m_numerator / (*iPrime);
            m_denominator = m_denominator / (*iPrime);
        }
    }
    
    // Note: if we try to factor values larger than our largest prime
    // we leave the fraction with a valid but not fully simplified value.
    // the math will continue to work but the displayed numerator & denominator will not be as expected.

    standardize_values();
}

// enfore constraints
// 2) if one of the two values is negative, make sure its the numerator
// 3) if both values are negative, make both values positive
// 4) if the numerator == 0, make the denominator == 1
void Fraction::standardize_values(void)
{
    if (!isValid())
    {   // if Fraction is not valid, force numerator to 0
        m_numerator = 0;
        return;
    }
        
    if ((m_denominator < 0) && (m_numerator < 0))
    {
        if (m_numerator >= 0) // if d is negative but n is NOT negative,
        {   // make the fraction negative by setting only the numerator to negative
            m_numerator = -labs(m_numerator);  // make the numerator negative
            m_denominator = labs(m_denominator);  // make denominator positive
        }
        else
        {
            // make both positive
            m_numerator = labs(m_numerator);  // make the numerator negative
            m_denominator = labs(m_denominator);  // make denominator positive
        }
    }
    
    if (isValid() && (m_numerator == 0))
        m_denominator = 1;
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
    m_numerator = (m_numerator * f.m_denominator) + (f.m_numerator * m_denominator);
    m_denominator = (m_denominator * f.m_denominator);
    simplify();
    
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
    m_numerator = (m_numerator * f.m_denominator) - (f.m_numerator * m_denominator);
    m_denominator = (m_denominator * f.m_denominator);
    simplify();
    
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
    m_numerator = (m_numerator * f.m_numerator);
    m_denominator = (m_denominator * f.m_denominator);
    simplify();
    
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
    m_numerator = (m_numerator * f.m_denominator);
    m_denominator = (m_denominator * f.m_numerator);
    simplify();
    
    return *this;
}

Fraction Fraction::operator/(const Fraction &f)
{
    Fraction result( m_numerator, m_denominator );
    result /= f;
    return result;
}