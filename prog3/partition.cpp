#include <iostream> 
#include <algorithm> 
#include <vector>
#include <tuple>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <thread>
#include <cmath>
#include <time.h>
#include <limits.h>
#include <tgmath.h>

using namespace std;

// thread safe random
// static mt19937* generator = nullptr;
random_device rd;
mt19937_64 eng(rd());

// random integer gen
int intRand(const int & min, const int & max) {
    uniform_int_distribution<int> distribution(min, max);
    return distribution(eng);
}

// random real num. gen
float realRand(const float & min, const float & max) {
    uniform_int_distribution<unsigned long long> distribution(min, max);
    return distribution(eng);
}

// random long long gen
long long longlongRand (const long long & min, const long long & max) {
    uniform_int_distribution<unsigned long long> distribution(min, max);
    return distribution(eng);
}

// random long gen
long longRand (const long & min, const long & max) {
    uniform_int_distribution<unsigned long> distribution(min, max);
    return distribution(eng);
}

// Karmarkar-Karp w/ bin heap
long karmarkarKarp (vector<long> * sequence) {
    priority_queue<long> pq (sequence->begin(), sequence->end());

    long m, sm;
    bool done = false;

    // run until residue form
    while (!done) {
        // take top 2 elements
        m = pq.top();
        pq.pop();
        sm = pq.top();
        pq.pop();

        // add diff & 0
        pq.push(m-sm);
        pq.push(0);

        if (sm == 0) {
            done = true;
        }
    }

    return m;
}

// Helper Function: Residue
long long residue (vector<long> * sequence, vector<int> * signs) {
    int n = sequence->size();
    long long res = 0;

    // sum over sequence
    for (int i = 0; i < n; ++i) {
        res += (*sequence)[i] * (long long) (*signs)[i];
    }

    return abs(res);
}

// Helper Function: Repeated Random
vector<int> * generateRandomSigns (vector<int> * signs) {
    int n = signs->size();
    fill(signs->begin(), signs->end(), 0);
    
    for (int i = 0; i < n; ++i) {
        int val = intRand(0,1);
        if (val == 0) {
            val = -1;
        }
        (*signs)[i] = val;
    }

    return signs;
}

// Repeated Random
long long repeatedRandom (vector<long> * sequence, int max_iter) {
    int n = sequence->size();
    vector<int> signs (n);
    vector<int> signs2 (n);

    // initial random sol
    generateRandomSigns(&signs);

    // initial res
    long long res = residue(sequence, &signs);

    long long res2;

    for (int i = 0; i < max_iter; ++i) {

        // new random sol & res
        generateRandomSigns(&signs2);
        res2 = residue(sequence, &signs2);

        if (res > res2) {
            res = res2;
        }
    }
    return res;
}

// Helper Function: Hill Climbing
vector<int> * randomMove (vector<int> * signs, vector<int> * signs2) {
    int n = signs->size();

    *signs2 = *signs;

    int i = 0, j = 0;
    // re-generate i & j until different
    while (i == j) {
        i = intRand(0,n-1);
        j = intRand(0,n-1);
    }
    
    (*signs2)[i] = -(*signs2)[i];

    int coinflip = intRand(0,1);
    if (coinflip == 0) {
        (*signs2)[j] = -(*signs2)[j];
    }

    return signs2;
}

// Hill Climbing
long long hillClimbing (vector<long> *sequence, int max_iter) {
    int n = sequence->size();

    // initial random sol
    vector<int> signs (n);
    generateRandomSigns(&signs);

    vector<int> signs2 (signs);
    long long res = residue(sequence, &signs), res2;

    for (int i = 0; i < max_iter; ++i) {
        // find neighbor
        randomMove(&signs, &signs2);

        res = residue(sequence, &signs);
        res2 = residue(sequence, &signs2);

        if (res > res2) {
            signs = signs2;
            res = res2;
        }
    }
    return res;
}

// Helper function: Simulated Annealing
float cooling (int iter) {
    float pwr = floor(iter / 300);
    return pow(10, 10) * pow(0.8, pwr);
}

// Simulated Annealing
long long simulatedAnnealing (vector<long> * sequence, int max_iter) {
    int n = sequence->size();

    // initial sol
    vector<int> signs (n);
    generateRandomSigns(&signs);

    vector<int> signs2 (signs), signs3 (signs);

    long long res = residue(sequence, &signs), res2 = 0, res3 = 0;

    for (int i = 0; i < max_iter; ++i) {
        // s'
        randomMove(&signs, &signs2);
        res2 = residue(sequence, &signs2);

        if (res > res2) {
            res = res2;
            signs = signs2;
        }

        else {
            float prob = exp(-(res2-res)/cooling(i));
            if (realRand(0.0,1.0) <= prob) {
                res = res2;
                signs = signs2;
            }
        }

        // s''
        res3 = residue(sequence, &signs3);
        if (res3 > residue(sequence, &signs)) {
            signs3 = signs;
        }
    }

    return residue(sequence, &signs3);
}


// PART 2: PREPARTITIONING

// Helper Functions
vector<int> generatePrepartition (int num_partitions) {
    vector<int> P (num_partitions);

    for (int i = 0; i < num_partitions; ++i) {
        // p[i] between 0 and n-1
        P[i] = intRand(0,num_partitions-1);
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
void prepartitionRandomMove (vector<int> * partition, vector<int> * partition2) {
    int n = partition->size();
    *partition2 = *partition;
   
    int i = intRand(0,n-1), j = intRand(0,n-1);
    while ((*partition)[i] == j) {
        i = intRand(0,n-1);
        j = intRand(0,n-1);
    }

    (*partition2)[i] = j;
    
    return;
}


// PRR
long prepartitionRepeatedRandom (vector<long> * sequence, int max_iter) {
    int n = sequence->size();

    // initial sol
    vector<int> partition = generatePrepartition(n);
    vector<long> newSequence (n);
    convertPrepartition(sequence, &partition, &newSequence);
    long res = karmarkarKarp(&newSequence), res2;

    vector<int> partition2;
    vector<long> newSequence2 (n);

    for (int i = 0; i < max_iter; ++i) {
        // random sol
        partition2 = generatePrepartition(n);
        convertPrepartition(sequence, &partition2, &newSequence2);
        res2 = karmarkarKarp(&newSequence2);

        if (res > res2) {
            res = res2;
        }
    }
    return res;
}


// PHC
long prepartitionHillClimbing (vector<long> * sequence, int max_iter) {
    int n = sequence->size(); 

    vector<int> partition = generatePrepartition(n);
    vector<int> partition2 = partition;
    vector<long> newSequence (n), newSequence2 (n);
    convertPrepartition(sequence, &partition, &newSequence);
    long res = karmarkarKarp(&newSequence), res2;

    for (int i = 0; i < max_iter; ++i) {
        prepartitionRandomMove(&partition, &partition2);
        convertPrepartition(sequence, &partition2, &newSequence2);
        res2 = karmarkarKarp(&newSequence2);

        if (res > res2) {
            partition = partition2;
            res = res2;
        }
    }
    return res;
}

// PSA
long prepartitionSimulatedAnnealing (vector<long> * sequence, int max_iter) {
    int n = sequence->size();

    // initialize partitions for S, S', and S''
    vector<int> partition = generatePrepartition(n);
    vector<int> partition2 = partition;
    vector<int> partition3 = partition;

    // initialize S, S', and S''
    vector<long> newSequence (n), newSequence2 (n), newSequence3 (n);
    convertPrepartition(sequence, &partition, &newSequence);
    newSequence3 = newSequence;

    long res = karmarkarKarp(&newSequence), res2, res3;

    for (int i = 0; i < max_iter; ++i) {
        prepartitionRandomMove(&partition, &partition2);
        convertPrepartition(sequence, &partition2, &newSequence2);
        res2 = karmarkarKarp(&newSequence2);

        if (res > res2) {
            partition = partition2;
            res = res2;
            newSequence = newSequence2;
        }

        else {
            float prob = exp(-(res2-res)/cooling(i));
            if (realRand(0.0,1.0) <= prob) {
                partition = partition2;
                res = res2;
                newSequence = newSequence2;
            }
        }

        res3 = karmarkarKarp(&newSequence3);
        if (res3 > karmarkarKarp(&newSequence)) {
            partition3 = partition;
            res3 = res;
            newSequence3 = newSequence;
        }
    }

    return karmarkarKarp(&newSequence3);
}

// PART 3: EXPERIMENTATION

// Generate random sequence of 100 64-bit long longs
void generateRandomSequenceLONGLONG (vector<long long> * seq) {
    int n = seq->size();
    for (int i = 0; i < n; ++i) {
        (*seq)[i] = longlongRand(0, LLONG_MAX);
    }
    return;
}

// Generate random sequence of longs
void generateRandomSequence (vector<long> * seq) {
    int n = seq->size();
    for (int i = 0; i < n; ++i) {
        (*seq)[i] = longRand(0, LONG_MAX);
    }
    return;
}

// Main
// ./partition flag algorithm inputfile
int main (int argc, char * argv[]) {
    srand(time(NULL));
    int algorithm = strtol(argv[2], NULL, 10);

    vector<long> seq;
    int seq_len = 100;
    if (argc == 4) {
        string inputfile = argv[3];
        ifstream input(inputfile);
        string line;
        for (int i = 0; i < seq_len; ++i) {
            getline(input, line);
            seq.push_back(stol(line, NULL, 10));
        }
    } 
    else {
        seq.resize(seq_len);
        generateRandomSequence(&seq);
    }
    
    int max_iter = 12000;

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
    else if (algorithm == 13) {
        cout << prepartitionSimulatedAnnealing(&seq, max_iter);
    }
}

