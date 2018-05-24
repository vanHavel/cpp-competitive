//
// Created by Lukas Huwald on 24.05.18.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Prelude.h"

class Dijkstra {
private:
    vi distances, parents;
    // ii: destination and weight
    vvii adjList;
    const int BILLION = 1000000000;
public:
    Dijkstra(vvii &_adjList) {
        adjList = _adjList;
    }
    void computeShortestPaths(int s) {
        int n = adjList.size();
        distances.assign(n, BILLION); distances[s] = 0;
        parents.assign(n, -1); parents[s] = s;
        // ii: cost and destination
        std::priority_queue<ii, std::vector<ii>, std::greater<ii>> pq;
        pq.push(std::make_pair(0, s));

        while (!pq.empty()) {
            ii front = pq.top(); pq.pop();
            int d = front.first, v = front.second;
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
    vi getDistances() {
        return distances;
    }
    vi getParents() {
        return parents;
    }
};

#endif DIJKSTRA_H
