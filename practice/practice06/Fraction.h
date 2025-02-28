#pragma once
#include <string>
#include <iostream>
#include <numeric>//for gcd in cimplify
#include <algorithm>//also for gcd

class Fraction {
private:
	int num;//numerator
	int den;//denominator

public:

	//constructors
	Fraction();//default constructor

	Fraction(int num, int den);//constructor with parameters

	//member functions

	int getNumerator() const;

	int getDenominator() const;

	void setNumerator(int n);

	void setDenominator(int d);//exception if d == 0

	void simplify();//use euclidean algorithm

	//friend functions
	friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator-(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator*(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator/(const Fraction& lhs, const Fraction& rhs);

	//prints fraction option
	friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);
	
};
