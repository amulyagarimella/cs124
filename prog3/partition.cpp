#include <iostream> 
#include <algorithm> 
#include <vector>
#include <tuple>

using namespace std;
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
    karmarkarKarp(sequence);
}