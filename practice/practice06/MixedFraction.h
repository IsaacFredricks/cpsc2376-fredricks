#pragma once
#include "Fraction.h"
#include <string>
#include <iostream>
#include <numeric>//for gcd in simplify

class MixedFraction : Fraction {//derived from fraction
private:
	int whole;

public:

	MixedFraction(int whole, int n, int d);
	MixedFraction(const Fraction& fraction);//converts fraction to mixed fraction

	int getWhole() const;

	//prints fraction option
	friend std::ostream& operator<<(std::ostream& os, const MixedFraction& mixFrac);
};