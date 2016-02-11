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

// Choice: use longs to store values, no floating point values
// Choice: always store values in fully reduced form

class Fraction
{
public:
    // initalize
    Fraction(long n, long d);
    
    // Fraction is not valid if denominator == 0
    const bool isValid( void ) const { return m_denominator != 0; }
    
    // display
    const std::string asString( void ); // "1/2"
    const std::string asDoubleAsString( void ); // ".5"
    const double asDouble( void );
    
    // typecast
    operator double(){ return asDouble(); }
    operator std::string(){ return asString(); }
    
    // access elements
    const long numerator( void ){ return m_numerator; }
    const long denominator( void ){ return m_denominator; }
    
    void set_Numerator( long n );       // To DO: Do we want these?
    void set_Denominator( long d );

    // equality operators
    const bool operator==( const Fraction &f) const;
    const bool operator!=( const Fraction &f) const;
    
    // comparison
    const bool operator<(const Fraction &f)const;
    const bool operator>(const Fraction &f)const;
    const bool operator<=(const Fraction &f)const;
    const bool operator>=(const Fraction &f)const;

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
    void simplify( void ); // reduce fraction by largest common factors
    
    long m_numerator;
    long m_denominator;
};

#endif /* Fraction_hpp */
