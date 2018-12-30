//
// Created by Lukas Huwald on 22.05.18.
//

#ifndef UNIONFIND_H
#define UNIONFIND_H

#include "Prelude.h"

class UnionFind {
private:
    vi parent, rank, sizes;
    int count;
public:
    UnionFind(int n) {
        rank.assign(n, 0);
        parent.assign(n, 0);
        sizes.assign(n, 1);
        count = n;
        REP(i, n) {
            parent[i] = i;
        }
    }

    int find(int i) {
        return (parent[i] == i ? i : parent[i] = find(parent[i]));
    }

    void unite(int i, int j) {
        int pi = find(i);
        int pj = find(j);
        if (pi != pj) {
            count--;
            if (rank[pi] > rank[pj]) {
                parent[pj] = pi;
                sizes[pi] = sizes[pj] + sizes[pi];
            }
            else {
                parent[pi] = pj;
                sizes[pj] = sizes[pi] + sizes[pj];
                if (rank[pi] == rank[pj]) {
                    rank[pj]++;
                }
            }
        }
    }

    int numberOfSets() {
        return count;
    }

    int sizeOfSet(int i) {
        return sizes[find(i)];
    }

};

#endif //UNIONFIND_H