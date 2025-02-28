#include "MixedFraction.h"
#include <string>
#include <iostream>

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
	if (mixFrac.getWhole() != 0 && mixFrac.getNumerator() > 0) {
		os << "It's a mixed fraction" << mixFrac.getWhole() 
		<< " " << mixFrac.getNumerator() << '/'
		<< mixFrac.getDenominator() << '\n';

	}

	else if (mixFrac.getNumerator() == 0) {
		os << "Its a whole number: " << mixFrac.getWhole() << '\n';

	}

	else {
		os << "It's not big enough to be a mixed fraction"
		<< mixFrac.getNumerator() << '/'
		<< mixFrac.getDenominator() << '\n';
	}
	return os;
}
