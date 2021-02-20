//
// Created by Lukas Huwald on 24.05.18.
//

#ifndef MAXBIPARTITEMATCHING_H
#define MAXBIPARTITEMATCHING_H

#include "Prelude.h"
#include "Random.h"
#include "HungarianMethod.h"

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

// O(V^3) by reduction to Hungarian method
class WeightedBipartiteMatching {
private:
    vii mwbm;
    ll maxWeight = 0;
public:
    // call with adjacency list (with positive weights) and size of first partition
    WeightedBipartiteMatching(vvill &adjList, int n) {
        int m = adjList.size() - n;
        int ma = std::max(n, m);
        // default weight is zero
        ll def = 0;
        vvll profits(ma, vll(ma, neg));
        REP(i, n) {
            FOREACH(it, adjList[i]) {
                int j = it->first - n;
                ll w = it->second;
                // first dimension of profit should be the larger partition
                if (n >= m) {
                    profits[i][j] = w;
                }
                else {
                    profits[j][i] = w;
                }
            }
        }
        HungarianMethod hm(profits);
        vi match = hm.getMatching();

        REP(i, ma) {
            int j = match[i];
            // do not take dummy edges
            if (profits[i][j] != def) {
                maxWeight += profits[i][j];
                if (n >= m) {
                    mwbm.push_back(ii(i, n + j));
                }
                else {
                    mwbm.push_back(ii(j, n+i));
                }
            }
        }
    }

    ll getMatchingWeight() {
        return maxWeight;
    }

    vii getMatching() {
        return mwbm;
    }
};

#endif //MAXBIPARTITEMATCHING_H
