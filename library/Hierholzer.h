//
// Created by Lukas Huwald on 21.09.20.
//

#ifndef HIERHOLZER_H
#define HIERHOLZER_H

#include "Prelude.h"

class Hierholzer {
private:
    vvi g;
public:
    Hierholzer(vvi const& graph) {
        g = graph;
    }
    vi computeEulerPath(int s) {
        int n = g.size();
        vi res, idx(n, 0), stack;
        stack.push_back(s);
        while (!stack.empty()) {
            int u = stack.back();
            if (idx[u] < g[u].size()) {
                stack.push_back(g[u][idx[u]]);
                ++idx[u];
            }
            else {
                res.push_back(u);
                stack.pop_back();
            }
        }
        std::reverse(res.begin(), res.end());
        return res;
    }

};

#endif //HIERHOLZER_H
