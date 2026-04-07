#ifndef FRACTION_H
#define FRACTION_H

#include <string>

class Fraction {
private:
    int numerator;
    int denominator;
    void simplify();
public:
    Fraction(int num, int den);
    std::string toString() const;
    Fraction sum(const Fraction& other) const;
    Fraction sub(const Fraction& other) const;
    Fraction mul(const Fraction& other) const;
    Fraction div(const Fraction& other) const;
    Fraction minus(int value) const;
};

#endif