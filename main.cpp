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
    solver.add(new Additor);
    solver.add(new Subtractor);
    solver.add(new Divisor);
    solver.add(new Multiplicator);
    solver.add(new QuadrEqSolver);
    for (int i = 1; i < argc; i++){
        int code;
        string ex;
        fstream f(argv[i]);
        if (!f){
            cout << "File " << argv[i] << " not found." << endl;
        } else {
            f >> code;
            f.seekg(3, ios::beg);
            getline(f, ex);
            cout << "Expression: " << ex << endl;
            try {
                double *solution = solver.solve(code, ex);
                cout << "Solution: ";
                print(solution);
            } catch (Exception &err){
                cout << err.getError();
            }
            cout << "\n\n" << endl;
        }
    }
    return 0;
}