//
// Created by Lukas Huwald on 22.05.18.
//

#ifndef SUMFENWICKTREE_H
#define SUMFENWICKTREE_H

#include "prelude.h"

#define lsb(i) ((i)&(-(i)))

class FenwickTree {
private:
    vi ft;
public:
    FenwickTree(int n) {
        ft.assign(n+1, 0);
    }
    FenwickTree(vi &vec) {
        int n = vec.size();
        ft.assign(n+1, 0);
        REP(i,n) {
            adjust(i+1, vec[i]);
        }
    }

    int prefixSum(int i) {
        int sum = 0;
        while (i) {
            sum += ft[i];
            i-= lsb(i);
        }
        return sum;
    }

    int rangeSum(int i, int j) {
        return prefixSum(j) - (i == 1 ? 0 : prefixSum(i - 1));
    }

    void adjust(int i, int v) {
        while (i < (int) ft.size()) {
            ft[i] += v;
            i += lsb(i);
        }
    }
};

#endif SUMFENWICKTREE_H
