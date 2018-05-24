//
// Created by Lukas Huwald on 23.05.18.
//

#ifndef STRONGLYCONNECTEDCOMPONENTS_H
#define STRONGLYCONNECTEDCOMPONENTS_H

#include "Prelude.h"

class SCC {
private:
    const int UNVISITED = -1;

    vi visitCounter, lowestReachable, stack, visited;
    vvi adjList;
    int dfsCounter, numSCC;
    vvi scc;

    void tarjan(int v) {
        lowestReachable[v] = visitCounter[v] = dfsCounter++;
        stack.push_back(v);
        visited[v] = true;
        for (int j = 0; j < (int)adjList[v].size(); ++j) {
            int u = adjList[v][j];
            if (visitCounter[u] == UNVISITED) {
                tarjan(u);
            }
            if (visited[u]) {
                lowestReachable[v] = std::min(lowestReachable[v], lowestReachable[u]);
            }
        }

        if (lowestReachable[v] == visitCounter[v]) {
            ++numSCC;
            int u = -1;
            vi newSCC;
            while (u != v) {
                u = stack.back(); stack.pop_back(); visited[u] = false;
                newSCC.push_back(u);
            }
            scc.push_back(newSCC);
        }
    }
public:
    SCC(vvi _adjList) {
        adjList = _adjList;
        int n = (int) adjList.size();
        visitCounter.assign(n, UNVISITED);
        lowestReachable.assign(n, 0);
        visited.assign(n, false);
        dfsCounter = numSCC = 0;

        REP(i,n) {
            if (visitCounter[i] == UNVISITED) {
                tarjan(i);
            }
        }
    }

    vvi getSCCs() {
        return scc;
    }
};


#endif STRONGLYCONNECTEDCOMPONENTS_H
