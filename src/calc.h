#ifndef CALC_CALC_H
#define CALC_CALC_H


#define QUADRATIC_EQ 1
#define ADDITION 2
#define SUBTRACTION 3
#define MULTIPLICATION 4
#define DIVISION 5


using namespace std;


class Calculator {
public:
    virtual double *calculate (double *koefficients) = 0;
    virtual int getCode() = 0;
    virtual double *getKoefsFromFile(ifstream &file) = 0;
};


class Quadratic_equation_solver: public Calculator{
public:
    int getCode() override{
        return QUADRATIC_EQ;
    }

    double *calculate (double *koefficients) override;
    double *getKoefsFromFile(ifstream &file) override;
};

class BasicSolver: public Calculator{
public:
    double *getKoefsFromFile(ifstream &file) override;
    double *calculate (double *koefficients) override;
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

double *solve(const char *filepath, Calculator **calc, int n);

void printArr(double *arr);
#endif //CALC_CALC_H
