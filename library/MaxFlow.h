//
// Created by Lukas Huwald on 24.05.18.
//

#ifndef MAXFLOW_H
#define MAXFLOW_H

#include "Prelude.h"

// target, capacity and flow
typedef std::tuple<int, ll, ll> edge;

// O(V^2E) Dinic algorithm
class MaxFlow {
private:
    int n;
    const static ll INF = 1e18;
    std::vector<edge> edgeList;
    // maps node index to list of edge indices in edgeList
    vvi adjacencyList;
    vi dist;
    // last used neighbor ids in DFS of level graph
    vi last;
    // previous node and used edge index for BFS
    vii p;

    bool BFS(int s, int t) {
        dist.assign(n, -1);
        dist[s] = 0;
        std::queue<int> q({s});
        p.assign(n, {-1, -1});
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) { break; }
            for (auto idx: adjacencyList[u]) {
                auto [v, cap, flow] = edgeList[idx];
                if (cap - flow > 0 && dist[v] == -1) {
                    dist[v] = dist[u]+1;
                    q.push(v);
                    p[v] = {u, idx};
                }
            }
        }
        // return false when sink no longer reachable
        return dist[t] != -1;
    }

    ll DFS(int u, int t, ll f = INF) {
        if (u == t || f == 0) { return f; }
        for (int i = last[u]; i < adjacencyList[u].size(); i++, last[u]++) {
            auto &[v, cap, flow] = edgeList[adjacencyList[u][i]];
            if (dist[v] != dist[u]+1) { continue; }
            if (ll pushed = DFS(v, t, std::min(f, cap-flow))) {
                flow += pushed;
                auto &rflow = std::get<2>(edgeList[adjacencyList[u][i]^1]);
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

public:
    MaxFlow(int nodes) {
        n = nodes;
        edgeList.clear();
        adjacencyList.assign(n, vi());
    }

    void add_edge(int u, int v, ll w, bool directed = true) {
        edgeList.emplace_back(v, w, 0);
        adjacencyList[u].push_back(edgeList.size()-1);
        edgeList.emplace_back(u, directed ? 0 : w, 0);
        adjacencyList[v].push_back(edgeList.size()-1);
    }

    ll compute(int s, int t) {
        ll mf = 0;
        while (BFS(s, t)) {
            last.assign(n, 0);
            while (ll f = DFS(s, t)) {
                mf += f;
            }
        }
        return mf;
    }
};
#endif //MAXFLOW_H