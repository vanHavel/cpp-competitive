//
// Created by Lukas Huwald on 24.05.18.
//

#ifndef MAXBIPARTITEMATCHING_H
#define MAXBIPARTITEMATCHING_H

#include "Prelude.h"

// naive O(n^3) algorithm
class BipartiteMatching {
private:
    vi match, visited;
    vvi adjList;
    int maxMatching;
    // partition sizes
    int n,m;

    int augment(int l) {
        if (visited[l]) { return 0; }
        visited[l] = 1;
        for (int j = 0; j < (int) adjList[l].size(); ++j) {
            int r = adjList[l][j];
            if (match[r] == -1 || augment(match[r])) {
                match[r] = l;
                return 1;
            }
        }
        return 0;
    }

    void computeMaxMatching() {
        maxMatching = 0;
        match.assign(n+m, -1);
        REP(l, n) {
            visited.assign(n, 0);
            maxMatching += augment(l);
        }
    }
public:
    // initialize with size of left partition
    // adj list has first n entries for left partition
    BipartiteMatching(vvi &_adjList, int _n) {
        adjList = _adjList;
        n = _n;
        int v = adjList.size();
        m = v - n;

        computeMaxMatching();
    }

    int getMaxMatchingSize() {
        return maxMatching;
    }
};

#endif MAXBIPARTITEMATCHING_H
