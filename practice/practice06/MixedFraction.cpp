#include "MixedFraction.h"
#include <string>
#include <iostream>
#include <numeric>//for gcd in cimplify
#include <algorithm>//also for gcd

MixedFraction::MixedFraction(int whole, int n, int d) : Fraction(n, d), whole{ whole } {}

MixedFraction::MixedFraction(const Fraction& fraction)
: Fraction(fraction.getNumerator() % fraction.getDenominator(), fraction.getDenominator()) {

	whole = fraction.getNumerator() / fraction.getDenominator();
}

int MixedFraction::getWhole() const{
	return whole;
}

//prints fraction option
std::ostream& operator<<(std::ostream& os, const MixedFraction& mixFrac) {
	os << mixFrac.getWhole() << " " << mixFrac.getNumerator() << '/' 
	<< mixFrac.getDenominator() << '\n';

	return os;
}
