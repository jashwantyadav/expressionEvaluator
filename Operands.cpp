#include "Operands.h"


IntegerOperand::IntegerOperand(int value_) : value(value_) {}
OperandType IntegerOperand::getType()  { return OperandType::INT; }
void IntegerOperand::printValue() { std::cout << value; }
int IntegerOperand::getValue() { return value; }

Operands * IntegerOperand::createFromLowerOperand(Operands &) { return nullptr; }



FloatOperand::FloatOperand(double value_) : value(value_) {}
OperandType FloatOperand::getType() { return OperandType::FLOAT; }
void FloatOperand::printValue() { std::cout << value; }
double FloatOperand::getValue() { return value; }


Operands * FloatOperand::createFromLowerOperand(Operands & lower) {
    switch(lower.getType()){
        case OperandType::INT:
            return new FloatOperand(
                static_cast<IntegerOperand&>(lower).getValue());
        default:
            return nullptr;
    }
}
