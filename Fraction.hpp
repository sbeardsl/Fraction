//
//  Fraction.hpp
//  
//
//  Created by Stephen Beardslee on 2/8/16.
//
//

#ifndef Fraction_hpp
#define Fraction_hpp

#include <stdio.h>
#include <string>

// ALWAYS store fraction in simplified form

// TODO Question: Do we want to allow setting of numerator/denominator individually
// TODO Question: How to handle situation when both part of fraction are negative
// TODO: get longer list of primes, handle values larger than list of primes in some way

// Choice: use longs to store values, no floating point values
// Choice: set denominator to 1 when numerator == 0
// Choice: always store values in fully reduced form
// Choice: always make the numerator negative for negative fractions, never the denominator

class Fraction
{
public:
    // initalize
    Fraction(long n, long d);
    
    // display
    const std::string asString( void ); // "1/2"
    const std::string asDoubleAsString( void ); // ".5"
    const double asDouble( void ){ return ( (double) m_numerator / (double) m_denominator ); }
    
    // access elements
    const long numerator( void ){ return m_numerator; }
    const long denominator( void ){ return m_denominator; }
    
    void set_Numerator( long n );       // do we want these?
    void set_Denominator( long d );

    // equality operators
    bool operator==(Fraction &f);
    bool operator!=(Fraction &f);
    
    // comparison
    bool operator<(Fraction &f);
    bool operator>(Fraction &f);
    bool operator<=(Fraction &f);
    bool operator>=(Fraction &f);

    // math functions
    Fraction operator+=(const Fraction &f);
    Fraction operator+(const Fraction &f);
    
    Fraction operator-=(const Fraction &f);
    Fraction operator-(const Fraction &f);
    Fraction operator-(void);
    
    Fraction operator*=(const Fraction &f);
    Fraction operator*(const Fraction &f);
    
    Fraction operator/=(const Fraction &f);
    Fraction operator/(const Fraction &f);
    
private:
    void simplify( void ); // reduce fraction to simplifiest common values
    
    // enfore four constraints
    // 1) if the denominator == 0, set it to 1 (and report and error somehow)
    // 2) if one of the two values is negative, make sure its the numerator
    // 3) if both values are negative, make both positive
    // 4) if the numerator == 0, make the denominator == 1
    void standardize_values( void );
    
    long m_numerator;
    long m_denominator;
};

#endif /* Fraction_hpp */