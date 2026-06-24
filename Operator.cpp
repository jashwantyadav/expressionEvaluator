#include "Operator.h"

Operator::Operator(int precedence_, Associativity associativity_, char symbol_)
    : precedence(precedence_), associativity(associativity_), symbol(symbol_) {}

int Operator::getPrecedence(){ return precedence; }
Associativity Operator::getAssociativity(){ return associativity; }
char Operator::getSymbol(){ return symbol; }

bool Operator::isOperator()  { return true; }

unique_ptr<Operands> Operator::operate(Operands & a, Operands & b) const {
    if(a.getType() == b.getType()){
        return dispatch(a, b);
    }
    if(a.getType() < b.getType()){             
        unique_ptr<Operands> promoted(b.createFromLowerOperand(a));
        return dispatch(*promoted, b);         
    } else {                                    
        unique_ptr<Operands> promoted(a.createFromLowerOperand(b));
        return dispatch(a, *promoted);          
    }
}


addOperator::addOperator() : Operator(6, Associativity::LEFT, '+') {}

unique_ptr<Operands> addOperator::dispatch(Operands & a, Operands & b) const  {
    if(a.getType() == OperandType::INT){
        return operateAddInt(a, b);
    } else if(a.getType() == OperandType::FLOAT){
        return operateAddFloat(a, b);
    }
    return nullptr;
}

unique_ptr<Operands> addOperator::operateAddInt(Operands & a, Operands & b) const {
    int x = static_cast<IntegerOperand&>(a).getValue();
    int y = static_cast<IntegerOperand&>(b).getValue();
    return std::make_unique<IntegerOperand>(x + y);
}
unique_ptr<Operands> addOperator::operateAddFloat(Operands & a, Operands & b) const {
    double x = static_cast<FloatOperand&>(a).getValue();
    double y = static_cast<FloatOperand&>(b).getValue();
    return std::make_unique<FloatOperand>(x + y);
}



subtractOperator::subtractOperator() : Operator(6, Associativity::LEFT, '-') {}

unique_ptr<Operands> subtractOperator::dispatch(Operands & a, Operands & b) const  {
    if(a.getType() == OperandType::INT){
        return operateSubInt(a, b);
    } else if(a.getType() == OperandType::FLOAT){
        return operateSubFloat(a, b);
    }
    return nullptr;
}

unique_ptr<Operands> subtractOperator::operateSubInt(Operands & a, Operands & b) const {
    int x = static_cast<IntegerOperand&>(a).getValue();
    int y = static_cast<IntegerOperand&>(b).getValue();
    return std::make_unique<IntegerOperand>(x - y);   
}
unique_ptr<Operands> subtractOperator::operateSubFloat(Operands & a, Operands & b) const {
    double x = static_cast<FloatOperand&>(a).getValue();
    double y = static_cast<FloatOperand&>(b).getValue();
    return std::make_unique<FloatOperand>(x - y);
}


multiplyOperator::multiplyOperator() : Operator(5, Associativity::LEFT, '*') {}

unique_ptr<Operands> multiplyOperator::dispatch(Operands & a, Operands & b) const  {
    if(a.getType() == OperandType::INT){
        return operateMulInt(a, b);
    } else if(a.getType() == OperandType::FLOAT){
        return operateMulFloat(a, b);
    }
    return nullptr;
}

unique_ptr<Operands> multiplyOperator::operateMulInt(Operands & a, Operands & b) const {
    int x = static_cast<IntegerOperand&>(a).getValue();
    int y = static_cast<IntegerOperand&>(b).getValue();
    return std::make_unique<IntegerOperand>(x * y);
}
unique_ptr<Operands> multiplyOperator::operateMulFloat(Operands & a, Operands & b) const {
    double x = static_cast<FloatOperand&>(a).getValue();
    double y = static_cast<FloatOperand&>(b).getValue();
    return std::make_unique<FloatOperand>(x * y);
}


divideOperator::divideOperator() : Operator(5, Associativity::LEFT, '/') {}

unique_ptr<Operands> divideOperator::dispatch(Operands & a, Operands & b) const  {
    if(a.getType() == OperandType::INT){
        return operateDivInt(a, b);
    } else if(a.getType() == OperandType::FLOAT){
        return operateDivFloat(a, b);
    }
    return nullptr;
}

unique_ptr<Operands> divideOperator::operateDivInt(Operands & a, Operands & b) const {
    int x = static_cast<IntegerOperand&>(a).getValue();
    int y = static_cast<IntegerOperand&>(b).getValue();
    if(y == 0) throw std::runtime_error("Division by zero");
    return std::make_unique<IntegerOperand>(x / y);  
}
unique_ptr<Operands> divideOperator::operateDivFloat(Operands & a, Operands & b) const {
    double x = static_cast<FloatOperand&>(a).getValue();
    double y = static_cast<FloatOperand&>(b).getValue();
    if(y == 0.0) throw std::runtime_error("Division by zero");
    return std::make_unique<FloatOperand>(x / y);
}

    
