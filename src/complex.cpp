#include "complex.hpp"
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>


Complex::Complex(double re, double im) : re(re), im(im) {}

double Complex::real() const { return re; }
double Complex::imag() const { return im; }
double Complex::abs() const { return sqrt(re*re + im*im); }

std::string Complex::str() const {
    auto format = [](double x) {
        if (x == 0.0) return std::string("0");
        std::ostringstream oss;
        oss << std::setprecision(6) << std::defaultfloat << x;
        std::string s = oss.str();
        s.erase(s.find_last_not_of('0') + 1, std::string::npos);
        if (!s.empty() && s.back() == '.') s.pop_back();
        return s;
    };
    return format(re) + (im >= 0 ? "+" : "") + format(im) + "i";
}

Complex Complex::operator-() const { return Complex(-re, -im); }
Complex Complex::operator~() const { return Complex(re, -im); }

Complex& Complex::operator+=(const Complex& other) {
    re += other.re;
    im += other.im;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    re -= other.re;
    im -= other.im;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    double new_re = re * other.re - im * other.im;
    double new_im = re * other.im + im * other.re;
    re = new_re;
    im = new_im;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    double other_squares = other.re * other.re + other.im * other.im;
    double new_re = (re * other.re + im * other.im) / other_squares;
    double new_im = (im * other.re - re * other.im) / other_squares;
    re = new_re;
    im = new_im;
    return *this;
}

bool Complex::operator==(const Complex& other) const {
    return re == other.re && im == other.im;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

Complex operator+(Complex a, const Complex& b) { return a += b; }
Complex operator-(Complex a, const Complex& b) { return a -= b; }
Complex operator*(Complex a, const Complex& b) { return a *= b; }
Complex operator/(Complex a, const Complex& b) { return a /= b; }

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.str();
    return os;
}