#include <iostream>
#include <cmath>
#include <stdlib.h> 
#include <vector>

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
            float r = ((float) rand() / (RAND_MAX));
            G[i].push_back(r);
        }
    }
    return G;
}

int main () {
    vector<vector<float> > test;
    test = generateGraph(3, 2);
    for (int i = 0; i < test.size(); ++i) {
        for (int j = 0; j < test[i].size(); ++j) {
            cout << test[i][j] << ' '; 
        }
        cout << "\n";
    }
    return 0;
}