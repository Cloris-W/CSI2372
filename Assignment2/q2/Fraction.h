#ifndef FRACTION_H
#define FRACTION_H

// Represents a fraction in lowest terms and tracks live Fraction objects.
class Fraction {
private:
    int numerator;
    int denominator;

public:
    // Initializes and simplifies the fraction; replaces a zero denominator with 1.
    Fraction(int num = 0, int den = 1);
    ~Fraction();

    // Reduces the fraction and makes its denominator positive.
    void simplify();

    // Returns the sum of this fraction and other, reduced to lowest terms.
    Fraction add(const Fraction& other) const;

    // Prints numerator/denominator without a trailing newline.
    void display() const;
    static int liveCount();

private:
    static int counter;
};

// Finds the greatest common divisor using recursive Euclidean division.
int gcd(int a, int b);

#endif
