#include "Fraction.h"
#include <string>
#include <iostream>
#include <numeric>//for gcd in simplify


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
		throw std::invalid_argument("The denominator can't be 0");
	}

	else {
		this->den = d;
	}

}

//https://www.geeksforgeeks.org/gcd-in-cpp/#gcd-using-inbuilt-function-in-c source  for gcd:
void Fraction::simplify() {
	if (den == 0) {
		throw std::invalid_argument("The denominator can't be 0");
	}

	int gcd = std::gcd(num, den);//gratest common factor

	num /= gcd;

	den /= gcd;

	if (den < 0) {//flips signs
		num = -num;

		den = -den;
	}
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

