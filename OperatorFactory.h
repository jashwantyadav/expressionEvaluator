#ifndef OperatorFactory_Header
#define OperatorFactory_Header 1

#include "Operator.h"

class OperatorFactory {
public:
    static bool isOperator(char c) ;
    static Operator * get(char c) ;
};

#endif
