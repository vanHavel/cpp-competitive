//
// Created by Lukas Huwald on 24.05.18.
//

#ifndef MINIMUMSPANNINGTREE_H
#define MINIMUMSPANNINGTREE_H

#include "Prelude.h"
#include "UnionFind.h"

// actually computes minimum spanning forest if grapgh is not connected
class MST {
private:
    EdgeList edgeList, mstEdges;
    int mstWeight, n;

    void computeMST() {
        int m = edgeList.size();
        UnionFind uf(n);

        REP(i, m) {
            auto front = edgeList[i];
            if (uf.find(front.second.first) != uf.find(front.second.second)) {
                mstWeight += front.first;
                uf.unite(front.second.first, front.second.second);
                mstEdges.push_back(front);
                if (uf.numberOfSets() == 1) { break; }
            }
        }
    }
public:
    MST(EdgeList _edgeList, int _n) {
        edgeList = _edgeList; n = _n;
        mstWeight = 0;
        std::sort(edgeList.begin(), edgeList.end());

        computeMST();
    }

    int getMSTWeight() {
        return mstWeight;
    }

    EdgeList getMSTEdges() {
        return mstEdges;
    }
};
#endif //MINIMUMSPANNINGTREE_H


