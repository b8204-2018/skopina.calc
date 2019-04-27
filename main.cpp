#include <iostream>
#include <fstream>
#include "src/calc.h"


using namespace std;


void print(double *array){
    for (int i = 1; i <= (int)array[0]; i++){
        cout << array[i] << " ";
    }
}


int main(int argc, char **argv) {
    if (argc < 2){
        return -1;
    }
    Solver solver;

    Additor add;
    solver.add(add);

    Subtractor sub;
    solver.add(sub);

    Multiplicator mul;
    solver.add(mul);

    Divisor div;
    solver.add(div);

    QuadrEqSolver qes;
    solver.add(qes);

    for (int i = 1; i < argc; i++){
        int code;
        string ex;
        fstream f(argv[i]);
        if (!f){
            cout << "File not found." << endl;
        } else {
            f >> code;
            f.seekg(3, ios::beg);
            getline(f, ex);
            cout << "Expression: " << ex << endl;
            cout << "Solution: ";
            print(solver.solve(code, ex));
            cout << "\n\n" << endl;
        }
    }
    return 0;
}