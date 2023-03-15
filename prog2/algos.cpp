#include <iostream>
#include <cmath>
#include <tgmath.h> 
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
    static vector<vector<float> > A;
    A.resize(len);
    for (int i = rstart; i < rstart + len; ++i) {
        A[i].resize(len);
        for (int j = cstart; j < cstart + len; ++j) {
            A[i][j] = (*M)[i][j];
        }
    }
    return (&A);
}

vector<vector<float> > * AplusB (vector<vector<float> > *A, vector<vector<float> > *B, bool subtract=false) {
    static vector<vector<float> > C;
    int n = (*A).size();
    C.resize(n);
    for (int i = 0; i < n; ++i) {
        C[i].resize(n);
        for (int j = 0; j < n; ++j) {
            if (subtract) {
                C[i][j] = (*A)[i][j] - (*B)[i][j];
            }
            else {
                C[i][j] = (*A)[i][j] + (*B)[i][j];
            }
        }
    }
    return (&C);
}

void resizeMatrix (vector<vector<float> > *A, int newn) {
    int n = A->size();
    for (int i = n-1; i < newn; ++i) {
        (*A)[i].resize(newn);
        for (int j = n-1; j < newn; ++j) {
            (*A)[i][j] = 0;
        }
    }
}

vector<vector<float> > * strassen (vector<vector<float> > *M1, vector<vector<float> > *M2) {
    int n = M1->size();
    // handle non powers of 2 by padding with 0s
    if (fmod(sqrt(n),1) != 0) {
        int newn = ceil(log2(n));
        resizeMatrix(M1, newn);
        resizeMatrix(M2, newn);
        n = newn;
    }

    // base case: n = 1
    vector<vector<float> > P;
    P.resize(n);
    if (n == 1) {
        P[0] = {(*M1)[0][0] * (*M2)[0][0]};
        return (&P);
    }

    // if power of 2
    vector<vector<float> > * A = fill_arr(M1, 0, 0, n/2);
    vector<vector<float> > * B = fill_arr(M1, 0, n/2, n/2);
    vector<vector<float> > * C = fill_arr(M1, n/2, 0, n/2);
    vector<vector<float> > * D = fill_arr(M1, n/2, n/2, n/2);

    vector<vector<float> > * E = fill_arr(M2, 0, 0, n/2);
    vector<vector<float> > * F = fill_arr(M2, 0, n/2, n/2);
    vector<vector<float> > * G = fill_arr(M2, n/2, 0, n/2);
    vector<vector<float> > * H = fill_arr(M2, n/2, n/2, n/2);
    
    // products
    vector<vector<float> > * p1 = strassen(A, AplusB(F,H,true));
    vector<vector<float> > * p2 = strassen(AplusB(A,B), H);
    vector<vector<float> > * p3 = strassen(AplusB(C,D), E);
    vector<vector<float> > * p4 = strassen(D, AplusB(G,E,true));
    vector<vector<float> > * p5 = strassen(AplusB(A,D), AplusB(E,H));
    vector<vector<float> > * p6 = strassen(AplusB(B,D,true), AplusB(G,H));
    vector<vector<float> > * p7 = strassen(AplusB(C,A,true), AplusB(E,F,true));

    // clear A ... H
    A->clear();
    B->clear();
    C->clear();
    D->clear();
    E->clear();
    F->clear();
    G->clear();
    H->clear();

    // parts
    vector<vector<float> > * q1 = AplusB(AplusB(AplusB(p4,p2,true),p5),p6);
    vector<vector<float> > * q2 = AplusB(p1,p2);
    vector<vector<float> > * q3 = AplusB(p3,p4);
    vector<vector<float> > * q4 = AplusB(AplusB(AplusB(p1,p3,true),p5),p7);

    // clear p1...p7
    p1->clear();
    p2->clear();
    p3->clear();
    p4->clear();
    p5->clear();
    p6->clear();
    p7->clear();

    // product
    // put final parts together
    q1->resize(n);
    for (int i = 0; i < n; ++i) {
        (*q1)[i].resize(n);
        (*q1)[i].insert((*q1)[i].end(), (*q2)[i].begin(), (*q2)[i].end());
        (*q3)[i].resize(n);
        (*q3)[i].insert((*q3)[i].end(), (*q4)[i].begin(), (*q4)[i].end());
    }
    (*q1).insert((*q1).end(), (*q3).begin(), (*q3).end());

    q2->clear();
    q3->clear();
    q4->clear();
    // TODO unpad if needed
    return q1;
}