#include <iostream>
#include <cmath>
#include <tgmath.h> 
#include <stdlib.h> 
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// TASK 3: Triangles

void printMatrix (vector<vector<int> > *M) {
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

void printDiagonals (vector<vector<int> > *M) {
    int n = M->size();
    for (int i = 0; i < n; ++i) {
        cout << (*M)[i][i] << "\n";
    }
    cout << "\n";
}

void copyFromFile (vector<vector<int> > *A, vector<vector<int> > *B, string inputfile, int n) {
    ifstream input(inputfile);
    string line;
    for (int i = 0; i < n; ++i) {
        vector<int> v;
        for (int j = 0; j < n; ++j) { 
            getline(input, line);
            v.push_back(stol(line, NULL, 10));
        }
        (*A).push_back(v);
    }
    for (int i = 0; i < n; ++i) {
        vector<int> v;
        for (int j = 0; j < n; ++j) { 
            getline(input, line);
            v.push_back(stol(line, NULL, 10));
        }
        (*B).push_back(v);
    }
}

vector<vector<int> > generateMatrix (int n) {
    vector<vector<int> > M; 
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
vector<vector<int> > standard (vector<vector<int> > *A, vector<vector<int> > *B) {
    int n = A->size();
    vector<vector<int> > C;
    C.resize(n);

    for (int i = 0; i < n; ++i) {
        C[i].resize(n);
        for (int k = 0; k < n; ++k) {
            // row i of A, col j of B
            for (int j = 0; j < n; ++j) {
                C[i][j] += (*A)[i][k] * (*B)[k][j];
            }
        }
    }
    /*printMatrix(A);
    printMatrix(B);
    printMatrix(&C);*/
    return C;
}

vector<vector<int> > fill_arr (vector<vector<int> > *M, int rstart, int cstart, int len) {
    vector<vector<int> > A;
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

vector<vector<int> > AplusB (vector<vector<int> > *A, vector<vector<int> > *B, bool subtract=false) {
    vector<vector<int> > C;
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



void resizeMatrix (vector<vector<int> > *A, int newn) {
    int n = A->size();
    A->resize(newn);
    for (int i = 0; i < newn; ++i) {
        (*A)[i].resize(newn);
    }
    if (newn > n) {
        for (int i = n; i < newn; ++i) {
            for (int j = n; j < newn; ++j) {
            (*A)[i][j] = 0;
            }
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
vector<vector<int> > strassen (vector<vector<int> > *M1, vector<vector<int> > *M2) {
    int n = M1->size();
    int oldn = n;
    bool odd = fmod(n,2) != 0;
    /*printMatrix(M1);
    printMatrix(M2);*/
    // base case - analytical crossover pt
    int cutoff = 200;
    if (odd) {
        cutoff = 225;
    }
    
    if (n <= cutoff) {
        return standard(M1, M2);
    }

    if (odd) {
        n = n + 1;
        // cout << "not a power of 2, padding\n";
        resizeMatrix(M1, n);
        resizeMatrix(M2, n);
    }
    // if power of 2
    vector<vector<int> > A = fill_arr(M1, 0, 0, n/2);
    vector<vector<int> > B = fill_arr(M1, 0, n/2, n/2);
    vector<vector<int> > C = fill_arr(M1, n/2, 0, n/2);
    vector<vector<int> > D = fill_arr(M1, n/2, n/2, n/2);
    vector<vector<int> > E = fill_arr(M2, 0, 0, n/2);
    vector<vector<int> > F = fill_arr(M2, 0, n/2, n/2);
    vector<vector<int> > G = fill_arr(M2, n/2, 0, n/2);
    vector<vector<int> > H = fill_arr(M2, n/2, n/2, n/2);
    
    // products
    vector<vector<int> > AB = AplusB(&A,&B);
    vector<vector<int> > AD = AplusB(&A,&D);
    vector<vector<int> > CA = AplusB(&C,&A,true);
    vector<vector<int> > FH = AplusB(&F,&H,true);
    vector<vector<int> > CD = AplusB(&C,&D);
    vector<vector<int> > GE = AplusB(&G,&E,true);
    vector<vector<int> > EH = AplusB(&E,&H);
    vector<vector<int> > BD = AplusB(&B,&D,true);
    vector<vector<int> > GH = AplusB(&G,&H);
    vector<vector<int> > EF = AplusB(&E,&F);
    
    vector<vector<int> > p1 = strassen(&A, &FH);
    vector<vector<int> > p2 = strassen(&AB, &H);
    vector<vector<int> > p3 = strassen(&CD, &E);
    vector<vector<int> > p4 = strassen(&D, &GE);
    vector<vector<int> > p5 = strassen(&AD, &EH);
    vector<vector<int> > p6 = strassen(&BD, &GH);
    vector<vector<int> > p7 = strassen(&CA, &EF);

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
    vector<vector<int> > p4p2 = AplusB(&p4,&p2,true);
    vector<vector<int> > p4p2p5 = AplusB(&p4p2,&p5);
    vector<vector<int> > p1p3 = AplusB(&p1,&p3,true);
    vector<vector<int> > p1p3p5 = AplusB(&p1p3,&p5);

    vector<vector<int> > q1 = AplusB(&p4p2p5,&p6);
    vector<vector<int> > q2 = AplusB(&p1,&p2);
    vector<vector<int> > q3 = AplusB(&p3,&p4);
    vector<vector<int> > q4 = AplusB(&p1p3p5,&p7);

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
    for (int i = 0; i < n/2; ++i) {
        q1[i].insert(q1[i].end(), q2[i].begin(), q2[i].end());
        q3[i].insert(q3[i].end(), q4[i].begin(), q4[i].end());
    }
    q1.insert(q1.end(), q3.begin(), q3.end());
    q2.clear();
    q3.clear();
    q4.clear();

    // cout << "n = " << oldn << "\n" << flush;

    if (odd) {
        resizeMatrix(&q1,oldn);
    }
    return q1;
}

vector<vector<int> > generateTriangleMatrix (int p, int n) {
    vector<vector<int> > M; 
    M.resize(n);
    for (int i = 0; i < n; ++i) {
        M[i].resize(n);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int flip = (int)(100.0 * rand() / (RAND_MAX + 1.0)) + 1;
            if (flip <= p) {
                M[i][j] = 1;
                M[j][i] = 1;
            }
            else {
                M[i][j] = 0;
                M[j][i] = 0;
            }
        }
    }
    return M;
}

int findTriangles (vector<vector<int> > *A, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      sum = sum + (*A)[i][i];
    }
    return (int) sum / 6;
}

int main(int argc, char * argv[]) {
    // int n = strtol(argv[2], NULL, 10);
    int n = 512;
    srand(time(NULL));
    // string input = argv[3];
    vector<vector<int> > A = generateMatrix(n);
    vector<vector<int> > B = generateMatrix(n);
    vector<vector<int> > C;
    // copyFromFile(&A,&B,input,n);
    /*if (strtol(argv[1], NULL, 10) == 1) {
        C = standard(&A,&B);
    } else {
        C = strassen(&A,&B);
    }*/
    
    // printDiagonals(&C);

        // test for p = 0.01
    vector<vector<int> > trig = generateTriangleMatrix(50, n);
    vector<vector<int> > intermed = strassen(&trig, &trig);
    vector<vector<int> > threeA = strassen(&trig, &intermed);
    cout << findTriangles(&threeA, n);
}