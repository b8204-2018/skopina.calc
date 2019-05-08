#ifndef CALC_EXCEPTIONS_H
#define CALC_EXCEPTIONS_H

#include <string>

class Exception{
protected:
    std::string error;
public:
    Exception(std::string error): error(std::move(error)){}
    const char* getError() { return error.c_str();}
};

class CalculatorIsAbsent: public Exception{
public:
    CalculatorIsAbsent():Exception("Appropriate calculator is absent."){}
};

class InvalidExpression: public Exception{
public:
    InvalidExpression():Exception("Invalid expression."){}
};

class NotAQuadrEq: public Exception{
public:
    NotAQuadrEq():Exception("Not a quadratic equation."){}
};

#endif //CALC_EXCEPTIONS_H
