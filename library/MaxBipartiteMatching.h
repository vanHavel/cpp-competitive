//
// Created by Lukas Huwald on 24.05.18.
//

#ifndef MAXBIPARTITEMATCHING_H
#define MAXBIPARTITEMATCHING_H

#include "Prelude.h"
#include "Random.h"

// naive O(VE) algorithm with greedy preprocessing
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
        auto rng = getMt();
        si free;
        REP(l, n) { free.insert(l); }
        match.assign(n+m, -1);
        REP(l, n) {
            vi candidates;
            for (int r : adjList[l]) {
                if (match[r] == -1) { candidates.push_back(r); }
            }
            if (candidates.size() > 0) {
                maxMatching++;
                free.erase(l);
                auto a = rng() % candidates.size();
                match[candidates[a]] = l;
            }
        }
        FOREACH(it, free) {
            visited.assign(n, 0);
            maxMatching += augment(*it);
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

    int getMatchingSize() {
        return maxMatching;
    }

    vii getMatching() {
        vii matching;
        for (int i = n; i < n + m; ++i) {
            if (match[i] != -1) {
                matching.push_back(ii(match[i], i));
            }
        }
        return matching;
    }
};

#endif //MAXBIPARTITEMATCHING_H
