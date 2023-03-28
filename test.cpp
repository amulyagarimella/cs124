#include <iostream>
#include <cmath>
#include <tuple>
#include <stdlib.h> 
#include <vector>
#include <set>
#include <iostream>
#include <unordered_map>
#include "randomgraph.h"

using namespace std;


int main() {
    std::cout << "Hello World!";

    vector<vector<float>> G[3];

    vector<vector<float>> weights[3];
    for (int i = 0 ; i < 3; i++) {
        weights[i].resize(G[i].size());
    }
    return 0;
}