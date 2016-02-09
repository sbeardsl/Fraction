//
//  Fraction.cpp
//  
//
//  Created by Stephen Beardslee on 2/8/16.
//
//


#include <iostream>
#include <sstream>
#include "Fraction.hpp"

// TODO: bigger list, how to handle values over max saved value?
// const list of primes


// this is a bounded solution, if we need to factor a value above out highest prime
// we fail to properly reduce the fraction...
static const long primes[] =
{
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    0
};

// const static long numPrimes = sizeof(primes)/sizeof(long);



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
    
    // now reduce fraction by common factors
    // we will walk the prime table from smallest to largest
    // reducing the numerator and denominator by common factors when we find them.
    // until we run out of primes or the next prime is larger than the smaller of our two values.
    long prime_index = 0;
    
    // TO TEST: with negative numerator
    // We don't have to test for common factors larger than the smallest of our values
    long max_possible_gcd = labs(m_numerator);
    if (m_denominator<max_possible_gcd)
        max_possible_gcd = m_denominator;
    
    while ((primes[prime_index] <= max_possible_gcd) && (primes[prime_index] > 0))
    {
        if ( ((m_numerator % primes[prime_index]) == 0) && ((m_denominator % primes[prime_index]) == 0) )
        {
            m_numerator = m_numerator / primes[prime_index];
            m_denominator = m_denominator / primes[prime_index];
            
            // leave prime index unchanged, try agian with same value
            // TODO: better way to do handle this?
            
            // if we have reduced our values, reset the max_possible_gcd
            if (labs(m_numerator)<max_possible_gcd)
                max_possible_gcd = labs(m_numerator);
            if (m_denominator<max_possible_gcd)
                max_possible_gcd = m_denominator;
        }
        else
            prime_index++; // TODO: bump up by prime numbers not not linear
    }
    
    // TODO: catch when we run past the end of our primes...

    standardize_values();
}

// enfore four constraints
// 1) if the denominator == 0, set it to 1 (and report and error somehow)
// 2) if one of the two values is negative, make sure its the numerator
// 3) if both values are negative, make both positive
// 4) if the numerator == 0, make the denominator == 1
void Fraction::standardize_values(void)
{
    if (m_denominator == 0)
    {
        // TODO: Error handling - Throw exception here?
        std::cout << "ERROR: Fraction with denominator == 0 [" << m_numerator << "/" << m_denominator <<"]\n";
        m_denominator = 1;
    }
        
    if (m_denominator < 0) // if denominator is negative
    {
        if (m_numerator > 0) // if d is negative but n is positive,
        {   // make the fraction negative by setting only the numerator to negative
            m_numerator = -labs(m_numerator);  // make the numerator negative
            m_denominator = labs(m_denominator);  // make denominator positive
        }
        else
        {   // // TODO: Error handling - Throw exception here?
            std::cout << "Warning: Fraction with two negative parts turn positive [" << m_numerator << "/" << m_denominator <<"]\n";
            // make both positive
            m_numerator = labs(m_numerator);  // make the numerator negative
            m_denominator = labs(m_denominator);  // make denominator positive
        }
    }
    
    if (m_numerator == 0)
        m_denominator = 1;
}


// returns string with numerator / denominator (e.g. "1/2")
const std::string Fraction::asString( void )
{
    std::stringstream outStream;
    
    outStream << numerator() << "/" << denominator();
    
    return std::string( outStream.str() );
}

// returns string with numerator / denominator (e.g. "1/2")
const std::string Fraction::asDoubleAsString( void )
{
    std::stringstream outStream;
    
    outStream << asDouble();
    
    return std::string( outStream.str() );
}

// assume values stored in simplied form
bool Fraction::operator==(Fraction &f)
{
    return (m_numerator == f.m_numerator) && (m_denominator == f.m_denominator);
}

bool Fraction::operator!=(Fraction &f)
{
    return !(*this == f);
}

bool Fraction::operator>(Fraction &f)
{
    long left = m_numerator * f.m_denominator;
    long right = f.m_numerator * m_denominator;
    
    return (left > right);
}

bool Fraction::operator<(Fraction &f)
{
    long left = m_numerator * f.m_denominator;
    long right = f.m_numerator * m_denominator;
    
    return (left < right);
}

bool Fraction::operator>=(Fraction &f)
{
    long left = m_numerator * f.m_denominator;
    long right = f.m_numerator * m_denominator;
    
    return (left >= right);
}

bool Fraction::operator<=(Fraction &f)
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