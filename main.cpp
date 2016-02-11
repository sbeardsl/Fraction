//
//  main.cpp
//  Fraction
//
//  Created by Stephen Beardslee on 2/8/16.
//  Copyright © 2016 Stephen Beardslee. All rights reserved.
//

#include <iostream>

#include "fraction.hpp"

static void ReportFraction( std::string sName, std::string sDescription, Fraction f );
static void ReportEqual( std::string sName, bool bShouldMatch, Fraction f1, Fraction f2 );
static void ReportGreaterThan( std::string sName, bool bShouldBeGreater, Fraction f1, Fraction f2 );
static void ReportValid( std::string sName, bool bShouldBeValid, Fraction f );

static void TestCreation( void );
static void TestEquality( void );
static void TestAdd( void );
static void TestSub( void );
static void TestMult( void );
static void TestDivide( void );
static void TestCompare( void );
static void TestInvalid( void );
static void TestTypecast( void );

int main(int argc, const char * argv[])
{
    TestCreation();
    TestEquality();
    TestAdd();
    TestSub();
    TestMult();
    TestDivide();
    TestCompare();
    TestInvalid();
    TestTypecast();
    
    return 0;
}

void ReportFraction( std::string sName, std::string sDescription, Fraction f )
{
    bool bPassed = (sDescription == f.asString());
    
    if (bPassed)
        std::cout << sName << " Pass: " << f.asString() << "\n";
    else
        std::cout << sName << " =FAIL=: " << f.asString() << " should be " << sDescription << "\n";
}

void ReportEqual( std::string sName, bool bShouldMatch, Fraction f1, Fraction f2 )
{
    bool bDoMatch = (f1 == f2);
    
    if (bDoMatch == bShouldMatch)
    {
        if (bDoMatch)
            std::cout << sName << " Pass: " << f1.asString() << " == " << f2.asString() << "\n";
        else
            std::cout << sName << " Pass: " << f1.asString() << " != " << f2.asString() << "\n";
    }
    else
    {
        if (bDoMatch)
            std::cout << sName << " =FAIL=: " << f1.asString() << " should NOT match " << f2.asString() << "\n";
        else
            std::cout << sName << " =FAIL=: " << f1.asString() << " SHOULD match " << f2.asString() << "\n";
    }
}

void ReportGreaterThan( std::string sName, bool bShouldF1BeGreater, Fraction f1, Fraction f2 )
{
    bool bF1IsGreater = (f1 > f2);
    
    if (bF1IsGreater == bShouldF1BeGreater)
    {
        if (bShouldF1BeGreater)
            std::cout << sName << " Pass: " << f1.asString() << " > " << f2.asString() << "\n";
        else
            std::cout << sName << " Pass: " << f1.asString() << " <= " << f2.asString() << "\n";
    }
    else
    {
        if (bF1IsGreater)
            std::cout << sName << " =FAIL=: " << f1.asString() << " should NOT be greater than " << f2.asString() << "\n";
        else
            std::cout << sName << " =FAIL=: " << f1.asString() << " SHOULD be greater than " << f2.asString() << "\n";
    }
}

void ReportValid( std::string sName, bool bShouldBeValid, Fraction f )
{
    if (f.isValid() == bShouldBeValid)
    {
        if (bShouldBeValid)
            std::cout << sName << " Pass: valid\n";
        else
            std::cout << sName << " Pass: invalid\n";
    }
    else
    {
        if (bShouldBeValid)
            std::cout << sName << " =FAIL=: should be valid but in invalid\n";
        else
            std::cout << sName << " =FAIL=: should be invalid but is valid\n";
    }
}

void TestCreation( void )
{
    std::cout << "\n=== TestCreation\n";
    
    Fraction f1(1,1);
    ReportFraction( " f1", "1/1", f1 );
    
    Fraction f2(2,2);
    ReportFraction( " f2", "1/1", f2 );
    
    Fraction f3(2,4);
    ReportFraction( " f3", "1/2", f3 );
    
    Fraction f4(4,2);
    ReportFraction( " f4", "2/1", f4 );
    
    Fraction f5(2,5);
    ReportFraction( " f5", "2/5", f5 );
    
    Fraction f6(3,9);
    ReportFraction( " f6", "1/3", f6 );
    
    Fraction f7(9,3);
    ReportFraction( " f7", "3/1", f7 );
    
    Fraction f8(27,9);
    ReportFraction( " f8", "3/1", f8 );
    
    Fraction f9(9,27);
    ReportFraction( " f9", "1/3", f9 );
    
    Fraction f10(-9,27);
    ReportFraction( "f10", "-1/3", f10 );
    
    Fraction f11(-27,9);
    ReportFraction( "f11", "-3/1", f11 );
    
    Fraction f12(3*5*11*17,5*11*17+1);
    ReportFraction( "f12", "935/312", f12 );
    
    Fraction f13(3*5*11*17,5*11*17);
    ReportFraction( "f13", "3/1", f13 );
    
    Fraction fZero( 1, 0);
    ReportFraction( "fZero", "Nan", fZero);
    
    Fraction two_neg( -5, -2 );  // now defined a positive
    ReportFraction( "f_2Neg", "-5/-2", two_neg);
}

void TestEquality( void )
{
    std::cout << "\n=== TestEquality\n";
    
    Fraction f1( 1, 1);
    Fraction f2( 2, 1);
    Fraction f3( 2, 2);
    Fraction f4( -2, 2);
    Fraction f5( -4, 4);
    
    ReportEqual( " e1", true, f1, f1 );
    ReportEqual( " e2", true, f2, f2 );
    ReportEqual( " e3", true, f3, f3 );
    ReportEqual( " e4", true, f4, f4 );
    
    ReportEqual( " e5", false, f1, f2 );
    ReportEqual( " e6", true, f1, f3 );
    ReportEqual( " e7", false, f1, f4 );
    ReportEqual( " e8", true, f4, f5 );
}


static void TestCompare( void )
{
    std::cout << "\n=== TestCompare\n";
    
    Fraction f1( 1, 1);
    Fraction f2( 2, 1);
    ReportGreaterThan( " c1", false, f1, f2 );
    ReportGreaterThan( " c2", true, f2, f1 );
    
    f1 = Fraction( -1, 2 );
    ReportGreaterThan( " c3", false, f1, f2 );
    ReportGreaterThan( " c4", true, f2, f1 );

	f1 = Fraction(-1, 2);
	ReportGreaterThan(" c5", false, f1, f1);
	ReportGreaterThan(" c6", false, f1, f1);
	
	f2 = Fraction(-2, 2);
	ReportGreaterThan(" c5", true, f1, f2);
	ReportGreaterThan(" c6", false, f2, f1);
}

static void TestAdd( void )
{
    std::cout << "\n=== TestAdd\n";
 
    // += and +
    std::cout << "\n=== Test +=\n";
    Fraction f1( 1, 1);
    Fraction f2( 2, 4);
    f1 += f2;
    ReportFraction( " a1", "3/2", f1 );
    
    f1 += Fraction( 1, 2 );
    ReportFraction( " a2", "2/1", f1 );
    
    f1 += Fraction( -1, 2 );
    ReportFraction( " a3", "3/2", f1 );
    
    f1 += Fraction( -3, 2 );
    ReportFraction( " a4", "0/4", f1 );
    
    f1 += Fraction( 1, 1 );
    ReportFraction( " a5", "1/1", f1 );
    
    f1 += Fraction( -1, 1 );
    ReportFraction( " a6", "0/1", f1 );
    
    f1 += Fraction( -1, 1 );
    ReportFraction( " a7", "-1/1", f1 );
    
    std::cout << "\n=== Test +\n";
    
    f2 = Fraction( 1, 1) + Fraction( 1, 1 );
    ReportFraction( " a8", "2/1", f2 );
    
    f1 = Fraction( 1, 1 );
    f2 = f1 + f1;
    ReportFraction( " a9", "2/1", f2 );
    
    f2 = Fraction( 1, 1) + f1;
    ReportFraction( "a10", "2/1", f2 );
    
    f1 = Fraction( -1 , 1 );
    f2 = Fraction( 0, 1 ) + f1;
    ReportFraction( "a11", "-1/1", f2 );
    
    f2 = f1 + f1 + f1 + f1;
    ReportFraction( "a12", "-4/1", f2 );
    
    Fraction f3 = f2 + f1;
    ReportFraction( "a13", "-5/1", f3 );
    
    f3 = f3 + Fraction( 10, 25 );
    ReportFraction( "a14", "-23/5", f3 );
    
    f3 = Fraction( 5, 6 ) + Fraction( 6, 5 );
    ReportFraction( "a15", "61/30", f3 );
    
    
}

static void TestSub( void )
{
    std::cout << "\n=== TestSub\n";
    
    // += and +
    std::cout << "\n=== Test -=\n";
    Fraction f1( 1, 1);
    Fraction f2( 2, 4);
    f1 -= f2;
    ReportFraction( " s1", "1/2", f1 );
    
    f1 -= Fraction( 1, 2 );
    ReportFraction( " s2", "0/4", f1 );
    
    f1 -= Fraction( -1, 2 );
    ReportFraction( " s3", "1/2", f1 );
    
    f1 -= Fraction( -3, 2 );
    ReportFraction( " s4", "2/1", f1 );
    
    f1 -= Fraction( 1, 1 );
    ReportFraction( " s5", "1/1", f1 );
    
    f1 -= f1;
    ReportFraction( " s6", "0/1", f1 );
    
    f1 -= Fraction( 1, 4 );
    ReportFraction( " s6a", "-1/4", f1 );
    
    std::cout << "\n=== Test -\n";
    
    f2 = Fraction( 5, 2 ) - Fraction( 1, 2 );
    ReportFraction( " s7", "2/1", f2 );
    
    f2 = Fraction( 1, 2) - Fraction( 5, 2 );
    ReportFraction( " s8", "-2/1", f2 );
    
    f1 = Fraction( 1, 1 );
    f2 = f1 - f1;
    ReportFraction( " s9", "0/1", f2 );
    
    f2 = Fraction( 6, 8) - Fraction( 3, 16 );
    ReportFraction( "s10", "9/16", f2 );
    
    f1 = Fraction( -1 , 1 );
    f2 = Fraction( 0, 1 ) - f1;
    ReportFraction( "s11", "1/1", f2 );
    
    f2 = f1 - f1 - f1 - f1;
    ReportFraction( "s12", "2/1", f2 );
    
    Fraction f3 = f2 + f1;
    ReportFraction( "s13", "1/1", f3 );
    
    f3 = Fraction(1,1) + Fraction( 10, 25 );
    ReportFraction( "s14", "7/5", f3 );
    
    f3 = Fraction( 6, 5 ) - Fraction( 5, 6 );
    ReportFraction( "s15", "11/30", f3 );
    
    std::cout << "\n=== Test unary -\n";
    f1 = -Fraction( 1, 2 );
    ReportFraction( "s16", "-1/2", f1 );
    
    f1 = -f1;
    ReportFraction( "s17", "1/2", f1 );  
}

static void TestMult( void )
{
    std::cout << "\n=== Test *=\n";
    
    Fraction f1( 1, 1);
    Fraction f2( 1, 1);
    f1 *= f2;
    ReportFraction( " m1", "1/1", f1 );
    
    f1 *= Fraction( 1, 2 );
    ReportFraction( " m2", "1/2", f1 );
    
    f1 *= Fraction( 2, 5 );
    ReportFraction( " m3", "1/5", f1 );
    
    f1 *= Fraction( 5, 3 );
    ReportFraction( " m4", "1/3", f1 );
    
    f1 = Fraction( 5, 3 ) * Fraction( 3, 5);
    ReportFraction( " m5", "1/1", f1 );
    
    f1 = f1 * f1;
    ReportFraction( " m6", "1/1", f1 );
    
    f1 = Fraction( -5, 2 ) * Fraction(2, 1);
    ReportFraction( " m7", "-5/1", f1 );
    
    f1 = Fraction( -5, 2 ) * Fraction( -2, 1 );
    ReportFraction( " m8", "5/1", f1 );
    
    f1 = Fraction( 7, 5 ) * Fraction( 5, 4 );
    ReportFraction( " m9", "7/4", f1 );
    
    f1 = Fraction( -2, -4) * Fraction( -1, 1 );
    ReportFraction( "m10", "1/-2", f1 );
    
    f1 = Fraction( -4, -4) * Fraction( -2, -2 );
    ReportFraction( "m11", "1/1", f1 );
    
    f1 = Fraction( -4, 4) * Fraction( -2, 2 );
    ReportFraction( "m12", "1/1", f1 );
    
    f1 = Fraction( -4, 4) * Fraction( 2, -2 );
    ReportFraction( "m13", "-1/-1", f1 );
    
    f1 = Fraction( 4, -4) * Fraction( -2, 2 );
    ReportFraction( "m14", "-1/-1", f1 );
    
    f1 = Fraction( 4, -4) * Fraction( 2, -2 );
    ReportFraction( "m15", "1/1", f1 );
}

void TestDivide( void )
{
    std::cout << "\n=== Test /=\n";
    
    Fraction f1( 1, 1);
    Fraction f2( 1, 1);
    f1 /= f2;
    ReportFraction( " d1", "1/1", f1 );
   
    f1 /= Fraction( 2, 3 );
    ReportFraction( " d2", "3/2", f1 );
    
    f1 /= Fraction( 1, 4 );
    ReportFraction( " d3", "6/1", f1 );
    
    f1 /= Fraction( 6, 1 );
    ReportFraction( " d4", "1/1", f1 );
    
    f1 = Fraction( 2,3 ) / Fraction( 1, 4 );
    ReportFraction( " d4", "8/3", f1 );
    
    f1 = Fraction( -2,3 ) / Fraction( 1, 4 );
    ReportFraction( " d5", "-8/3", f1 );
    
    f1 = Fraction( -4,4 );
    f2 = Fraction( -2, -2 );
    Fraction f3 = f1 / f2;
    ReportFraction( " d6", "1/-1", f3 );
    
    f1 = Fraction( -2,3 ) / Fraction( -1, 4 );
    ReportFraction( " d7", "-8/-3", f1 );
}

void TestInvalid( void )
{
    std::cout << "\n=== Test Valid\n";
    
    Fraction f1( 1, 1);
    ReportValid( " v1", true, f1 );
    
    Fraction fInvalid( 1, 0);
    ReportValid( " v2", false, fInvalid );
    
    ReportValid( " v3", false, fInvalid + fInvalid );
    ReportValid( " v4", false, fInvalid - fInvalid );
    ReportValid( " v5", false, fInvalid * fInvalid );
    ReportValid( " v6", false, fInvalid / fInvalid );
    
    ReportValid( " v7", false, f1 + fInvalid );
    ReportValid( " v8", false, f1 - fInvalid );
    ReportValid( " v9", false, f1 * fInvalid );
    ReportValid( "v10", false, f1 / fInvalid );
    
    ReportValid( "v11", false, fInvalid + f1 );
    ReportValid( "v12", false, fInvalid - f1 );
    ReportValid( "v13", false, fInvalid * f1 );
    ReportValid( "v14", false, fInvalid / f1 );
    
    Fraction fNan = Fraction( 0, 0 );
    ReportGreaterThan("v15", false, fNan, fNan);
    ReportGreaterThan("v16", false, f1, fNan);
    ReportGreaterThan("v17", false, fNan, f1);
}

void TestTypecast( void )
{
    std::cout << "\n=== Test Typecast\n";
    
    Fraction f1(75,3);
    double d = f1;
    std::cout << "f1(75,3) as double: " << d << "\n";
    
    std::string s = f1;
    std::cout << "f1(75,3) as string: " << s << "\n";
    
    std::cout << "f1(75,3) as inline: " << f1 << "\n";  // reports double, not string
}