#ifndef Operator_Header
#define Operator_Header 1

#include "Token.h"
#include "Operands.h"
#include <memory>
#include <stdexcept>

using std::unique_ptr;

enum class Associativity{
    LEFT,
    RIGHT
};

class Operator : public Token{
    private:
    int precedence;
    Associativity associativity;
    char symbol;

    public:
    Operator(int precedence_, Associativity associativity_, char symbol_);

    int getPrecedence();
    Associativity getAssociativity();
    char getSymbol();

    bool isOperator() override ;

    unique_ptr<Operands> operate(Operands & a, Operands & b) const ;

    protected:
    virtual unique_ptr<Operands> dispatch(Operands & a, Operands & b) const = 0;
};


class addOperator : public Operator {
public:
    addOperator();
protected:
    unique_ptr<Operands> dispatch(Operands & a, Operands & b) const override ;
private:
    unique_ptr<Operands> operateAddInt(Operands & a, Operands & b) const ;
    unique_ptr<Operands> operateAddFloat(Operands & a, Operands & b) const ;
};

class subtractOperator : public Operator {
public:
    subtractOperator() ;
protected:
    unique_ptr<Operands> dispatch(Operands & a, Operands & b) const override ;
private:
    unique_ptr<Operands> operateSubInt(Operands & a, Operands & b) const ;
    unique_ptr<Operands> operateSubFloat(Operands & a, Operands & b) const ;
};

class multiplyOperator : public Operator {
public:
    multiplyOperator() ;
protected:
    unique_ptr<Operands> dispatch(Operands & a, Operands & b) const override ;
    
private:
    unique_ptr<Operands> operateMulInt(Operands & a, Operands & b) const ;
    unique_ptr<Operands> operateMulFloat(Operands & a, Operands & b) const ;
};

class divideOperator : public Operator {
public:
    divideOperator() ;
protected:
    unique_ptr<Operands> dispatch(Operands & a, Operands & b) const override ;
private:
    unique_ptr<Operands> operateDivInt(Operands & a, Operands & b) const ;
    unique_ptr<Operands> operateDivFloat(Operands & a, Operands & b) const ;
};

#endif
