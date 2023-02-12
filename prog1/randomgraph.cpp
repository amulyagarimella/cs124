#include <iostream>
#include <cmath>
#include <tuple>
/*
Thoughts
- maybe store adjacency lists as min-heap bintrees for each vertex on edge weight
*/
template <class T>
struct graphD {
    T nodes[];
    


};

struct graph0 {
    int nodes[];

};

struct graph2 {

};

struct graph3{

};

struct graph4 {

};

// TODO: what to do with overflow? -> prob unlikely bc small #s
template <class T>
float euclideanDistance (T (&points)[2]) {
    float sumDistSquared = 0;
    for (int i : std::tuple_size_v<T>) {
        sumDistSquared += (points[0][i] - points[1][i]) ** 2;
    }
    return sqrt(sumDistSquared);
}

int generateGraph (int n, int dim) {
    /*
    input: # points, # dimensions
    output: 
        - adjacency list
        - edge weights
    */
    // rand generate pts of size dim
}