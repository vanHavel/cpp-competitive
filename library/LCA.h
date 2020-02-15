#ifndef LCA_H
#define LCA_H

#include "Prelude.h"

// LCA: precompute in n * log(n) time, query in log(n) time
class LCA {
private:
    vi heights;
    vvi parents; //parents[i][j] is the 2^jth ancestor of i
    int log;

    void dfs(int v, vvi const& edges, int parent = -1) {
        parents[v][0] = parent;
        if (parent != -1)
            heights[v] = heights[parent] + 1;
        for (int i = 1; i < log; i++)
            if (parents[v][i - 1] != -1)
                parents[v][i] = parents[parents[v][i - 1]][i - 1];
        for (int u : edges[v]) {
            if (parent != u) {
                dfs(u, edges, v);
            }
        }
    }

public:
    LCA(vvi const &edges, int root = 0) {
        int n = edges.size();
        log = 2;
        int c = 1;
        while (c < n) {
            c *= 2;
            log++;
        }
        parents = vvi(n, vi(log, -1));
        heights = vi(n, 0);
        dfs(root, edges);
    }

    int lca(int v, int u) const {
        // make sure v is the deeper node
        if(heights[v] < heights[u]) {
            int tmp = u;
            u = v;
            v = tmp;
        }
        // move from v up to height of u
        for (int i = log - 1; i >= 0; i --) {
            if (parents[v][i] != -1 && heights[parents[v][i]] >= heights[u]) {
                v = parents[v][i];
            }
        }
        if(v == u)
            return v;
        for (int i = log - 1; i >= 0; i --) {
            if (parents[v][i] != parents[u][i]) {
                v = parents[v][i], u = parents[u][i];
            }
        }
        return parents[v][0];
    }

    int height(int v) const {
        return heights[v];
    }

    int distance(int v, int u) const {
        return heights[u] + heights[v] - 2 * heights[lca(v, u)];
    }
};


#endif // LCA_H
