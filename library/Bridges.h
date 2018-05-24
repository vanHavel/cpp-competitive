//
// Created by Lukas Huwald on 23.05.18.
//

#ifndef BRIDGES_H
#define BRIDGES_H

#include "Prelude.h"

class Bridges {
private:
    const int UNVISITED = -1;

    vi articulationVertex, visitCounter, lowestReachable, parents;
    vii bridges;
    vvi adjList;
    int dfsCounter, dfsRoot, rootChildren;

    void computeBridges(int v) {
        visitCounter[v] = lowestReachable[v] = dfsCounter++;
        for (int j = 0; j < (int) adjList[v].size(); ++j) {
            int u = adjList[v][j];
            if (visitCounter[u] == UNVISITED) {
                parents[u] = v;
                if (v == dfsRoot) { rootChildren++; }
                computeBridges(u);
                if (lowestReachable[u] >= visitCounter[v]) {
                    articulationVertex[v] = true;
                }
                if (lowestReachable[u] > visitCounter[v]) {
                    auto edge = std::make_pair(v, u);
                    bridges.push_back(edge);
                }
                lowestReachable[v] = std::min(lowestReachable[v], lowestReachable[u]);
            }
            else if (u != parents[v]) {
                lowestReachable[v] = std::min(lowestReachable[v], visitCounter[u]);
            }
        }
    }
public:
    Bridges(vvi& _adjList) {
        dfsCounter = 0;
        adjList = _adjList;
        int n = (int) adjList.size();
        visitCounter.assign(n, UNVISITED);
        lowestReachable.assign(n, 0);
        parents.assign(n, 0);
        articulationVertex.assign(n, 0);
        bridges = vii();
        REP(i, n) {
            if (visitCounter[i] == UNVISITED) {
                dfsRoot = i;
                rootChildren = 0;
                computeBridges(i);
                articulationVertex[i] = (rootChildren > 1);
            }
        }
    }

    vi getArticulationPoints() {
        return articulationVertex;
    }

    vii getBridges() {
        return bridges;
    }
};

#endif BRIDGES_H
