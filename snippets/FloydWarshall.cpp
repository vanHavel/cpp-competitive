//
// Created by Lukas Huwald on 24.05.18.
//

#include "../library/Prelude.h"

int n;
// initialize to weights and 1B for non-edges
vvi adjMatrix;
// initialize parents[i][j] to i if edge is there, or -1 if no edge there
vvi parents;

int main() {
    REP(k, n) {
        REP(i, n) {
            REP(j, n) {
                if (adjMatrix[i][k] + adjMatrix[k][j] < adjMatrix[i][j]) {
                    adjMatrix[i][j] = adjMatrix[i][k] + adjMatrix[k][j];
                    parents[i][j] = parents[k][j];
                }
            }
        }
    }
}