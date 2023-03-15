#include <iostream>
#include <cmath>
#include <stdlib.h> 
#include <vector>


using namespace std;

// Standard matmul algorithm
/*
Input:
- pointers to n x n matrices A and B

Output: 
- product of A and B

Runtime: O(n^3)
*/
vector<vector<float> > standard (vector<vector<float> > *A, vector<vector<float> > *B) {
    int n = A->size();
    vector<vector<float> > C;
    C.resize(n);

    for (int i = 0; i < n; ++i) {
        C[i].resize(n);
        for (int j = 0; j < n; ++j) {
            // row i of A, col j of B
            for (int k = 0; k < n; k++) {
                C[i][j] += (*A)[i][k] * (*B)[k][j];
            }
        }
    }

    return C;
}

// Strassen algorithm
/*
Input:
- pointers to n x n matrices M1 and M2

Output: 
- product of M1 and M2
*/
vector<vector<float> > * fill_arr (vector<vector<float> > *M, int rstart, int cstart, int len) {
    vector<vector<float> > A;
    A.resize(len);
    for (int i = rstart; i < rstart + len; ++i) {
        for (int j = cstart; j < cstart + len; ++j) {
            A[i].push_back((*M)[i][j]);
        }
    }
    return (&A);
}

vector<vector<float> > strassen (vector<vector<float> > *M1, vector<vector<float> > *M2, int start, int end) {
    int n = M1->size();
    // if not power of 2
    vector<vector<float> > * A = fill_arr(M1, 0, 0, n/2);
    vector<vector<float> > * B = fill_arr(M1, 0, n/2, n/2);
    vector<vector<float> > * C = fill_arr(M1, n/2, 0, n/2);
    vector<vector<float> > * D = fill_arr(M1, n/2, n/2, n/2);

    vector<vector<float> > * E = fill_arr(M2, 0, 0, n/2);
    vector<vector<float> > * F = fill_arr(M2, 0, n/2, n/2);
    vector<vector<float> > * G = fill_arr(M2, n/2, 0, n/2);
    vector<vector<float> > * H = fill_arr(M2, n/2, n/2, n/2);
    


    vector<vector<float> > C;
    C.resize(n);
    for (int i = 0; i < n; ++i) {
        C[i].resize(n);
    }
    
    int subsize = n/4;




    return C;
}