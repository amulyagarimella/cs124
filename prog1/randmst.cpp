#include <iostream>
#include <cmath>
#include <tuple>
#include <stdlib.h> 
#include <vector>
#include <set>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <math.h>
#include "randomgraph.h"
using namespace std;

class edge {
    public:
        int parentVertex;
        int childVertex;
        float weight;
};

bool compareEdges (edge c1, edge c2) {
    if (c1.weight < c2.weight) {
        return true;
    }
    return false;
}

class UnionFind {
    public:
        vector<int> parent;
        vector<int> rank;

        void makeSet (long size) {
            parent.resize(size);
            rank.resize(size, 0);
            
            for (long i = 0; i < size; ++i) {
                parent[i] = i;
            }
        }

        int find (long v) {
            if (parent[v] != v) {
                parent[v] = find(parent[v]);
                return parent[v];
            }
            return v;
        }
        
        void link (long x, long y) {
            if (rank[x] > rank[y]) {
                swap(x,y);
            }
            if (rank[x] == rank[y]) {
                rank[y] += 1;
            }
            parent[x] = y;
            rank[x] += rank[y];
        }


        void unite (long x, long y) {
            link(find(x), find(y));
        }
        
};

float MST_krusk (int dim, long size = 0, vector<vector<float> > *G = NULL) {
    long s = size;
    if (G != NULL) {
        s = G->size();
    }
    vector<edge> edges;
    vector<edge> MST;
    srand (time(NULL));

    float prune_lim = 0.1;
    if (dim == 0) {
        prune_lim = exp(-1*s) + 0.0084;
    } else if (dim == 2) {
        prune_lim = exp(-1*s) + 0.054;
    } else if (dim == 3) {
        prune_lim = exp(-1*s) + 0.135;
    } else if (dim == 4) {
        prune_lim = exp(-1*s) + 0.219;
    }
    
    edge temp;
    if (s == 0) {
        return {};
    }
    
    for (int i = 0; i < s; ++i) {
        for (int j = i + 1; j < s; ++j) {
            if (i == j) { 
                continue;
            }
            if (G != NULL) {
                temp.weight = euclideanDistance((*G)[i], (*G)[j]);
            }
            else {
                temp.weight = (float) rand() / (RAND_MAX);
            }
            
            if (temp.weight < prune_lim) {
                temp.parentVertex = i;
                temp.childVertex = j;
                edges.push_back(temp);
                temp.parentVertex = j;
                temp.childVertex = i;
                edges.push_back(temp);
            }
        }
    }


    // 2: sort edge weights in inc order
    sort(edges.begin(), edges.end(), compareEdges);
    
    UnionFind u;
    
    u.makeSet(s);
    float sum = 0;
    float maxWeight = 0;
    for (long i = 0; i < edges.size(); ++ i) {
        edge e = edges[i];
        int v = e.parentVertex;
        int w = e.childVertex;
        if (u.find(v) != u.find(w)) {
            float weight = e.weight;
            MST.push_back(e);
            sum += weight;
            if (weight > maxWeight) {
                maxWeight = weight;
            }
            if (MST.size() == s - 1) {
                break;
            }
            u.unite(v,w);
            if (i != edges.size()) {
                if (v == edges[i+1].childVertex && w == edges[i+1].parentVertex) {
                    ++i;
                }
            }
        }
    }

    if (MST.size() != s - 1) {
        // return exn
    }

    if (dim != 0) {
        G->clear();
    }

    return sum;
} 


int main(int argc, char* argv[]) {
    int n = strtol(argv[2], NULL, 10);
    int ntrials = strtol(argv[3], NULL, 10);
    int dim =  strtol(argv[4], NULL, 10);
    float sumtrials = 0;
    for (int i = 0; i < ntrials; i++) {
        if (dim == 0) {
            sumtrials += MST_krusk (0, n);
        }
        else {
            vector<vector<float> > G = generateGraph(n, dim);
            sumtrials += MST_krusk (dim, n, &G);
        }
    }

    cout << sumtrials/ (float) ntrials << " " << n <<  " " << ntrials << " " << dim;
    return 0;
};