#include <iostream>
#include <cmath>
#include <stdlib.h> 
#include <vector>

using namespace std;
struct CompleteGraph {
    // do we want nodes as int or float? am leaning int but do we need float for math reasons
    vector<vector<float> > nodes;
    vector<vector<float> > edges;
};

// TODO: what to do with overflow? -> prob unlikely bc small #s
float euclideanDistance (vector<float> point1, vector<float> point2);
// TODO: test, add debug
// template <int n, int dim>
// TODO figure out dim0/dim1 case @Amulya
CompleteGraph generateGraph (int n, int dim);