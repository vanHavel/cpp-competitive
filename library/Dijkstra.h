//
// Created by Lukas Huwald on 24.05.18.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Prelude.h"

typedef std::pair<ll, int> lli;

class Dijkstra {
private:
    vll distances;
    vi parents;
    // ill: destination and weight
    vvill adjList;
    const ll DIJK_INF = 1'000'000'000'000'000'000;
public:
    Dijkstra(vvill &_adjList) {
        adjList = _adjList;
    }
    void computeShortestPaths(int s) {
        int n = adjList.size();
        distances.assign(n, DIJK_INF); distances[s] = 0;
        parents.assign(n, -1); parents[s] = s;
        // ii: cost and destination
        std::priority_queue<lli, std::vector<lli>, std::greater<lli>> pq;
        pq.push(std::make_pair(0, s));

        while (!pq.empty()) {
            auto front = pq.top(); pq.pop();
            auto d = front.first;
            auto v = front.second;
            if (d > distances[v]) { continue; }
            for (int j = 0; j < (int) adjList[v].size(); ++j) {
                ii u = adjList[v][j];
                if (distances[v] + u.second < distances[u.first]) {
                    distances[u.first] = distances[v] + u.second;
                    parents[u.first] = v;
                    pq.push(std::make_pair(distances[u.first], u.first));
                }
            }
        }
    }
    vll getDistances() {
        return distances;
    }
    vi getParents() {
        return parents;
    }
};

#endif //DIJKSTRA_H
