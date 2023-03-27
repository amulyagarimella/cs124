#include <iostream>
#include <cmath>
#include <tgmath.h> 
#include <stdlib.h> 
#include <vector>

// TODO make changes to input format
using namespace std;

void printMatrix (vector<vector<float> > *M) {
    int n = M->size();
    cout << "[\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << (*M)[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "]\n\n";
}

void printDiagonals (vector<vector<float> > *M) {
    int n = M->size();
    for (int i = 0; i < n; ++i) {
        cout << (*M)[i][i] << "\n";
    }
    cout << "\n";
}

// TODO
void copyFromFile (vector<vector<float> > *A, string inputfile) {
    cout << "x";
}

vector<vector<float> > generateMatrix (int n) {
    vector<vector<float> > M; 
    M.resize(n);
    for (int i = 0; i < n; ++i) {
        M[i].resize(n);
        for (int j = 0; j < n; ++j) {
            M[i][j] = rand() % 3;
        }
    }
    return M;
}


// Standard matmul algorithm
/*
Input:
- pointers to n x n matrices A and B

Output: 
- product of A and B

Runtime: O(n^3)

Tests: runs, correct
*/
vector<vector<float> > standard (vector<vector<float> > *A, vector<vector<float> > *B) {
    int n = A->size();
    vector<vector<float> > C;
    C.resize(n);

    for (int i = 0; i < n; ++i) {
        C[i].resize(n);
        for (int j = 0; j < n; ++j) {
            // row i of A, col j of B
            for (int k = 0; k < n; ++k) {
                C[i][j] += (*A)[i][k] * (*B)[k][j];
            }
        }
    }
    /*printMatrix(A);
    printMatrix(B);
    printMatrix(&C);*/
    return C;
}

vector<vector<float> > fill_arr (vector<vector<float> > *M, int rstart, int cstart, int len) {
    vector<vector<float> > A;
    A.resize(len);
    //cout << len;
    for (int i = rstart; i < rstart + len; ++i) {
        //cout << i;
        A[i-rstart].resize(len);
        for (int j = cstart; j < cstart + len; ++j) {
            int entry = (*M)[i][j];
            A[i-rstart][j-cstart] = entry;
        }
    }
    return A;
}

vector<vector<float> > AplusB (vector<vector<float> > *A, vector<vector<float> > *B, bool subtract=false) {
    vector<vector<float> > C;
    int n = A->size();
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
    return C;
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

// Strassen algorithm
/*
Input:
- pointers to n x n matrices M1 and M2

Output: 
- product of M1 and M2
*/
vector<vector<float> > strassen (vector<vector<float> > *M1, vector<vector<float> > *M2) {
    int n = M1->size();
    // handle non powers of 2 by padding with 0s
    if (n != 1 && fmod(n,2) != 0 && fmod(sqrt(n),1) != 0) {
        cout << "not a power of 2, padding\n";
        int newn = ceil(log2(n));
        resizeMatrix(M1, newn);
        resizeMatrix(M2, newn);
        n = newn;
    }
    /*
    printMatrix(M1);
    printMatrix(M2);
    */

    // base case: n = 1
    if (n == 1 || n == 2) {
        return standard(M1, M2);
    }

    // if power of 2
    vector<vector<float> > A = fill_arr(M1, 0, 0, n/2);
    vector<vector<float> > B = fill_arr(M1, 0, n/2, n/2);
    vector<vector<float> > C = fill_arr(M1, n/2, 0, n/2);
    vector<vector<float> > D = fill_arr(M1, n/2, n/2, n/2);

    vector<vector<float> > E = fill_arr(M2, 0, 0, n/2);
    vector<vector<float> > F = fill_arr(M2, 0, n/2, n/2);
    vector<vector<float> > G = fill_arr(M2, n/2, 0, n/2);
    vector<vector<float> > H = fill_arr(M2, n/2, n/2, n/2);
    
    // products
    // vector<vector<float> > AB = ;
    vector<vector<float> > AD = AplusB(&A,&D);
    vector<vector<float> > CA = AplusB(&C,&A,true);
    vector<vector<float> > FH = AplusB(&F,&H,true);
    vector<vector<float> > CD = AplusB(&C,&D);
    vector<vector<float> > GE = AplusB(&G,&E,true);
    vector<vector<float> > EH = AplusB(&E,&H);
    vector<vector<float> > BD = AplusB(&B,&D,true);
    vector<vector<float> > GH = AplusB(&G,&H);
    vector<vector<float> > EF = AplusB(&E,&F);
    
    vector<vector<float> > p1 = strassen(&A, &FH);
    vector<vector<float> > p2 = strassen(&AplusB(&A,&B), &H);
    vector<vector<float> > p3 = strassen(&CD, &E);
    vector<vector<float> > p4 = strassen(&D, &GE);
    vector<vector<float> > p5 = strassen(&AD, &EH);
    vector<vector<float> > p6 = strassen(&BD, &GH);
    vector<vector<float> > p7 = strassen(&CA, &EF);

    // clear A ... H
    A.clear();
    B.clear();
    C.clear();
    D.clear();
    E.clear();
    F.clear();
    G.clear();
    H.clear();

    // parts
    // TODO modify AplusB to return something that can be used without saving
    vector<vector<float> > p4p2 = AplusB(&p4,&p2,true);
    vector<vector<float> > p4p2p5 = AplusB(&p4p2,&p5);
    vector<vector<float> > p1p3 = AplusB(&p1,&p3,true);
    vector<vector<float> > p1p3p5 = AplusB(&p1p3,&p5);

    vector<vector<float> > q1 = AplusB(&p4p2p5,&p6);
    vector<vector<float> > q2 = AplusB(&p1,&p2);
    vector<vector<float> > q3 = AplusB(&p3,&p4);
    vector<vector<float> > q4 = AplusB(&p1p3p5,&p7);

    // clear p1...p7
    p1.clear();
    p2.clear();
    p3.clear();
    p4.clear();
    p5.clear();
    p6.clear();
    p7.clear();
    p4p2.clear();
    p4p2p5.clear();
    p1p3.clear();
    p1p3p5.clear();
    // product
    // put final parts together
    /*printMatrix(&q1);
    printMatrix(&q2);
    printMatrix(&q3);
    printMatrix(&q4);*/
    for (int i = 0; i < n/2; ++i) {
        //q1[i].resize(n);
        q1[i].insert(q1[i].end(), q2[i].begin(), q2[i].end());
        //q3[i].resize(n);
        q3[i].insert(q3[i].end(), q4[i].begin(), q4[i].end());
    }
    //q1.resize(n);
    q1.insert(q1.end(), q3.begin(), q3.end());
    q2.clear();
    q3.clear();
    q4.clear();
    // TODO unpad if needed
    // printMatrix(&q1);
    return q1;
}

int main(int argc, char * argv[]) {
    int n = strtol(argv[1], NULL, 10);
    srand (time(NULL));
    // TODO read in A and B
    vector<vector<float> > A = generateMatrix(n);
    //printMatrix(&A);
    vector<vector<float> > B = generateMatrix(n);
    //printMatrix(&B);
    //vector<vector<float> > C1 = standard(&A,&B);
    vector<vector<float> > C2 = strassen(&A,&B);
    //printMatrix(&C1);
    printDiagonals(&C2);
}