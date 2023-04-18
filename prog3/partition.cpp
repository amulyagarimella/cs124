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

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0.0, 1.0);

// TODO thread safe random

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
    // srand(time(NULL));
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
    int res = residue(sequence, &signs);

    int res2;
    for (int i = 0; i < max_iter; ++i) {
        generateRandomSigns(&signs2);
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
    // srand(time(NULL));
    int i = 0, j=0;
    while (i == j) {
        i = rand() % n;
        j = rand() % n;
    }
    (*signs)[i] = -(*signs)[i];
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
            float prob = exp(-(res2-res)/cooling(i));
            if (dis(gen) <= prob) {
                signs = signs2;
            }
        }
        res3 = residue(sequence, &signs3);
        if (res3 > residue(sequence, &signs)) {
            // hopefully switching pointers will work
            signs3 = signs;
        }
    }
    return residue(sequence, &signs3);
}


vector<int> generatePrepartition (int num_partitions) {
    vector<int> P (num_partitions);
    for (int i = 0; i < num_partitions; ++i) {
        // p[i] between 0 and n-1
        P[i] = rand() % num_partitions;
    }
    return P;  
}

/*
Essentially A′ is derived by resetting ai to be the sum of all values j with pj = i,
*/
vector<long> * convertPrepartition (vector<long> * sequence, vector<int> * partition, vector<long> * newSequence) {
    int n = sequence->size();

    fill(newSequence->begin(), newSequence->end(), 0);

    for (int j = 0; j < n; ++j) {
        (*newSequence)[(*partition)[j]] += (*sequence)[j];
    }

    return newSequence; 
}

/*
Thinking of all possible solutions as a state space, a natural way to define neighbors of a
solution P is as the set of all solutions that differ from P in just one place. 
The interpretation is that we
change the prepartitioning by changing the partition of one element. 
A random move on this state space
can be defined as follows. Choose two random indices i and j
 from [1, n] with pi  != j and set pi to j.
*/
vector<int> * prepartitionRandomMove (vector<int> * partition, vector<int> * partition2) {
    int n = partition->size();
    int i = 0, j = 0;
    while ((*partition)[i] == j) {
        i = rand() % n;
        j = rand() % n;
    }
    partition2 = partition;
    (*partition2)[i] = j;
    return partition2;
}


// PRR
int prepartitionRepeatedRandom (vector<long> * sequence, int max_iter) {
    int n = sequence->size();
    // srand(time(NULL));
    // cout << "size" << n << "\n";
    vector<int> partition = generatePrepartition(n);
    vector<long> newSequence (n);
    convertPrepartition(sequence, &partition, &newSequence);
    
    int res = karmarkarKarp(&newSequence);
    vector<int> partition2;
    vector<long> newSequence2 (n);
    for (int i = 0; i < max_iter; ++i) {
        partition2 = generatePrepartition(n);
        /*cout << "p2\n";
        for (int i = 0; i < 3; ++i) {
            cout << partition2[i] << "\n";
        } */
        convertPrepartition(sequence, &partition2, &newSequence2);
        int res2 = karmarkarKarp(&newSequence2);
        if (res > res2) {
            res = res2;
        }
    }
    return res;
}


// PHC
int prepartitionHillClimbing (vector<long> * sequence, int max_iter) {
    int n = sequence->size();
    // srand(time(NULL));
    // cout << "size" << n << "\n";
    vector<int> partition = generatePrepartition(n);
    vector<long> newSequence (n);
    convertPrepartition(sequence, &partition, &newSequence);
    int res = karmarkarKarp(&newSequence);
    vector<int> partition2 = partition;
    vector<long> newSequence2 (n);
    int res2;
    for (int i = 0; i < max_iter; ++i) {
        // srand(time(NULL));
        prepartitionRandomMove(&partition, &partition2);
        /*cout << "p2\n";
        for (int i = 0; i < 3; ++i) {
            cout << partition[i] << "\n";
        } */
        convertPrepartition(sequence, &partition2, &newSequence2);
        res2 = karmarkarKarp(&newSequence2);
        if (res > res2) {
            partition = partition2;
        }
    }
    return karmarkarKarp(&newSequence);
}

// PSA TODO!!
/*
int prepartitionSimulatedAnnealing (vector<long> * sequence, int max_iter) {
    int n = sequence->size();
    // srand(time(NULL));
    // cout << "size" << n << "\n";
    vector<int> partition = generatePrepartition(n);
    vector<long> newSequence = convertPrepartition(sequence, &partition);
    int res = karmarkarKarp(&newSequence);
    vector<long> newSequence2;
    for (int i = 0; i < max_iter; ++i) {
        prepartitionRandomMove(&partition);
        newSequence2 = convertPrepartition(sequence, &partition);
        int res2 = karmarkarKarp(&newSequence2);
        if (res > res2) {
            res = res2;
        }
    }
    return res;
}*/


// Preprocessing: TODO
/*
TODO: test
Correctness: ?
*/

// TODO!!!!!!! check srand use
// Main
// ./partition flag algorithm inputfile
int main (int argc, char * argv[]) {
    srand(time(NULL));
    int flag = strtol(argv[1], NULL, 10);
    int algorithm = strtol(argv[2], NULL, 10);

    string inputfile = argv[3];
    ifstream input(inputfile);
    int seq_len = 100;
    vector<long> seq;
    string line;
    for (int i = 0; i < seq_len; ++i) {
        getline(input, line);
        seq.push_back(stol(line, NULL, 10));
    }

    // min=29980 | avg=2191094.1
    
    int max_iter = 25000;

    /*vector<int> example_p = {0, 1, 1, 3, 4};
    vector<long> example_kk = {10,8,7,6,5};
    vector<long> new_kk = convertPrepartition(&example_kk, &example_p);
    for (int i = 0; i < int(new_kk.size()); ++i) {
        cout << new_kk[i] << "\n";
    }*/

    if (algorithm == 0) {
        cout << karmarkarKarp(&seq);
    }
    else if (algorithm == 1) {
        cout << repeatedRandom(&seq, max_iter);
    }
    else if (algorithm == 2) {
        cout << hillClimbing(&seq, max_iter);
    }
    else if (algorithm == 3) {
        cout << simulatedAnnealing(&seq, max_iter);
    }
    else if (algorithm == 11) {
        cout << prepartitionRepeatedRandom(&seq, max_iter);
    }
    else if (algorithm == 12) {
        cout << prepartitionHillClimbing(&seq, max_iter);
    }
}

