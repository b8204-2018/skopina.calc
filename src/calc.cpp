#include <iostream>
#include <sstream>
#include <cmath>
#include "calc.h"


using namespace std;


double* QuadrEqSolver::calculate(std::string &s) {
    QuadrEqParser parser;
    double *coefficients = parser.parse(s);
    double *roots; //roots[0] = number of roots
    double a, b, c;
    a = coefficients[0];
    b = coefficients[1];
    c = coefficients[2];
    double d = b * b - 4 * a * c;
    if (d < 0) {
        roots = new double[1];
        roots[0] = 0;
        return roots;
    }
    if (d == 0) {
        roots = new double[2];
        roots[0] = 1;
        roots[1] = (-b) / (2 * a);
        return roots;
    }
    roots = new double[3];
    roots[0] = 2;
    roots[1] = (-b + sqrt(d)) / (2 * a);
    roots[2] = (-b - sqrt(d)) / (2 * a);
    return roots;
}


double* BasicSolver::calculate(std::string &s) {
    BiOpParser parser;
    double *coefficients = parser.parse(s);
    auto *result = new double[2];
    result[0] = 1;
    result[1] = operationResult(coefficients[0], coefficients[1]);
    return result;
}


bool Parser::isNum(char c) {
    return (c >= 0x30 && c <= 0x39);
}


void QuadrEqParser::getCoef(string &ex, int pos, int index, double *&coefs){
    if (pos == 0){
        coefs[index] = 1;
    } else if (pos == 1 && ex[0] == '-'){
        coefs[index] = -1;
    } else {
        coefs[index] = stod(ex.substr(0, pos));
    }
}

double* QuadrEqParser::parse(std::string ex) {
    int pos = ex.find("x^2");
    if (pos == string::npos) {
        throw ParserException("Not a quadratic equation.");
    }
    for (int i = 0; i < ex.length(); i++){
        if (ex[i] == ' '){
            ex.erase(i, 1);
        }
    }
    ex.erase(ex.find('='));
    auto coefs = new double [3];
    string number;
    getCoef(ex, pos, 0, coefs);
    ex.erase(0, ex.find("x^2") + 3);
    pos = ex.find('x');
    if (pos != string::npos){
        getCoef(ex, pos, 1, coefs);
        ex.erase(0, pos + 1);
    } else {
        coefs[1] = 0;
    }
    coefs[2] = !ex.empty() ? stod(ex) : 0;
    return coefs;
}

double* BiOpParser::parse(std::string ex) {
    auto *coefs = new double [2];
    int count(0);
    string number;
    int i(0);
    while (i < ex.length() && count <= 2) {
        if (isNum(ex[i])) {
            if (i != 0 && ex[i - 1] == '-'){
                number.insert(0, 1, ex[i - 1]);
            }
            while (isNum(ex[i])) {
                number += ex[i];
                i++;
                if (ex[i] == '.') {
                    if (i + 1 < ex.length() && isNum(ex[i + 1])) {
                        number += ex.substr(i, 2);
                        i += 2;
                    }
                }
            }
            coefs[count] = stod(number);
            count++;
            number.clear();
        }
        else {
            i++;
        }
    }
    if (count != 2){
        throw ParserException("Invalid expression.");
    }
    return coefs;
}


void Solver::add(Calculator *calculator) {
    int i;
    for (i = 0; i < calc.size() && calc[i]->getCode() != calculator->getCode(); i++);
    if (i == calc.size()){//если такого калькулятора еще нет
        calc.push_back(calculator);
    }
}

double* Solver::solve(int code, std::string &s) {
    int i;
    for (i = 0; i < calc.size() && calc[i]->getCode() != code; i++);
    if (i == calc.size()){
        throw SolverException("Appropriate calculator is absent.");
    }
    return calc[i]->calculate(s);
}