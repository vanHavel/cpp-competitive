//
// Created by Lukas Huwald on 24.05.18.
//


int main() {
    int n, s;
    const int BILLION = 1000000000;
    vi distances;
    distances.assign(n, BILLION);
    distances[s] = 0;
    vvii adjList;

    for (int i = 0; i < n-1; ++i) {
        bool update = false;
        for (int v = 0; v < n; ++v) {
            for (int j = 0; j < (int) adjList[v].size(); ++j) {
                ii u = adjList[v][j];
                if (distances[v] + u.second < distances[u.first]) {
                    distances[u.first] = distances[v] + u.second;
                    update = true;
                }
            }
        }
        if (!update) {
            break;
        }
    }

    bool negativeCycle = false;
    for (int v = 0; v < n; ++v) {
        for (int j = 0; j < (int) adjList[v].size(); ++j) {
            ii u = adjList[v][j];
            if (distances[v] + u.second < distances[u.first]) {
                negativeCycle = true;
            }
        }
    }

}

