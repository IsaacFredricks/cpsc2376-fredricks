#include "Fraction.h"
#include <string>
#include <iostream>

Fraction::Fraction() {
	num = 0;
	den = 1;
}

Fraction::Fraction(int num, int den) : num{num}, den{den} {}

int Fraction::getNumerator() const{
	return num;
}

int Fraction::getDenominator() const{
	return den;
}

void Fraction::setNumerator(int n) {
	this->num = n;
}

void Fraction::setDenominator(int d) {
	if (d == 0) {
		std::cout << "error: denominator can't be 0. Exiting program\n";
		throw std::invalid_argument("The denominator can't be 0");
	}

	else {
		this->den = d;
	}

}

void Fraction::simplify() {
	int a = num;
	int b = den;

	// Compute GCD using the Euclidean algorithm
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	int divisor = a;

	// Simplify the fraction
	num /= divisor;
	den /= divisor;
}

//fraction a/b * c/d = ad + cd/ bd
Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
	Fraction frac(((lhs.getNumerator() * rhs.getDenominator())
	+ (rhs.getNumerator() * lhs.getDenominator())),
	(lhs.getDenominator() * rhs.getDenominator()));

	frac.simplify();

	return frac;
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
	Fraction frac(((lhs.getNumerator() * rhs.getDenominator())
	- (rhs.getNumerator() * lhs.getDenominator())),
	(lhs.getDenominator() * rhs.getDenominator()));

	frac.simplify();

	return frac;
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
	Fraction frac((lhs.getNumerator() * rhs.getNumerator())
	, (lhs.getDenominator() * rhs.getDenominator()));

	return frac;
}

//dividing fractions same as multiplying by its reciprocal
Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
	Fraction frac((lhs.getNumerator() * rhs.getDenominator())
	, (lhs.getDenominator() * rhs.getNumerator()));

	return frac;
}

std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
	os << frac.getNumerator() << '/' << frac.getDenominator() << '\n';

	return os;
}

