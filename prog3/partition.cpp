#include <iostream> 
#include <algorithm> 
#include <vector>
#include <tuple>

using namespace std;

// Karmarkar-Karp algorithm
/*
TODO: test
Correctness: ?
*/
tuple<int,int> findMaxes (vector<int> * sequence) {
    int n = sequence->size();
    int idx_m = 0; 
    int idx_sm = 0;
    for (int i = 0; i < n; i++) {
        int c = (*sequence)[i];
        if (c > (*sequence)[idx_m]) {
            idx_m = i;
        }
    }
    for (int i = 0; i < n && i != idx_m; i++) {
        int c = (*sequence)[i];
        if (c > (*sequence)[idx_sm]) {
            idx_sm = i;
        }
    }
    return make_tuple(idx_m, idx_sm);
}
int karmarkarKarp (vector<int> * sequence) {
    tuple<int,int> maxes =  findMaxes(sequence);
    int m = (*sequence)[get<0>(maxes)];
    int sm = (*sequence)[get<1>(maxes)];
    if (sm == 0) {
        return m;
    }
    (*sequence)[get<0>(maxes)] = m - sm;
    (*sequence)[get<1>(maxes)] = 0;
    return karmarkarKarp(sequence);
}

// Repeated random
/*
TODO: test
Correctness: ?
*/
vector<int> * generateRandomSigns (vector<int> * signs) {
    int n = signs->size();
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        int val = rand() % 2;
        if (val == 0) {
            val = -1;
        }
        (*signs)[i] = val;
    }
    return signs;
}

int residue (vector<int> * sequence, vector<int> * signs) {
    int n = sequence->size();
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res += (*sequence)[i] * (*signs)[i];
    }
    return res;
}

int repeatedRandom (vector<int> * sequence, int max_iter) {
    int n = sequence->size();
    vector<int> signs (n);
    vector<int> signs2 (n);
    generateRandomSigns(&signs);
    int res, res2;
    for (int i = 0; i < max_iter; ++i) {
        generateRandomSigns(&signs2);
        res = residue(sequence, &signs);
        res2 = residue(sequence, &signs2);
        if (res > res2) {
            // hopefully switching pointers will work
            signs = signs2;
        }
    }
    
}

// Hill climbing
/*
TODO: test
Correctness: ?
*/

vector<int> * randomMove (vector<int> * signs) {
    int n = signs->size();
    srand(time(NULL));
    int i = rand() % n;
    (*signs)[i] = -(*signs)[i];
    int j = rand() % n;
    int coinflip = rand() % 2;
    if (coinflip == 0) {
        (*signs)[j] = -(*signs)[j];
    }
    return signs;
}

vector<vector<vector<int> > > generateGraph (int n) {
    // TODO
    return 
}


int hillClimbing (vector<int> * sequence, int max_iter) {
    int n = sequence->size();
    vector<int> signs (n);
    generateRandomSigns(&signs);
    vector<int> signs2 (signs);
    // signs2 = signs;
    int res, res2;
    for (int i = 0; i < max_iter; ++i) {
        randomMove(&signs2);
        res = residue(sequence, &signs);
        res2 = residue(sequence, &signs2);
        if (res > res2) {
            // hopefully switching pointers will work
            signs = signs2;
        }
    }
}

// Simulated annealing: TODO
/*
TODO: test
Correctness: ?
*/
int simulatedAnnealing () {
    
}

// Preprocessing: TODO
/*
TODO: test
Correctness: ?
*/

// Main: TODO


