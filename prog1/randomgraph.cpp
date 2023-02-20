#include <iostream>
#include <cmath>
#include <tuple>
#include <stdlib.h> 
#include <vector>
using namespace std;

#ifndef MYSTRUCT_H
#define MYSTRUCT_H

struct CompleteGraph {
    // do we want nodes as int or float? am leaning int but do we need float for math reasons
    vector<vector<float> > nodes;
    vector<vector<float> > edges;
};

#endif

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
CompleteGraph generateGraph (int n, int dim) {
    srand (time(NULL));

    // initialize nodes
    CompleteGraph G;
    G.nodes.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < dim; ++j) {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            G.nodes[i].push_back(r);
        }
    }
    // pairwise edge weights
    G.edges.resize(n);
    for (int i = 0; i < n; ++i) {
        G.edges[i].resize(n); 
        
        // need to resize since pushing only will lead to off-by-one (since no self edges)
        for (int j = i + 1; j < n; ++j) {
            float weight = euclideanDistance(G.nodes[i], G.nodes[j]);
            G.nodes[i][j] = weight;
            G.nodes[j][i] = weight;
        }
    }
    return G;
}

int main() {
    return 0;
}