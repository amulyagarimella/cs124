#include <iostream>
#include <cmath>
#include <stdlib.h> 
#include <vector>
#include "randomgraph.h"
using namespace std;

// TODO: what to do with overflow? -> prob unlikely bc small #s
float euclideanDistance (vector<float> point1, vector<float> point2) {
    float sumDistSquared = 0;
    for (int i = 0; i < point1.size(); ++i) {
        sumDistSquared += pow(point1[i] - point2[i], 2);
    }
    return sqrt(sumDistSquared);
}

// TODO: test, add debug
// template <int n, int dim>
// TODO figure out dim0/dim1 case @Amulya
vector<vector<float> > generateGraph (int n, int dim) {
    srand (time(NULL));

    // initialize nodes
    vector<vector<float> > G;
    G.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < dim; ++j) {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            G[i].push_back(r);
        }
    }
    return G;
}