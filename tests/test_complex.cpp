#include <catch2/catch_test_macros.hpp>
#include "complex.hpp"
#include <sstream>
#include <cmath>

TEST_CASE("Complex number operations") {
    SECTION("Constructors") {
        Complex c1;
        REQUIRE(c1.real() == 0.0);
        REQUIRE(c1.imag() == 0.0);

        Complex c2(3.5);
        REQUIRE(c2.real() == 3.5);
        REQUIRE(c2.imag() == 0.0);

        Complex c3(2.0, -1.5);
        REQUIRE(c3.real() == 2.0);
        REQUIRE(c3.imag() == -1.5);
    }

    SECTION("Arithmetic operations") {
        Complex a(1.0, 2.0);
        Complex b(3.0, -4.0);

        SECTION("Addition") {
            Complex c = a + b;
            REQUIRE(c.real() == 4.0);
            REQUIRE(c.imag() == -2.0);

            a += b;
            REQUIRE(a.real() == 4.0);
            REQUIRE(a.imag() == -2.0);
        }

        SECTION("Subtraction") {
            Complex c = a - b;
            REQUIRE(c.real() == -2.0);
            REQUIRE(c.imag() == 6.0);

            a -= b;
            REQUIRE(a.real() == -2.0);
            REQUIRE(a.imag() == 6.0);
        }

        SECTION("Multiplication") {
            Complex c = a * b;
            REQUIRE(c.real() == 11.0);
            REQUIRE(c.imag() == 2.0);

            a *= b;
            REQUIRE(a.real() == 11.0);
            REQUIRE(a.imag() == 2.0);
        }

        SECTION("Division") {
            Complex c = a / b;
            REQUIRE(c.real() == -0.2);
            REQUIRE(c.imag() == 0.4);

            a /= b;
            REQUIRE(a.real() == -0.2);
            REQUIRE(a.imag() == 0.4);
        }
    }

    SECTION("Unary operations") {
        Complex a(1.0, -2.0);

        SECTION("Unary minus") {
            Complex b = -a;
            REQUIRE(b.real() == -1.0);
            REQUIRE(b.imag() == 2.0);
        }

        SECTION("Conjugate") {
            Complex b = ~a;
            REQUIRE(b.real() == 1.0);
            REQUIRE(b.imag() == 2.0);
        }
    }

    SECTION("Absolute value") {
        Complex a(3.0, 4.0);
        REQUIRE(a.abs() == 5.0);

        Complex b(-3.0, -4.0);
        REQUIRE(b.abs() == 5.0);
    }

    SECTION("Comparison") {
        Complex a(1.0, 2.0);
        Complex b(1.0, 2.0);
        Complex c(1.0, 2.1);
        Complex d(1.1, 2.0);

        REQUIRE(a == b);
        REQUIRE(a != c);
        REQUIRE(a != d);
        REQUIRE(c != d);
    }

    SECTION("String representation") {
        Complex a(1.5, 2.5);
        REQUIRE(a.str() == "1.5+2.5i");

        Complex b(-1.5, -2.5);
        REQUIRE(b.str() == "-1.5-2.5i");

        Complex c(0.0, 1.0);
        REQUIRE(c.str() == "0+1i");

        Complex d(1.0, 0.0);
        REQUIRE(d.str() == "1+0i");
    }

    SECTION("Stream output") {
        Complex a(1.5, -2.5);
        std::ostringstream oss;
        oss << a;
        REQUIRE(oss.str() == "1.5-2.5i");
    }
}