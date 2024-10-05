
#ifndef RANGESUMSEGMENTTREE_H
#define RANGESUMSEGMENTTREE_H

#include "prelude.h"

// A sum segment tree supporting lazy range updates
class RangeSumSegmentTree {
private:
    vll st, A, lazy;
    int n;
    int left(int parent) { return parent << 1; }
    int right(int parent) { return (parent << 1) + 1; }

    void build(int parent, int leftBound, int rightBound) {
        if (leftBound == rightBound) {
            st[parent] = A[leftBound];
        }
        else {
            int middle = (leftBound + rightBound) / 2;
            build(left(parent), leftBound, middle);
            build(right(parent), middle + 1, rightBound);
            st[parent] = st[left(parent)] + st[right(parent)];
        }
    }

    ll rsq(int parent, int leftBound, int rightBound, int i, int j) {
        lazyUpdate(parent, leftBound, rightBound);

        if (i > rightBound || j < leftBound || leftBound > rightBound) { return 0; }
        if (leftBound >= i && rightBound <= j) { return st[parent]; }

        int middle = (leftBound + rightBound) / 2;
        ll r1 = rsq(left(parent), leftBound, middle, i, j);
        ll r2 = rsq(right(parent), middle + 1, rightBound, i, j);
        return r1 + r2;
    }

    void lazyUpdate(int parent, int leftBound, int rightBound) {
        if (lazy[parent] != 0) {
            st[parent] += (rightBound - leftBound + 1) * lazy[parent];
            if (leftBound < rightBound) {
                lazy[left(parent)] += lazy[parent];
                lazy[right(parent)] += lazy[parent];
            }
            lazy[parent] = 0;
        }
    }

    void updateRange(int parent, int leftBound, int rightBound, int updateLeft, int updateRight, ll diff) {
        lazyUpdate(parent, leftBound, rightBound);
        // stop recursing
        if (leftBound > rightBound || leftBound > updateRight || rightBound < updateLeft) {
            return;
        }
        // range in update
        if (leftBound >= updateLeft && rightBound <= updateRight) {
            st[parent] += (rightBound - leftBound + 1) * diff;
            if (leftBound < rightBound) {
                lazy[left(parent)] += diff;
                lazy[right(parent)] += diff;
            }
        }
        // overlapping range
        else {
            int middle = (leftBound + rightBound) / 2;
            updateRange(left(parent), leftBound, middle, updateLeft, updateRight, diff);
            updateRange(right(parent), middle + 1, rightBound, updateLeft, updateRight, diff);
            st[parent] = st[left(parent)] + st[right(parent)];
        }
    }

public:
    RangeSumSegmentTree(vll const &_A) {
        A = _A;
        n = (int) A.size();
        st.assign(4*n, 0);
        lazy.assign(4*n, 0);
        build(1, 0, n-1);
    }

    ll rangeSumQuery(int i, int j) {
        return rsq(1, 0, n-1, i, j);
    }

    void update(int i, ll diff) {
        updateRange(1, 0, n-1, i, i, diff);
    }

    void updateRange(int i, int j, ll diff) {
        updateRange(1, 0, n-1, i, j, diff);
    }

    ll get(int i) {
        return rangeSumQuery(i, i);
    }

};

#endif