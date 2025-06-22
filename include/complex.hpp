#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <string>

class Complex {
private:
    double re, im;

public:
    Complex(double re = 0, double im = 0);

    double real() const;
    double imag() const;
    double abs() const;
    std::string str() const;

    Complex operator-() const;
    Complex operator~() const;

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);

    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
};

Complex operator+(Complex a, const Complex& b);
Complex operator-(Complex a, const Complex& b);
Complex operator*(Complex a, const Complex& b);
Complex operator/(Complex a, const Complex& b);

std::ostream& operator<<(std::ostream& os, const Complex& c);

#endif