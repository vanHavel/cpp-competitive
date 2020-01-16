//
// Created by Lukas Huwald on 24.05.18.
//

#ifndef MAXFLOW_H
#define MAXFLOW_H

#include "Prelude.h"

class MaxFlow {
private:
    // adjacency matrix of residuals
    vvi residuals;
    vi parents;
    int n, maxFlow, augmentation, source, sink;
    const int BILLION = 1000000000;

    void computeMaxFlow() {
        maxFlow = 0;
        while (true) {
            augmentation = 0;
            vi distances(n, BILLION); distances[source] = 0;
            std::queue<int> q; q.push(source);
            parents.assign(n, -1);

            while (!q.empty()) {
                int v = q.front(); q.pop();
                if (v == sink) { break; }
                REP(u, n) {
                    if (residuals[v][u] > 0 && distances[u] == BILLION) {
                        distances[u] = distances[v] + 1;
                        q.push(u);
                        parents[u] = v;
                    }
                }
            }

            augment(sink, BILLION);
            if (augmentation == 0) { break; }
            maxFlow += augmentation;
        }
    }

    void augment(int v, int minEdge) {
        if (v == source) {
            augmentation = minEdge;
            return;
        }
        else if (parents[v] != -1) {
            augment(parents[v], std::min(minEdge, residuals[parents[v]][v]));
            residuals[parents[v]][v] -= augmentation;
            residuals[v][parents[v]] += augmentation;
        }
    }

public:
    MaxFlow(vvi &capacities, int _source, int _sink) {
        n = capacities.size();
        residuals = vvi(n);
        REP(i,n) {
            residuals[i] = vi(n);
            REP(j,n) {
                residuals[i][j] = capacities[i][j];
            }
        }
        source = _source;
        sink = _sink;
        computeMaxFlow();
    }

    int getMaxFlow() {
        return maxFlow;
    }
};
#endif //MAXFLOW_H