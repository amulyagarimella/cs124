// import all da stuff
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
#include "test.h"

// #include "randomgraph.cpp"
using namespace std;
// TODO (low priority) place priorityqueue, vertex, and item into separate file

// Programming problem set 1
// Nadine Han + Amulya Garimella

// TODO: Generate random graph of dim 0, 2, 3, 4
/* 
We will be considering complete, undirected graphs. A graph with n vertices is
complete if all n-choose-2 pairs of vertices are edges in the graph
(can an adjanceny matrix work? rather than a linked list we have to look thru???)

i believe adj should work? i don't see why not as long as we get the right results
since we are accessing this matrix a lot it might make more sense than a linked list
Yes and we don't waste that much space because fully connected.

DIM 0: Complete graphs on n vertices, where the weight of each edge is a real
number chosen uniformly at random on [0, 1].

DIM 1: I guess we ignore this lol... would this just be points on a numberline? yea it seems like

DIM 2: Complete graphs on n vertices, where the vertices are points chosen
uniformly at random inside the unit square. (That is, the points are (x,y),
with x and y each a real number chosen uniformly at random from [0, 1].)
The weight of an edge is just the Euclidean distance between its endpoints.

DIM 3, 4: Complete graphs on n vertices, where the vertices are points chosen 
uniformly at random inside the unit cube (3 dimensions) and hypercube (4 
dimensions). As with the unit square case above, the weight of an edge is just 
the Euclidean distance between its endpoints.
*/

// for denser graphs (higher dimensions) we should use prim, for less we should use krus 
// also if edges happen to be sorted we should mayb use kruskal
// i think this means we might want to implement both and apply them depending on the dims? lmk what u think
// Bigly agree

// TODO: MST function
// store potential edges to add in min heap
// k(n) estimator

// do we need to define some structure to store MST, diff from completeGraph? they seem to be same type tho
// struct MST {
//     vector<vector<float> > nodes;
//     vector<vector<float> > edges;
// };
// I think MST should be different - we should NOT store MST edges in an adjacency MATRIX

// do we use this struct anywhere?
/*
struct vertex {
    int key;
    int parent_ptr;
};
*/

// prioqueue w/ special item element - must manually implement as per pset specs
// structure is {s : 0} where s is the vertex and 0 is dist
// see sect 2 notes for pseudo: https://drive.google.com/file/d/1yg2569DDp1bDsvtCP0y-BRntkAG6hndr/view

// item.vertex should refer to the index of the node imo
class item {
    // should pt to the vertex not store it b/c unnecessary space probs
    public:

        int vertex;
        int dist;
        // TODO replace with parent POINTER
        int parentVertex;

        int compare (item item2) {
            if (dist == item2.dist) {
                return 0;
            }
            else if (dist < item2.dist) {
                return -1;
            }
            else {
                return 1;
            }
        };

        void print() {
            cout << "(vertex " << vertex << ", dist " << dist << ")";
        }
};

class PriorityQueue {
    // initialize this for push function
    public: 
        item value;
        vector<item> heap;
        // TODO maybe make long
        vector<int> positions;

        // debugging purpose
        void print_heap() {
            cout << "[";
            for (int i = 0; i < heap.size(); ++i) {
                heap[i].print();
            }
            cout << "]\n";
        }

        void set_size (int n) {
            positions.resize(n);
        }

        void push(int v, int d) {
            value.vertex = v;
            value.dist = d;
            heap.push_back(value);
            positions[v] = heap.size() - 1;
            print_heap();
            bubble_up(heap.size() - 1);
            print_heap();
        }

        item top() {
            return heap[0];
        }

        item pop() {
            item popped = heap[0];
            heap[0] = heap.back();
            positions[popped.vertex] = -1;
            heap.pop_back();
            bubble_down(0);
            return popped;
        }

        bool empty() const {
            // set all to NULL
            positions.empty();
            return heap.empty();
        }

    private:
        void bubble_up(int i) {
        // shortcut if the root node is inputted
        if (i == 0) return;

        int parent = (i - 1) / 2;

            if (heap[i].compare(heap[parent]) < 0) {
                swap(heap[i], heap[parent]);
                bubble_up(parent);
            }
        }

        void bubble_down(int i) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int min = i;

            // get the largest child
            if (left < heap.size() && heap[left].compare(heap[min]) < 0) {
                min = left;
            }

            if (right < heap.size() && heap[right].compare(heap[min]) < 0) {
                min = right;
            }

            // do the actual comparison
            if (min != i) {
                positions[min] = i;
                positions[i] = min;
                swap(heap[i], heap[min]);
                bubble_down(min);
            }
        }

};

// prim's - see lecture 6 pseudocode: https://drive.google.com/file/d/1ZZUqY1_7V940y8N7-E3wuJTyUqiXPu80/view

// todo - inner vector of ints or of items?
/*
struct MST {
    vector <vector<int> > adjList;
};
*/
template<typename T>
float MST_prim (T G, int s) {
    vector<float> dist[G.size()];
    vector<int> pre[G.size()];

    // pseudo said use set for this one
    // Amulya used unorderd map to decrease lookup time
    // a little redundant to store items at ints because item.vertex is redundant
    unordered_map<int, item> visited;

    PriorityQueue H;
    H.set_size(G.size());
    H.push(s, 0);
    visited[s] = H.heap[0];

    for (int i = 0; i < G.size(); ++i) {
        // replacing infty with int_max! lmk if u disagree tho - idk how this will interact with float, but we'll see
        H.push(i, INT_MAX);
        // TODO add order to graphs? do we need this?
        // pre[i] = null;
    }
    while (!H.empty()) {
        item v = H.pop();
        visited[v.vertex] = v;
        int v_idx = v.vertex;
        for (int w_idx = 0; w_idx < G.size() && w_idx != v_idx; ++w_idx) {
            item w = H.heap[H.positions[w_idx]];
            if (visited.find(w_idx) != visited.end()) {
                float edgeWeight = euclideanDistance(G[v_idx], G[w_idx]);
                if (w.dist > edgeWeight) {
                    w.dist = edgeWeight;
                    w.parentVertex = v_idx;
                }
            }
        }

    }
    // add to MST
    int sum = 0;
    int numEdges = 0;
    for (auto x : visited) {
        // todo edge weight calc
        // ans.adjList[x.second.parentVertex].push_back(x.first);
        sum += euclideanDistance(G[x.first], G[x.second.parentVertex]);
        ++numEdges;
    }
    return sum / numEdges;
    // return ans;
};

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

        // this will also work on 0 dim
        void makeSet (int size) {
            parent.resize(size);
            rank.resize(size, 0);
            
            for (int i = 0; i < size; ++i) {
                parent[i] = i;
            }
        }

        int find (int v) {
            if (parent[v] != v) {
                parent[v] = find(parent[v]);
                return parent[v];
            }
            return v;
        }
        
        void link (int x, int y) {
            if (rank[x] > rank[y]) {
                swap(x,y);
            }
            if (rank[x] == rank[y]) {
                rank[y] += 1;
            }
            parent[x] = y;
            rank[x] += rank[y];
        }


        void unite (int x, int y) {
            link(find(x), find(y));
        }
        
};

// vector -> forward list
vector<float> MST_krusk (int dim, int size = 0, vector<vector<float> > G = {}) {
    int s = max(size, (int) G.size());
    vector<edge> edges;
    edges.reserve(s*s);
    vector<edge> MST;
    MST.reserve(s-1);
    srand (time(NULL));

    // float prune_lim = log2(s) * max(1,dim) / (float) pow(10,log10(s)-2);
    // float prune_lim = 10.;
    float prune_lim = exp(0.9 * s) + (5.74 * pow(10,13));
    // cout << prune_lim;
    /*int s = G.size();
    if (s == 0) {
        s = size;
    }*/
    edge temp;
    // 1: calc and store edge weights of given graph if not dim 0 - we might have repetition if the input will always be undirected complete
    if (s == 0) {
        return {};
    }
    
    for (int i = 0; i < s; ++i) {
        for (int j = i + 1; j < s; ++j) {
            if (i == j) { 
                continue;
            }
            if (dim > 0) {
                // cout << "weight: " << temp.weight << "\n";
                temp.weight = euclideanDistance(G[i], G[j]);
            }
            else {
                temp.weight = (float) rand() / (RAND_MAX);
            }
            // pruning (first pass attempt)
            
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

    // print edges
    // for (int i = 0; i < edges.size(); ++i) {
    //     cout << edges[i].parentVertex << ' '; 
    //     cout << edges[i].childVertex << ' '; 
    //     cout << edges[i].weight << ' '; 
    //     cout << "\n";
    // }

    // 2: sort edge weights in inc order
    // return {1};
    sort(edges.begin(), edges.end(), compareEdges);
    
    // 3: iterate through edges
    UnionFind u;
    
    u.makeSet(s);
    float sum = 0;
    float maxWeight = 0;
    for (int i = 0; i < edges.size(); ++ i) {
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
            u.unite(v,w);
            if (MST.size() == s - 1) {
                break;
            }
            if (i != edges.size()) {
                if (v == edges[i+1].childVertex && w == edges[i+1].parentVertex) {
                    ++i;
                }
            }
        }
    }

    // print MST
    // for (int i = 0; i < MST.size(); ++i) {
    //     cout << MST[i].parentVertex << ' '; 
    //     cout << MST[i].childVertex << ' '; 
    //     cout << MST[i].weight << ' '; 
    //     cout << "\n";
    // }

    return {sum, sum/MST.size(), maxWeight, (float) MST.size()};
} 


int main(int argc, char* argv[]) {
    int n = strtol(argv[2], NULL, 10);
    int ntrials = strtol(argv[3], NULL, 10);
    int dim =  strtol(argv[4], NULL, 10);
    /*cout << dim << "\n";
    cout << n << "\n";
    cout << ntrials << "\n";*/
    vector<float> res;
    res.reserve(4);
    if (dim == 0) {
        res = MST_krusk (0, n);
    }
    else {
        vector<vector<float> > G = generateGraph(n, dim);
        res = MST_krusk (dim, n, G);
    }
    
    for (int i = 0; i < ntrials; ++i) {
        cout << res[0] << "," << res[1] <<  "," << res[2] << "," << res[3] << "\n";
    }
    return 0;
};



/* TODO
- check to make sure it accts for cycles <- i dont rlly understand this. There are going to be cycles in this graph bc all graphs we are considering are complete and undirected

- add edge pruning from hint: 
    - then graph the weights of all of the maximum edges in those examples (using python or sumn probs)
    - find a line of best fit to determine the trend of the weights relative to size
    - take that function and double it (so that the edges we prune aren't too close to normal weights and will only catch OUTLIERS)
    - return exception if we cannot create MST

- check for more optimizations (path compression, union by rank,

- also figure out the makefile situation ? also some of the commands are preventing me from running randomgraph for permission reasons -_- idek why
*/

/* DONE - Amulya
key functionality
- works on 0dim graphs
- remove graph generation functionality - now generate vertices on the fly to save space + time ~ remaining TODO = code cleanup

edge pruning
- wrote python script to test
    - strategy from andrew is do a bunch of test graph inputs in increasing size
- added tenative pruning

optimizations
- also did we repeat the edges??? in our calc of those) -> cut forloop in half
- I think we alr do the union by rank and path compression

makefile
- will o3 mess it up? o3 works for me

etc.
- command line interface to comply with guidelines

WRITEUP
part 1
- code to generate table with sizes and total weights is complete
- my function guess is 

part 2 
- 

*/