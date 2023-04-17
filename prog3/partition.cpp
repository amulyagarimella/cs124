#include <iostream> 
#include <algorithm> 
#include <vector>
#include <tuple>
#include <tgmath.h>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

// Karmarkar-Karp algorithm
/*
TODO: test
Correctness: ?
*/

/*tuple<int,int> findMaxes (vector<int> * sequence) {
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
}*/

int karmarkarKarp (vector<long> * sequence) {
    priority_queue<long> pq (sequence->begin(), sequence->end());
    /*int m = sequence->back();
    sequence->pop_back();
    int sm = sequence->back();
    sequence->pop_back();*/
    long m, sm;
    bool done = false;
    // todo while
    while (!done) {
        m = pq.top();
        pq.pop();
        sm = pq.top();
        pq.pop();
        pq.push(m-sm);
        pq.push(0);
        if (sm == 0) {
            done = true;
        }
    }
    /*for (int i = 0; i < sequence->size(); ++i) {
        cout << (*sequence)[i] << "\n";
    }*/
    return m;
}

// Repeated random
/*
TODO: test
Correctness: ?
*/

// overwrite provided sequence of signs with new ones
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

int residue (vector<long> * sequence, vector<int> * signs) {
    int n = sequence->size();
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res += (*sequence)[i] * (*signs)[i];
    }
    return abs(res);
}

int repeatedRandom (vector<long> * sequence, int max_iter) {
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
    return residue(sequence, &signs);
}

// Hill climbing
/*
TODO: test
Correctness: ?
*/

// overwrite provided sequence of signs with random move
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

// should return vector<vector<vector<int> > > 

/*
void generateGraph (int n) {
    // TODO
    return;
}*/

// TODO better way to generate/change random

int hillClimbing (vector<long> * sequence, int max_iter) {
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
    return residue(sequence, &signs);
}

float cooling (int iter) {
    int pwr = int(iter/300);
    return pow(10,10)*pow(0.8,pwr);
}

// Simulated annealing: TODO
/*
TODO: test
Correctness: ?
*/
// TODO: recursion
int simulatedAnnealing (vector<long> * sequence, int max_iter) {
    int n = sequence->size();
    vector<int> signs (n);
    generateRandomSigns(&signs);
    vector<int> signs2 (signs);
    vector<int> signs3 (signs);
    int res, res2, res3 = 0;
    res = residue(sequence, &signs);
    res2 = residue(sequence, &signs2);
    for (int i = 0; i < max_iter; ++i) {
        randomMove(&signs2);
        if (res > res2) {
            // hopefully switching pointers will work
            signs = signs2;
        }
        else {
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.0, 1.0);
            float prob = exp(-(res2-res)/cooling(i));
            if (dis(gen) <= prob) {
                signs = signs2;
            }
        }
        // res3 = residue(sequence, &signs3);
        if (res3 > residue(sequence, &signs)) {
            // hopefully switching pointers will work
            signs3 = signs;
        }
    }
    return residue(sequence, &signs3);
}



// Preprocessing: TODO
/*
TODO: test
Correctness: ?
*/

// Main: TODO
// ./partition flag algorithm inputfile
int main (int argc, char * argv[]) {
    int flag = strtol(argv[1], NULL, 10);
    int algorithm = strtol(argv[2], NULL, 10);
    string inputfile = argv[3];
    ifstream input(inputfile);
    int seq_len = 100;
    vector<long> seq (seq_len);
    string line;
    for (int i = 0; i < seq_len; ++i) {
        getline(input, line);
        seq.push_back(stol(line, NULL, 10));
    }
    
    int max_iter = 25000;

    if (algorithm % 10 == 0) {
        cout << karmarkarKarp(&seq);
    }
    else if (algorithm % 10 == 1) {
        cout << repeatedRandom(&seq, max_iter);
    }
    else if (algorithm % 10 == 2) {
        cout << hillClimbing(&seq, max_iter);
    }
    else if (algorithm % 10 == 3) {
        cout << simulatedAnnealing(&seq, max_iter);
    }
}

