// import all da stuff
#include <iostream>
#include <cmath>
#include <tuple>
#include <stdlib.h> 
#include <vector>
#include <set>
#include "mystruct.h"
using namespace std;

// define some structure to store MST, diff from completeGraph - do we need to differentiate tho?
struct MST {
    vector<vector<float> > nodes;
    vector<vector<float> > edges;
};

// Programming problem set 1
// Nadine Han + Amulya Garimella

// TODO: Generate random graph of dim 0, 2, 3, 4
/* 
We will be considering complete, undirected graphs. A graph with n vertices is
complete if all n-choose-2 pairs of vertices are edges in the graph
(can an adjanceny matrix work? rather than a linked list we have to look thru???)

i believe adj should work? i don't see why not as long as we get the right results
since we are accessing this matrix a lot it might make more sense than a linked list

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

// TODO: MST function
// store potential edges to add in min heap
// k(n) estimator

// prioqueue w/ special item element

struct item {
    int vertex;
    int dist;
};

class PriorityQueue {
    item value;
    vector<item> heap;

    void bubble_up(int i) {
        // shortcut if the root node is inputted
        if (i == 0) return;

        int parent = (i - 1) / 2;

        if (heap[i] > heap[parent]) {
            swap(heap[i], heap[parent]);
            bubble_up(parent);
        }
    }

    void bubble_down(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        // get the largest child
        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        // do the actual comparison
        if (largest != i) {
            swap(heap[i], heap[largest]);
            bubble_down(largest);
        }
    }

    public:
        void push(int v, int d) {
            value.vertex = v;
            value.dist = d;
            heap.push_back(value);
            bubble_up(heap.size() - 1);
        }

        int top() {
            return heap[0];
        }

        void pop() {
            heap[0] = heap.back();
            heap.pop_back();
            bubble_down(0);
        }

        bool empty() const {
            return heap.empty();
        }
};

// prim's
auto MST_prim (CompleteGraph G, int s) {
    vector<float> dist;
    vector<int> vertices;
    set<int> visited;

    PriorityQueue H;
    H.push(s, 0);

    for (int i = 0; i < H.size(); ++i) {

    }

dist[v] := ∞, prev[v] :=nil
rof
dist[s] := 0
while H 6= 0/
v := deletemin(h)
S := S∪ {v}
for (v,w) ∈ E and w ∈ V(G) \ S do
if dist[w] > length(v,w)
dist[w] := length(v,w), prev[w] := v, insert(w,dist[w],H)
fi
rof
end while end Prim
}

float MST_krusk (vector<float> point1, vector<float> point2) {

}

// TODO: return average MST edge weight