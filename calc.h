#ifndef CALC_CALC_H
#define CALC_CALC_H

#include <vector>

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

class Additor: public Calculator{
public:
    int getCode() override{
        return ADDITION;
    }

    double *calculate (double *koefficients) override;
    double *getKoefsFromFile(ifstream &file) override;
};

class Subtractor: public Calculator{
public:
    int getCode() override{
        return SUBTRACTION;
    }

    double *calculate (double *koefficients) override;
    double *getKoefsFromFile(ifstream &file) override;
};

class Multiplicator: public Calculator{
public:
    int getCode() override{
        return MULTIPLICATION;
    }

    double *calculate (double *koefficients) override;
    double *getKoefsFromFile(ifstream &file) override;
};

class Divisor: public Calculator{
public:
    int getCode() override{
        return DIVISION;
    }

    double *calculate (double *koefficients) override;
    double *getKoefsFromFile(ifstream &file) override;
};

double *solve(const char *filepath, Calculator **calc, int n);

void printArr(double *arr);
#endif //CALC_CALC_H
