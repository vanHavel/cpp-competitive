//
// Created by Lukas Huwald on 18.02.21.
//

#ifndef VERTEXCOVER_H
#define VERTEXCOVER_H

#include "MaxBipartiteMatching.h"

class BipartiteVertexCover {
private:
    vi mvc;
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
        REP(i, n) {
            if (z[i] == 0) {
                mvc.push_back(i);
            }
        }
        REP(i, m) {
            if (z[n+i] == 1) {
                mvc.push_back(n+i);
            }
        }
    }

    vi getMinVertexCover() {
        return mvc;
    }

    int getMinVertexCoverSize() {
        return mvc.size();
    }
};

#endif //VERTEXCOVER_H
