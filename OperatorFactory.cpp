#include "OperatorFactory.h"


bool OperatorFactory::isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}

Operator * OperatorFactory::get(char c){
    static addOperator      add;
    static subtractOperator sub;
    static multiplyOperator mul;
    static divideOperator   div;
    switch(c){
        case '+': return &add;
        case '-': return &sub;
        case '*': return &mul;
        case '/': return &div;
        default:  return nullptr;
    }
}
