//
// Created by Lukas Huwald on 04.09.24.
//

#ifndef LIS_H
#define LIS_H

#include "Prelude.h"

class LIS {
public:
    vi dp;
    vi prev;
    LIS(vll const &A) {
        int n = (int) A.size();
        // dp[i] = index of smallest element that ends an increasing subsequence of length i
        dp = vi();
        // prev[i] = index of element before A[i] in the longest increasing subsequence ending at A[i]
        prev = vi(n);
        REP(i, n) {
            // find first element in dp that references a value greater than A[i]
            int lo = 0;
            int hi = (int) dp.size();
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (A[dp[mid]] < A[i]) { lo = mid + 1; }
                else { hi = mid; }
            }
            if (lo > 0) { prev[i] = dp[lo - 1]; }
            else { prev[i] = -1; }
            if (lo == (int) dp.size()) { dp.push_back(i); }
            else { dp[lo] = i; }
        }
    }

    int len() {
        return (int) dp.size();
    }

    // return the indices of the longest increasing subsequence
    vll seq() {
        int n = (int) dp.size();
        vll res(n);
        int cur = dp[n-1];
        for (int i = n - 1; i >= 0; i--) {
            res[i] = cur;
            cur = prev[cur];
        }
        return res;
    }
};

#endif //LIS_H
