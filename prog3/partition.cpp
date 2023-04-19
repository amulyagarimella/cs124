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
#include <time.h>
#include <thread>

using namespace std;

// thread safe random
// static mt19937* generator = nullptr;
random_device rd;
mt19937_64 eng(rd());

int intRand(const int & min, const int & max) {
    uniform_int_distribution<int> distribution(min, max);
    return distribution(eng);
}

float realRand(const float & min, const float & max) {
    uniform_int_distribution<unsigned long long> distribution(min, max);
    return distribution(eng);
}

long long longlongRand (const long long & min, const long long & max) {
    uniform_int_distribution<unsigned long long> distribution(min, max);
    return distribution(eng);
}
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

int karmarkarKarp (vector<long long> * sequence) {
    priority_queue<long long> pq (sequence->begin(), sequence->end());
    /*int m = sequence->back();
    sequence->pop_back();
    int sm = sequence->back();
    sequence->pop_back();*/
    long long m, sm;
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
    fill(signs->begin(), signs->end(), 0);
    // srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        int val = intRand(0,1);
        if (val == 0) {
            val = -1;
        }
        (*signs)[i] = val;
    }
    return signs;
}

long long residue (vector<long long> * sequence, vector<int> * signs) {
    int n = sequence->size();
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res += (*sequence)[i] * (*signs)[i];
    }
    return abs(res);
}

long long repeatedRandom (vector<long long> * sequence, int max_iter) {
    int n = sequence->size();
    vector<int> signs (n);
    vector<int> signs2 (n);
    generateRandomSigns(&signs);
    long long res = residue(sequence, &signs);

    long long res2;
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

vector<int> randomMove (vector<int> * signs) {
    int n = signs->size();
    // srand(time(NULL));
    vector<int> signs2 = *signs;
    int i = 0, j=0;
    while (i == j) {
        i = intRand(0,n-1);
        j = intRand(0,n-1);
    }
    /*cout << i << "," << j << "\n";
    cout << (*signs2)[i] << "\n";
    cout << (*signs2)[i] << "\n";*/
    signs2[i] = -signs2[i];
    int coinflip = intRand(0,1);
    if (coinflip == 0) {
        signs2[j] = -signs2[j];
    }
    return signs2;
}

// should return vector<vector<vector<int> > > 

/*
void generateGraph (int n) {
    // TODO
    return;
}*/

// TODO better way to generate/change random

long long hillClimbing (vector<long long> *sequence, int max_iter) {
    int n = sequence->size();
    vector<int> signs (n);
    generateRandomSigns(&signs);
    /*for (int i = 0; i < n; ++i) {
        cout << signs[i] << ",";
    }
    cout << "\n";*/
    vector<int> signs2 (signs);
    long long res = residue(sequence, &signs), res2;
    // cout << res << "\n";
    for (int i = 0; i < max_iter; ++i) {
        signs2 = randomMove(&signs);
        /*for (int i = 0; i < n; ++i) {
            cout << signs2[i] << ",";
        }
        cout << "\n";*/

        res = residue(sequence, &signs);
        res2 = residue(sequence, &signs2);
        if (res > res2) {
            // cout << res << "," << res2 << "\n";
            res = res2;
            signs = signs2;
        }
    }
    return residue(sequence, &signs);
}

float cooling (int iter) {
    float pwr = iter/300;
    return pow(10,10)*pow(0.8,pwr);
}

// Simulated annealing: TODO
/*
TODO: test
Correctness: ?
*/
/*random_device rd;
mt19937 gen(time(NULL));*/
long long simulatedAnnealing (vector<long long> * sequence, int max_iter) {
    int n = sequence->size();
    vector<int> signs (n);
    generateRandomSigns(&signs);
    vector<int> signs2 (signs);
    vector<int> signs3 (signs);
    long long res = residue(sequence, &signs), res2 = 0, res3 = 0;
    for (int i = 0; i < max_iter; ++i) {
        signs2 = randomMove(&signs);
        res2 = residue(sequence, &signs2);
        if (res > res2) {
            res = res2;
            signs = signs2;
        }
        else {
            float prob = exp(-(res2-res)/cooling(i));
            // cout << prob << "\n";
            if (realRand(0.0,1.0) <= prob) {
                res = res2;
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
        P[i] = intRand(0,num_partitions-1);
    }
    return P;  
}

/*
Essentially A′ is derived by resetting ai to be the sum of all values j with pj = i,
*/
vector<long long> * convertPrepartition (vector<long long> * sequence, vector<int> * partition, vector<long long> * newSequence) {
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
long long prepartitionRepeatedRandom (vector<long long> * sequence, int max_iter) {
    int n = sequence->size();
    // srand(time(NULL));
    // cout << "size" << n << "\n";
    vector<int> partition = generatePrepartition(n);
    vector<long long> newSequence (n);
    convertPrepartition(sequence, &partition, &newSequence);
    
    int res = karmarkarKarp(&newSequence);
    vector<int> partition2;
    vector<long long> newSequence2 (n);
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
long long prepartitionHillClimbing (vector<long long> * sequence, int max_iter) {
    int n = sequence->size();
    // srand(time(NULL));
    // cout << "size" << n << "\n";
    // generate 
    vector<int> partition = generatePrepartition(n);
    vector<long long> newSequence (n);
    convertPrepartition(sequence, &partition, &newSequence);

    int res = karmarkarKarp(&newSequence);

    vector<int> partition2 = partition;
    vector<long long> newSequence2 (n);
    
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
            res = res2;
            newSequence = newSequence2;
        }
    }
    return karmarkarKarp(&newSequence);
}

// PSA TODO!!
/*
int prepartitionSimulatedAnnealing (vector<long long> * sequence, int max_iter) {
    int n = sequence->size();
    // srand(time(NULL));
    // cout << "size" << n << "\n";
    vector<int> partition = generatePrepartition(n);
    vector<long long> newSequence = convertPrepartition(sequence, &partition);
    int res = karmarkarKarp(&newSequence);
    vector<long long> newSequence2;
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

// Generate random sequence of 100 64-bit long longs
void generateRandomSequence (vector<long long> * seq) {
    int n = seq->size();
    for (int i = 0; i < n; ++i) {
        (*seq)[i] = longlongRand(0,pow(2,64)-1);
    }
    return;
}

// TODO!!!!!!! check srand use
// Main
// ./partition flag algorithm inputfile
int main (int argc, char * argv[]) {
    srand(time(NULL));
    int flag = strtol(argv[1], NULL, 10);
    int algorithm = strtol(argv[2], NULL, 10);

    vector<long long> seq;
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
    
    int max_iter = 2000;

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

