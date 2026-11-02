#include "Fraction.h"
#include <iostream>
#include <cstdlib>

int Fraction::counter = 0;

Fraction::Fraction(int num, int den)
    : numerator(num), denominator(den) {
    if (denominator == 0) {
        std::cerr << "Error: denominator cannot be zero; using 1 instead."
                  << std::endl;
        denominator = 1;
    }
    simplify();
    ++counter;
}

Fraction::~Fraction() {
    --counter;
}

void Fraction::simplify() {
    const int divisor = gcd(std::abs(numerator), std::abs(denominator));
    numerator /= divisor;
    denominator /= divisor;

    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

Fraction Fraction::add(const Fraction& other) const {
    // C++17 constructs this result directly, without an intermediate copy.
    return Fraction(numerator * other.denominator + other.numerator * denominator,
                    denominator * other.denominator);
}

void Fraction::display() const {
    std::cout << numerator << '/' << denominator;
}

int Fraction::liveCount() {
    return counter;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
