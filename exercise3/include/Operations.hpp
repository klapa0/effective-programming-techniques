#pragma once

#include <vector>
#include <cmath>
#include <iostream>

typedef double (*Operation)(std::vector<double>);

// Functions
double add(std::vector<double> vector) { return vector[0]+vector[1]; }
double subtract(std::vector<double> vector) { return vector[0] - vector[1]; }
double multiply(std::vector<double> vector) { return vector[0] * vector[1]; }
double divide(std::vector<double> vector) { 
    if (vector[1] != 0) return vector[0] / vector[1]; 
    std::cout<<"Division by zero"<<"\n";
    return -1;
}
double cosinus(std::vector<double> vector){return std::cos(vector[0]);}
double sinus(std::vector<double> vector){return std::sin(vector[0]);}