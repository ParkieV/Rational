#include "include/rational/Rational.h"
#include <iostream>
#include <numeric>
#include <stdexcept>


// Constructors 
Rational::Rational() : num_(0), den_(1) {}
Rational::Rational(const int32_t value) noexcept : num_(value), den_(1) {}
Rational::Rational(const int32_t num, const int32_t den) : num_(num), den_(den) {
	normalize();
}

// Basic сomparison operations
bool Rational::operator==(const Rational& other) const noexcept { // k == n;
	return num_ == other.num() && den_ == other.den();
}

bool Rational::operator!=(const Rational& other) const noexcept {
	return !(*this == other);
}

bool Rational::operator>(const Rational& other) const noexcept {
	return num_ * other.den() > other.num() * den_;
}

bool Rational::operator<(const Rational& other) const noexcept {
	return num_ * other.den() < other.num() * den_;
}

bool Rational::operator>=(const Rational& other) const noexcept {
	return !(other > *this);
}

bool Rational::operator<=(const Rational& other) const noexcept {
	return !(other < *this);
}


Rational Rational::operator-() const noexcept { // -num
	return Rational(-num_, den_);
}

Rational::operator bool() const noexcept {
	return *this != Rational(0, 1);
}

Rational& Rational::operator*=(const Rational& rhs) noexcept {
	*this = Rational(num_ * rhs.num(), den_ * rhs.den());
	normalize();
	return *this;
}

Rational& Rational::operator+=(const Rational& rhs) noexcept {
	*this = Rational(num_ * rhs.den() + rhs.num()* den_, den_* rhs.den());
	normalize();
	return *this;
}

Rational& Rational::operator-=(const Rational& rhs) noexcept {
	*this = Rational(num_ * rhs.den() - rhs.num()* den_, den_* rhs.den());
    normalize();
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
	*this = Rational(num_ * rhs.den(), den_ * rhs.num());
	normalize();
	return *this;
}

std::istream& Rational::read_from(std::istream& istrm) noexcept {
	char delimiter(0);
	double num(0.0);
	double den(1.0);
	while (!istrm.eof()) {
		char sym = istrm.get();
		if (sym != ' ') {
			istrm.unget();
			break;
		}
	}
	istrm >> std::noskipws >> num >> delimiter >> den;
	if (istrm.good() || istrm.eof()) {
		if (delimiter == delimiter_ && den > 0) {
			num_ = num;
			den_ = den;
			normalize();
		}
		else {
			istrm.clear(std::ios_base::failbit);
		}
	}
	return istrm;
	
};

std::ostream& Rational::write_to(std::ostream& ostrm) const noexcept {
	return ostrm << num_ << delimiter_ << den_;
	
}

void Rational::normalize() {
	if (den_ < 0) {
		num_ = -num_;
		den_ = -den_;
	}
	else if (den_ == 0) {
		throw std::invalid_argument("Division by zero not allowed");
	}
	int divisor = std::gcd(num(), den());
	num_ /= divisor;
	den_ /= divisor;
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
	return rhs.read_from(istrm);
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
	return rhs.write_to(ostrm);
}