#ifndef CALC_CALC_H
#define CALC_CALC_H


#include <vector>


#define QUADRATIC_EQ 1
#define ADDITION 2
#define SUBTRACTION 3
#define MULTIPLICATION 4
#define DIVISION 5

class Exception{
protected:
    std::string error;
public:
    Exception(std::string error): error(error){}
    const char* getError() { return error.c_str();}
};


class ParserException: public Exception{
public:
    ParserException(std::string err): Exception(err){}
};


class SolverException: public Exception{
public:
    SolverException(std::string err): Exception(err){}
};


class Parser {
public:
    bool isNum (char c);
    virtual double *parse(std::string ex) = 0;
};


class QuadrEqParser: public Parser {
    void getCoef(std::string &ex, int pos, int index, double *&coefs);
public:
    double *parse(std::string ex) override ;
};


class BiOpParser: public Parser{
public:
    double *parse(std::string ex) override ;
};


class Calculator {
public:
    virtual double *calculate (std::string &s) = 0;
    virtual int getCode() = 0;
};


class QuadrEqSolver: public Calculator{
public:
    int getCode() override{
        return QUADRATIC_EQ;
    }
    double *calculate (std::string &s) override;
};


class BasicSolver: public Calculator{
public:
    double *calculate (std::string &s) override;
    virtual double operationResult(double a, double b) = 0;
};


class Additor: public BasicSolver{
public:
    int getCode() override{
        return ADDITION;
    }
    double operationResult(double a, double b)override {
        return (a + b);
    }
};


class Subtractor: public BasicSolver{
public:
    int getCode() override{
        return SUBTRACTION;
    }
    double operationResult(double a, double b)override {
        return (a - b);
    }
};


class Multiplicator: public BasicSolver{
public:
    int getCode() override{
        return MULTIPLICATION;
    }
    double operationResult(double a, double b)override {
        return (a * b);
    }
};


class Divisor: public BasicSolver{
public:
    int getCode() override{
        return DIVISION;
    }
    double operationResult(double a, double b)override {
        return (a / b);
    }
};


class Solver{
    std::vector<Calculator*> calc;
public:
    void add(Calculator *calculator);
    double *solve(int code, std::string &s);
};

#endif //CALC_CALC_H
