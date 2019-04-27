#include <iostream>
#include <sstream>
#include <cmath>
#include "calc.h"


using namespace std;


double* QuadrEqSolver::calculate(std::string &s) {
   try {
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
   } catch (std::invalid_argument &err){
       cout << err.what();
   }
}


double* BasicSolver::calculate(std::string &s) {
    try {
        BiOpParser parser;
        double *coefficients = parser.parse(s);
        auto *result = new double[2];
        result[0] = 1;
        result[1] = operationResult(coefficients[0], coefficients[1]);
        return result;
    } catch (std::invalid_argument &err){
        cout << err.what() << endl;
    }
}


bool Parser::isNum(char c) {
    return (c >= 0x30 && c <= 0x39);
}


double Parser::cast(std::string s) {
    stringstream stream;
    stream << s;
    double number;
    stream >> number;
    return number;
}

void QuadrEqParser::getCoef(string &ex, string separ, int index, double *&coefs){
    if (ex.find(separ) == 0){
        coefs[index] = 1;
    } else if (ex.find(separ) == 1 && ex[0] == '-'){
        coefs[index] = -1;
    } else {
        int pos = ex.find(separ);
        coefs[index] = cast(ex.substr(0, pos));
    }
}

double* QuadrEqParser::parse(std::string ex) {
    if (ex.find("x^2") == string::npos) {
        throw std::invalid_argument("Not a quadratic equation.");
    }
    for (int i = 0; i < ex.length(); i++){
        if (ex[i] == ' '){
            ex.erase(i, 1);
        }
    }
    ex.erase(ex.find("="));
    auto coefs = new double [3];
    string number;
    getCoef(ex, "x^2", 0, coefs);
    ex.erase(0, ex.find("x^2") + 3);
    if (ex.find("x") != string::npos){
        getCoef(ex, "x", 1, coefs);
        ex.erase(0, ex.find("x") + 1);
    } else {
        coefs[1] = 0;
    }
    if (!ex.empty()){
        coefs[2] = cast(ex);
    } else {
        coefs[2] = 0;
    }
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
            coefs[count] = cast(number);
            count++;
            number.clear();
        }
        else {
            i++;
        }
    }
    if (count != 2){
        throw std::invalid_argument ("Invalid expression.");
    }
    return coefs;
}


bool operator!= (Calculator &calc1, Calculator &calc2){
    return (calc1.getCode() != calc2.getCode());
}



void Solver::add(Calculator &calculator) {
    CalcList *current = head;
    while (current != nullptr && current->calculator != calculator){
        current = current->next;
    }
    if (current == nullptr){//если такого калькулятора еще нет
        current = new CalcList(calculator);
        current->next = head;
        swap(head, current);
    }
}

double* Solver::solve(int code, std::string &s) {
    CalcList *current = head;
    while (current != nullptr && current->calculator.getCode()!= code){
        current = current->next;
    }
    if (current == nullptr){
        throw std::logic_error ("Appropriate calculator is absent.");
    }
    return current->calculator.calculate(s);
}