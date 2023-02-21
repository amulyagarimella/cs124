#include <iostream>
#include <cmath>
#include <stdlib.h> 
#include <vector>

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

// TODO: what to do with overflow? -> prob unlikely bc small #s
float euclideanDistance (std::vector<float> point1, std::vector<float> point2);
std::vector<std::vector<float> > generateGraph (int n, int dim);

#endif