#include "expressions.hpp"
#include <cmath>
#include <sstream>

Const::Const(const Complex& value) : value(value) {}

Complex Const::eval(const std::map<std::string, Complex>&) const {
    return value;
}

Const* Const::clone() const {
    return new Const(value);
}

void Const::print(std::ostream& os) const {
    os << value;
}

Variable::Variable(const std::string& name) : name(name) {}

Complex Variable::eval(const std::map<std::string, Complex>& variables) const {
    auto it = variables.find(name);
    if (it == variables.end()) {
        return Complex();
    }
    return it->second;
}

Variable* Variable::clone() const {
    return new Variable(name);
}

void Variable::print(std::ostream& os) const {
    os << name;
}

Negate::Negate(const Expression& expr) : expr(expr.clone()) {}

Complex Negate::eval(const std::map<std::string, Complex>& variables) const {
    return -expr->eval(variables);
}

Negate* Negate::clone() const {
    return new Negate(*expr);
}

void Negate::print(std::ostream& os) const {
    os << "-(" << *expr << ")";
}

Conjugate::Conjugate(const Expression& expr) : expr(expr.clone()) {}

Complex Conjugate::eval(const std::map<std::string, Complex>& variables) const {
    return ~expr->eval(variables);
}

Conjugate* Conjugate::clone() const {
    return new Conjugate(*expr);
}

void Conjugate::print(std::ostream& os) const {
    os << "~(" << *expr << ")";
}

Add::Add(const Expression& left, const Expression& right)
    : left(left.clone()), right(right.clone()) {}

Complex Add::eval(const std::map<std::string, Complex>& variables) const {
    return left->eval(variables) + right->eval(variables);
}

Add* Add::clone() const {
    return new Add(*left, *right);
}

void Add::print(std::ostream& os) const {
    os << "(" << *left << " + " << *right << ")";
}

Subtract::Subtract(const Expression& left, const Expression& right)
    : left(left.clone()), right(right.clone()) {}

Complex Subtract::eval(const std::map<std::string, Complex>& variables) const {
    return left->eval(variables) - right->eval(variables);
}

Subtract* Subtract::clone() const {
    return new Subtract(*left, *right);
}

void Subtract::print(std::ostream& os) const {
    os << "(" << *left << " - " << *right << ")";
}

Multiply::Multiply(const Expression& left, const Expression& right)
    : left(left.clone()), right(right.clone()) {}

Complex Multiply::eval(const std::map<std::string, Complex>& variables) const {
    return left->eval(variables) * right->eval(variables);
}

Multiply* Multiply::clone() const {
    return new Multiply(*left, *right);
}

void Multiply::print(std::ostream& os) const {
    os << "(" << *left << " * " << *right << ")";
}

Divide::Divide(const Expression& left, const Expression& right)
    : left(left.clone()), right(right.clone()) {}

Complex Divide::eval(const std::map<std::string, Complex>& variables) const {
    return left->eval(variables) / right->eval(variables);
}

Divide* Divide::clone() const {
    return new Divide(*left, *right);
}

void Divide::print(std::ostream& os) const {
    os << "(" << *left << " / " << *right << ")";
}

const Negate operator-(const Expression& expr) {
    return Negate(expr);
}

const Conjugate operator~(const Expression& expr) {
    return Conjugate(expr);
}

const Add operator+(const Expression& left, const Expression& right) {
    return Add(left, right);
}

const Subtract operator-(const Expression& left, const Expression& right) {
    return Subtract(left, right);
}

const Multiply operator*(const Expression& left, const Expression& right) {
    return Multiply(left, right);
}

const Divide operator/(const Expression& left, const Expression& right) {
    return Divide(left, right);
}

std::ostream& operator<<(std::ostream& os, const Expression& expr) {
    expr.print(os);
    return os;
}