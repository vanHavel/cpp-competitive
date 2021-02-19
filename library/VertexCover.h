//
// Created by Lukas Huwald on 18.02.21.
//

#ifndef VERTEXCOVER_H
#define VERTEXCOVER_H

#include "MaxBipartiteMatching.h"
#include "MaxFlow.h"

class BipartiteVertexCover {
private:
    vi mvc, mis;
public:
    // initialize with edges and size of first partition
    BipartiteVertexCover(vvi adjList, int n) {
        BipartiteMatching mm(adjList, n);
        int m = adjList.size() - n;
        vii matching = mm.getMatching();
        vi match(adjList.size(), -1);
        vi z(adjList.size(), 0);
        FOREACH(it, matching) {
            match[it->first] = it->second;
            match[it->second] = it->first;
        }
        // get vertex cover from König's theorem
        std::queue<int> q;
        vi visited(n+m, 0);
        REP(i, n) {
            if (match[i] == -1) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            z[u] = 1;
            visited[u] = 1;
            FOREACH(it, adjList[u]) {
                int v = *it;
                if (visited[v] == 0 && (v >= n && match[u] != v) || (v < n && match[u] == v)) {
                    q.push(v);
                }
            }
        }
        mvc = vi();
        mis = vi();
        REP(i, n) {
            if (z[i] == 0) {
                mvc.push_back(i);
            }
            else {
                mis.push_back(i);
            }
        }
        REP(i, m) {
            if (z[n+i] == 1) {
                mvc.push_back(n+i);
            }
            else {
                mis.push_back(n + i);
            }
        }
    }

    vi getMinVertexCover() {
        return mvc;
    }

    int getMinVertexCoverSize() {
        return mvc.size();
    }

    vi getMaxIndependentSet() {
        return mis;
    }

    int getMaxIndependentSetSize() {
        return mis.size();
    }
};

class BipartiteWeightedVertexCover {
private:
    vi mvc, mis;
    ll mvcw = 0, misw = 0;
    const static ll INF = 1e18;
public:
    BipartiteWeightedVertexCover(vvi adjList, int n, vll w) {
        int m = adjList.size() - n;
        MaxFlow mf(n+m+2);
        int s = n+m, t = n+m+1;
        REP(i, n+m) {
            if (i < n) {
                mf.add_edge(s, i, w[i]);
            }
            else {
                mf.add_edge(i, t, w[i]);
            }
        }
        REP(i, n) {
            FOREACH(it, adjList[i]) {
                int j = *it;
                mf.add_edge(i, j, INF);
            }
        }
        vi comps = mf.getComponentVector(s, t);
        // Königs theorem to get vertex cover: left vertices in T component and right vertices in S component
        REP(i, n) {
            if (comps[i]) {
                mvc.push_back(i);
            }
            else {
                mis.push_back(i);
            }
        }
        REP(i, m) {
            if (!comps[n+i]) {
                mvc.push_back(n+i);
            }
            else {
                mis.push_back(n+i);
            }
        }
        FOREACH(it, mvc) {
            mvcw += w[*it];
        }
        FOREACH(it, mis) {
            misw += w[*it];
        }
    }
    vi getMinVertexCover() {
        return mvc;
    }
    ll getMinVertexCoverWeight() {
        return mvcw;
    }
    vi getMaxIndependentSet() {
        return mis;
    }
    ll getMaxIndependentSetWeight() {
        return misw;
    }
};

#endif //VERTEXCOVER_H
