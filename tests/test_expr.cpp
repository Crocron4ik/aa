#include <catch2/catch_test_macros.hpp>
#include "expressions.hpp"
#include <sstream>
#include <map>

TEST_CASE("Expression evaluation") {
    std::map<std::string, Complex> vars = {
        {"x", Complex(2.0, 1.0)},
        {"y", Complex(1.0, -1.0)}
    };

    SECTION("Const expression") {
        Const c(Complex(3.0, 4.0));
        REQUIRE(c.eval(vars) == Complex(3.0, 4.0));

        std::ostringstream oss;
        oss << c;
        REQUIRE(oss.str() == "3+4i");
    }

    SECTION("Variable expression") {
        Variable x("x");
        REQUIRE(x.eval(vars) == Complex(2.0, 1.0));

        Variable z("z");
        REQUIRE(z.eval(vars) == Complex(0.0, 0.0));

        std::ostringstream oss;
        oss << x;
        REQUIRE(oss.str() == "x");
    }

    SECTION("Negate expression") {
        Const c(Complex(1.0, -2.0));
        Negate neg(c);
        REQUIRE(neg.eval(vars) == Complex(-1.0, 2.0));

        std::ostringstream oss;
        oss << neg;
        REQUIRE(oss.str() == "-(1-2i)");
    }

    SECTION("Conjugate expression") {
        Const c(Complex(1.0, -2.0));
        Conjugate conj(c);
        REQUIRE(conj.eval(vars) == Complex(1.0, 2.0));

        std::ostringstream oss;
        oss << conj;
        REQUIRE(oss.str() == "~(1-2i)");
    }

    SECTION("Add expression") {
        Add expr = Const(1.0) + Variable("x");
        REQUIRE(expr.eval(vars) == Complex(3.0, 1.0));

        std::ostringstream oss;
        oss << expr;
        REQUIRE(oss.str() == "(1+0i + x)");
    }

    SECTION("Subtract expression") {
        Subtract expr = Variable("x") - Const(1.0);
        REQUIRE(expr.eval(vars) == Complex(1.0, 1.0));

        std::ostringstream oss;
        oss << expr;
        REQUIRE(oss.str() == "(x - 1+0i)");
    }

    SECTION("Multiply expression") {
        Multiply expr = Variable("x") * Variable("y");
        REQUIRE(expr.eval(vars) == Complex(3.0, -1.0));

        std::ostringstream oss;
        oss << expr;
        REQUIRE(oss.str() == "(x * y)");
    }

    SECTION("Divide expression") {
        Divide expr = Variable("x") / Variable("y");
        Complex result = expr.eval(vars);
        REQUIRE(std::abs(result.real() - 0.5) < 1e-9);
        REQUIRE(std::abs(result.imag() - 1.5) < 1e-9);

        std::ostringstream oss;
        oss << expr;
        REQUIRE(oss.str() == "(x / y)");
    }

    SECTION("Complex expression") {
        const auto expr = (Const(2.0) * Variable("x") + Const(1.0)) / Variable("y");
        Complex result = expr.eval(vars);

        REQUIRE(std::abs(result.real() - 1.5) < 1e-9);
        REQUIRE(std::abs(result.imag() - 3.5) < 1e-9);

        std::ostringstream oss;
        oss << expr;
        REQUIRE(oss.str() == "(((2+0i * x) + 1+0i) / y)");
    }

    SECTION("Expression cloning") {
        Const c(Complex(1.0, 2.0));
        auto* clone = c.clone();
        REQUIRE(clone->eval(vars) == Complex(1.0, 2.0));
        delete clone;

        Variable v("x");
        auto* vclone = v.clone();
        REQUIRE(vclone->eval(vars) == Complex(2.0, 1.0));
        delete vclone;
    }
}