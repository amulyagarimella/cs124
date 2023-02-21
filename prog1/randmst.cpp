// import all da stuff
#include <iostream>
#include <cmath>
#include <tuple>
#include <stdlib.h> 
#include <vector>
#include <set>
#include <iostream>
#include <unordered_map>
#include "randomgraph.h"
// #include "randmst.h"

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
struct MST {
    vector <vector<int> > adjList;
};

MST MST_prim (vector<vector<float> > G, int s) {
    vector<float> dist[G.size()];
    vector<int> pre[G.size()];
    MST ans;

    // pseudo said use set for this one
    // Amulya used unorderd map to decrease lookup time
    // a little redundant to store items at ints because item.vertex is redundant
    unordered_map<int, item> visited;

    PriorityQueue H;
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
            // find a better ay to check if w in set
            item w = H.heap[H.positions[w_idx]];
            if (visited.find(w_idx) != visited.end()) {
                float edgeWeight = euclideanDistance(G[v_idx], G[w_idx]);
                if (w.dist > edgeWeight) {
                    w.dist = edgeWeight;
                    w.parentVertex = v_idx;
                }
            }
        }

        // H.pop(); // Do we do this actually tho? i feel like this would pop second smallest so maybe not ideal
    }
    // add to MST
    for (auto x : visited) {
        // todo edge weight calc
        ans.adjList[x.second.parentVertex].push_back(x.first);
    }

    return ans;
};

/*
float MST_krusk (vector<float> point1, vector<float> point2) {
} 
*/

// TODO: return average MST edge weight

int main() {
    PriorityQueue h;
    h.push(1, 0);
    h.push(2, 0);
    h.push(3, -1);
    h.push(4, 5);
    h.pop();
    h.pop();
    h.pop();
    h.pop();
    return 0;
}