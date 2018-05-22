//
// Created by Lukas Huwald on 22.05.18.
//

#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

#include "prelude.h"

class MinSegmentTree {
private:
    vi st, A;
    int n;
    int left(int parent) { return parent << 1; }
    int right(int parent) { return (parent << 1) + 1; }

    void build(int parent, int leftBound, int rightBound) {
        if (leftBound == rightBound) {
            st[parent] = leftBound;
        }
        else {
            build(left(parent), leftBound, (leftBound + rightBound) / 2);
            build(right(parent), (leftBound + rightBound) / 2 + 1, rightBound);
            int r1 = st[left(parent)], r2 = st[right(parent)];
            st[parent] = (A[r1] <= A[r2]) ? r1 : r2;
        }
    }

    int rmq(int parent, int leftBound, int rightBound, int i, int j) {
        if (i > rightBound || j < leftBound) { return -1; }
        if (leftBound >= i && rightBound <= j) { return st[parent]; }

        int r1 = rmq(left(parent), leftBound, (leftBound + rightBound) / 2, i, j);
        int r2 = rmq(right(parent), (leftBound + rightBound) / 2 + 1, rightBound, i, j);

        if (r1 == -1) { return r2; }
        if (r2 == -1) { return r1; }
        return (A[r1] <= A[r2]) ? r1 : r2;
    }

    void update(int parent, int leftBound, int rightBound, int i) {
        if (leftBound == rightBound) { return; }
        int middle = (leftBound + rightBound) / 2;
        if (i <= middle) {
            update(left(parent), leftBound, middle, i);
        }
        else {
            update(right(parent), middle + 1, rightBound, i);
        }
        int r1 = st[left(parent)], r2 = st[right(parent)];
        st[parent] = (A[r1] <= A[r2]) ? r1 : r2;
    }

public:
    MinSegmentTree(vi &_A) {
        A = _A;
        n = (int) A.size();
        st.assign(4*n, 0);
        build(1, 0, n-1);
    }

    int rmq(int i, int j) {
        return rmq(1, 0, n-1, i, j);
    }

    void update(int i, int val) {
        A[i] = val;
        update(1, 0, n-1, i);
    }
};

#endif SEGMENTTREE_H