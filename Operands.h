#ifndef Operands_Header
#define Operands_Header 1
#include "Token.h"
#include <iostream>

enum class OperandType{
    INT,
    FLOAT,
    COMPLEX
};

class Operands : public Token{
    public:
    virtual ~Operands() = default;
    virtual OperandType getType() = 0;
    virtual void printValue() = 0;
    bool isOperator() override {
        return false;
    }
    
    virtual Operands * createFromLowerOperand(Operands & lower) = 0;
};

class IntegerOperand : public Operands {
    int value;
public:
    IntegerOperand(int value_) ;
    OperandType getType() override ;
    void printValue() override ; 
    int getValue() ; 
    
    Operands * createFromLowerOperand(Operands &) override ; 
};

class FloatOperand : public Operands {
    double value;
public:
    FloatOperand(double value_) ;
    OperandType getType() override ;
    void printValue() override ; 
    double getValue() ;

    
    Operands * createFromLowerOperand(Operands & lower) override ;
};

#endif
