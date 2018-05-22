//
// Created by Lukas Huwald on 22.05.18.
//

#include "../library/prelude.h"

#define VISITED 1
#define UNVISITED 0

// visited nodes
vi visited;

// adjacency list
vvi adjList;

// basic dfs and bfs
// add your flavour like parents, distances etc.

void dfs(int v) {
    visited[v] = VISITED;
    for (int j = 0; j < (int) adjList[v].size(); ++j) {
        int u = adjList[v][j];
        if (visited[u] == UNVISITED) {
            dfs(u);
        }
    }
}

void bfs(int v) {
    std::queue<int> q;
    q.push(v);
    visited[v] = VISITED;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int j = 0; j < (int) adjList[v].size(); ++j) {
            int u = adjList[v][j];
            if (visited[u] == UNVISITED) {
                visited[u] = VISITED;
                q.push(u);
            }
        }
    }
}