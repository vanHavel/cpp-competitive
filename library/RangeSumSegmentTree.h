
#ifndef RANGESUMSEGMENTTREE_H
#define RANGESUMSEGMENTTREE_H

#include "prelude.h"

class RangeSumSegmentTree {
private:
    vi st, A, lazy;
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
            st[parent] = r1 + r2;
        }
    }

    int rsq(int parent, int leftBound, int rightBound, int i, int j) {
        lazyUpdate(parent, leftBound, rightBound);

        if (i > rightBound || j < leftBound) { return 0; }
        if (leftBound >= i && rightBound <= j) { return st[parent]; }

        int r1 = rsq(left(parent), leftBound, (leftBound + rightBound) / 2, i, j);
        int r2 = rsq(right(parent), (leftBound + rightBound) / 2 + 1, rightBound, i, j);
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

    void updateRange(int parent, int leftBound, int rightBound, int updateLeft, int updateRight, int diff) {
        lazyUpdate(parent, leftBound, rightBound);
        // stop recursing
        if (leftBound > rightBound || leftBound > updateRight || rightBound < updateLeft) {
            return;
        }
        // update in range
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
        }
    }

public:
    RangeSumSegmentTree(vi &_A) {
        A = _A;
        n = (int) A.size();
        st.assign(4*n, 0);
        lazy.assign(4*n, 0);
        build(1, 0, n-1);
    }

    int rangeSumQuery(int i, int j) {
        return rsq(1, 0, n-1, i, j);
    }

    void update(int i, int diff) {
        updateRange(1, 0, n-1, i, i, diff);
    }

    void updateRange(int i, int j, int diff) {
        updateRange(1, 0, n-1, i, j, diff);
    }

};

#endif