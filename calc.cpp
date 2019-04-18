#include <fstream>
#include <cmath>
#include "calc.h"


double * Quadratic_equation_solver::calculate(double *koefficients) {
    double n = koefficients[0];
    if (n < 1 || n > 3){
        return nullptr;
    }
    double *roots; //roots[0] = number of roots
    double a, b, c;
    a = koefficients[1];

    if (n == 1){
     b = c = 0;
    }
    if (n == 2) {
        b = koefficients[2];
        c = 0;
    }
    if (n == 3) {
        b = koefficients[2];
        c = koefficients [3];
    }

    double d = b * b - 4 * a * c;
    if (d < 0){
        roots = new double [1];
        roots[0] = 0;
        return roots;
    }
    if (d == 0){
        roots = new double [2];
        roots[0] = 1;
        roots[1] = (-b)/(2 * a);
        return roots;
    }
    if (d > 0){
        roots = new double [3];
        roots[0] = 2;
        roots[1] = (-b + sqrt(d)) / (2 * a);
        roots[2] = (-b - sqrt(d)) / (2 * a);
        return roots;
    }
}

double* Additor::calculate(double *koefficients) {
    if (koefficients[0] != 2) {
        return nullptr;
    }
    auto *result = new double [2];
    result[0] = 1;
    result[1] = koefficients[1] + koefficients[2];
    return result;
}

double* Subtractor::calculate(double *koefficients) {
    if (koefficients[0] != 2) {
        return nullptr;
    }
    auto *result = new double [2];
    result[0] = 1;
    result[1] = koefficients[1] - koefficients[2];
    return result;
}

double* Divisor::calculate(double *koefficients) {
    if (koefficients[0] != 2) {
        return nullptr;
    }
    auto *result = new double [2];
    result[0] = 1;
    result[1] = koefficients[1] / koefficients[2];
    return result;
}

double* Multiplicator::calculate(double *koefficients) {
    if (koefficients[0] != 2) {
        return nullptr;
    }
    auto *result = new double [2];
    result[0] = 1;
    result[1] = koefficients[1] * koefficients[2];
    return result;
}

double checkSign(double numb, ifstream &file){
    file.seekg(-3, ios::cur);
    double result(numb);
    char c;
    file >> c;
    if (c == '-'){
        result *= -1;
    }
    file.seekg(2, ios::cur);
    return result;
}

double* Quadratic_equation_solver::getKoefsFromFile(ifstream &file) {
    double count(0), koef[3];
    if (!file.eof()){
        file >> koef[0];
        count++;
        file.seekg(8, ios::cur);
        if (!file.eof()){
            file >> koef[1];
            koef[1] = checkSign(koef[1], file);
            count++;
            file.seekg(6, ios::cur);
            if (!file.eof()){
                file >> koef[2];
                koef[2] = checkSign(koef[2], file);
                count++;
                file.seekg(3, ios::cur);
            }
        }
    }
    auto *result = new double [(int)count + 1];
    result[0] = count;
    for (int i = 1; i <= (int)count; i++){
        result[i] = koef[i - 1];
    }
    return result;
}

double *basicOperationsKoefs(ifstream &file){
    double count(0), koefs[2];
    if (!file.eof()){
        file >> koefs[0];
        count++;
        file.seekg(2, ios::cur);
        if (!file.eof()){
            file >> koefs[1];
            count++;
        }
    }
    auto *result = new double [(int)count + 1];
    result[0] = count;
    for (int i = 1; i <= (int)count; i++){
        result[i] = koefs[i - 1];
    }
    return result;
}

double* Additor::getKoefsFromFile(ifstream &file) {
    return basicOperationsKoefs(file);
}


double* Subtractor::getKoefsFromFile(ifstream &file) {
    return basicOperationsKoefs(file);
}

double* Divisor::getKoefsFromFile(ifstream &file) {
    return basicOperationsKoefs(file);
}

double* Multiplicator::getKoefsFromFile(ifstream &file) {
    return basicOperationsKoefs(file);
}


double *solve(const char *filepath, Calculator **calc, int n){
    ifstream f(filepath);
    if (!f){
        return nullptr;
    }
    double code;
    f >> code;
    int i(0);
    while (i < n){
        if (code == calc[i]->getCode()){
            return calc[i]->calculate(calc[i]->getKoefsFromFile(f));
        }
        i++;
    }
    return nullptr;
}

void printArr(double *arr) {
    int n = (int) arr[0];
    for (int i = 1; i <= n; i++) {
        printf("%f ", arr[i]);
    }
}