#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include "complex.hpp"
#include <string>
#include <map>
#include <memory>
#include <iostream>

class Expression {
public:
    virtual ~Expression() = default;
    virtual Complex eval(const std::map<std::string, Complex>& variables) const = 0;
    virtual Expression* clone() const = 0;
    virtual void print(std::ostream& os) const = 0;
};

class Const : public Expression {
    Complex value;
public:
    Const(const Complex& value);
    Complex eval(const std::map<std::string, Complex>& variables) const override;
    Const* clone() const override;
    void print(std::ostream& os) const override;
};

class Variable : public Expression {
    std::string name;
public:
    Variable(const std::string& name);
    Complex eval(const std::map<std::string, Complex>& variables) const override;
    Variable* clone() const override;
    void print(std::ostream& os) const override;
};

class Negate : public Expression {
    std::unique_ptr<Expression> expr;
public:
    Negate(const Expression& expr);
    Complex eval(const std::map<std::string, Complex>& variables) const override;
    Negate* clone() const override;
    void print(std::ostream& os) const override;
};

class Conjugate : public Expression {
    std::unique_ptr<Expression> expr;
public:
    Conjugate(const Expression& expr);
    Complex eval(const std::map<std::string, Complex>& variables) const override;
    Conjugate* clone() const override;
    void print(std::ostream& os) const override;
};

class Add : public Expression {
    std::unique_ptr<Expression> left, right;
public:
    Add(const Expression& left, const Expression& right);
    Complex eval(const std::map<std::string, Complex>& variables) const override;
    Add* clone() const override;
    void print(std::ostream& os) const override;
};

class Subtract : public Expression {
    std::unique_ptr<Expression> left, right;
public:
    Subtract(const Expression& left, const Expression& right);
    Complex eval(const std::map<std::string, Complex>& variables) const override;
    Subtract* clone() const override;
    void print(std::ostream& os) const override;
};

class Multiply : public Expression {
    std::unique_ptr<Expression> left, right;
public:
    Multiply(const Expression& left, const Expression& right);
    Complex eval(const std::map<std::string, Complex>& variables) const override;
    Multiply* clone() const override;
    void print(std::ostream& os) const override;
};

class Divide : public Expression {
    std::unique_ptr<Expression> left, right;
public:
    Divide(const Expression& left, const Expression& right);
    Complex eval(const std::map<std::string, Complex>& variables) const override;
    Divide* clone() const override;
    void print(std::ostream& os) const override;
};

const Negate operator-(const Expression& expr);
const Conjugate operator~(const Expression& expr);
const Add operator+(const Expression& left, const Expression& right);
const Subtract operator-(const Expression& left, const Expression& right);
const Multiply operator*(const Expression& left, const Expression& right);
const Divide operator/(const Expression& left, const Expression& right);

std::ostream& operator<<(std::ostream& os, const Expression& expr);

#endif // EXPRESSIONS_HPP