#ifndef LICHAOTREE_H
#define LICHAOTREE_H

#include "Prelude.h"

// a segment tree of linear functions, that can be queried for the min value of all functions at an index
class LiChaoTree {

private:
    // a linear function m*x + b is represented as (m, b)
    vdd functions;
    vi ids;
    constexpr static const double INF = 1e20;
    //constexpr static const ll INF = 1000000000000000000;
    int n;

    static double apply(dd function, int x) {
        return function.first * x + function.second;
    }

    void addLine(dd newFunction, int id, int index, int left, int right) {
        int mid = (left + right) / 2;
        bool leftLowerNew = apply(newFunction, left) < apply(functions[index], left);
        bool midLowerNew = apply(newFunction, mid) < apply(functions[index], mid);
        if (midLowerNew) {
            auto tmpFunc = functions[index];
            int tmpId = ids[index];
            functions[index] = newFunction;
            ids[index] = id;
            newFunction = tmpFunc;
            id = tmpId;
        }
        if (right - left == 1) {
            return;
        } else if (leftLowerNew != midLowerNew) {
            addLine(newFunction, id, 2 * index, left, mid);
        } else {
            addLine(newFunction, id, 2 * index + 1, mid, right);
        }
    }

    std::pair<double, int> getMinimumAndId(int x, int index, int left, int right) {
        int mid = (left + right) / 2;
        if(right - left == 1) {
            return std::make_pair(apply(functions[index], x), ids[index]);
        } else if(x < mid) {
            auto here = apply(functions[index], x);
            auto rec = getMinimumAndId(x, 2 * index, left, mid);
            if (rec.first < here) {
                return rec;
            }
            else {
                return std::make_pair(here, ids[index]);
            }
        } else {
            auto here = apply(functions[index], x);
            auto rec = getMinimumAndId(x, 2 * index + 1, mid, right);
            if (rec.first < here) {
                return rec;
            }
            else {
                return std::make_pair(here, ids[index]);
            }
        }
    }

public:
    LiChaoTree(int _n) {
        n = _n;
        functions = vdd(4*n, dd(0, INF));
        ids = vi(4*n, -1);
    }

    void addLine(dd newFunction, int id) {
        addLine(newFunction, id, 1, 0, n);
    }

    double getMinimum(int x) {
        return getMinimumAndId(x, 1, 0, n).first;
    }

    int getId(int x) {
        return getMinimumAndId(x, 1, 0, n).second;
    }
};


#endif //LICHAOTREE_H
