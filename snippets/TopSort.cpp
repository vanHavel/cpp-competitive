//
// Created by Lukas Huwald on 23.05.18.
//

#include "../library/prelude.h"

#define VISITED 1
#define UNVISITED 0

// visited nodes
vi visited;
// adjacency list
vvi adjList;

// inverse top sort vector
vi topSort;

void topSortDfs(int v) {
    visited[v] = VISITED;
    for (int j = 0; j < (int) adjList[v].size(); ++j) {
        int u = adjList[v][j];
        if (visited[u] == UNVISITED) {
            topSortDfs(u);
        }
    }
    topSort.push_back(v);
}

int main() {
    int n = (int) adjList.size();
    visited.assign(n, 0);
    REP(i,n) {
        if (visited[i] == UNVISITED) {
            topSortDfs(i);
        }
    }
}