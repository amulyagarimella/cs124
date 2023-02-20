#include <iostream>
#include <cmath>
#include <stdlib.h> 
#include <vector>

namespace std {
    struct CompleteGraph {
        vector<vector<float> > nodes;
    };

    // TODO: what to do with overflow? -> prob unlikely bc small #s
    float euclideanDistance (vector<float> point1, vector<float> point2);
    CompleteGraph generateGraph (int n, int dim);
}