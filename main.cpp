#include <iostream>

#include "include/complex.hpp"

int main() {
    Complex a(1, 2);
    Complex b(3, -4);

    a /= b;

    std::cout << a << std::endl;
}
