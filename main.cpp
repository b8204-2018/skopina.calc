#include <iostream>
#include "src/calc.h"

using namespace std;

int main() {
    Additor add;
    Subtractor sub;
    Quadratic_equation_solver qes;
    Divisor div;
    Multiplicator mul;
    Calculator *arr[] = {&add, &sub, &qes, &div, &mul};
    const char quadr[] = "C:\\Users\\super hacka\\Desktop\\c++\\calc\\examples\\quadr_example";
    const char addition[] = "C:\\Users\\super hacka\\Desktop\\c++\\calc\\examples\\add_example";
    const char subtr[] = "C:\\Users\\super hacka\\Desktop\\c++\\calc\\examples\\sub_example";
    const char mult[] = "C:\\Users\\super hacka\\Desktop\\c++\\calc\\examples\\mul_example";
    const char divis[] = "C:\\Users\\super hacka\\Desktop\\c++\\calc\\examples\\div_example";
    double *result = solve(quadr, arr, 5);
    printf("Quadratic equation's roots: ");
    printArr(result);
    printf("\n");

    result = solve(addition, arr, 5);
    printf("Addition is: ");
    printArr(result);
    printf("\n");

    result = solve(subtr, arr, 5);
    printf("Subtraction is: ");
    printArr(result);
    printf("\n");

    result = solve(mult, arr, 5);
    printf("Multiplication is: ");
    printArr(result);
    printf("\n");

    result = solve(divis, arr, 5);
    printf("Division is: ");
    printArr(result);
    printf("\n");
    return 0;

}