
#ifndef HUNGARIANMETHOD_H
#define HUNGARIANMETHOD_H

#include "Prelude.h"

class HungarianMethod {
private:
    vvll profits;
    vll rowPotentials, colPotentials;
    vi rowMatches, colMatches;
    vll colSlacks;
    vi colSlackPartners;
    int n;
    ll INF = 1000000000000000000ll;

    void computeInitialPotential() {
        REP(i, n) {
            REP(j, n) {
                rowPotentials[i] = std::max(rowPotentials[i], profits[i][j]);
            }
        }
    }

    void computeBestMatching() {
        computeInitialPotential();
        // augment n times
        REP(i, n) {
            // find unmatched node
            int root = 0;
            while (rowMatches[root] != -1) {
                root++;
            }
            bfs(root);
        }
    }

    void bfs(int root) {
        qi queue;
        vi rowGrandParents(n, -1);
        vi colsVisited(n, 0);
        vi rowsVisited(n, 0);
        initSlacks(root);
        queue.push(root);
        rowsVisited[root] = 1;
        int found = -1;
        int foundRow = -1;
        rowGrandParents[root] = -2;

        while (found == -1) {
            int row = queue.front();
            queue.pop();
            REP(col, n) {
                if (tight(row, col) && !colsVisited[col]) {
                    if (colMatches[col] == -1) {
                        // augmenting path found
                        found = col;
                        foundRow = row;
                        break;
                    } else {
                        // continue bfs
                        colsVisited[col] = 1;
                        int newRow = colMatches[col];
                        rowGrandParents[newRow] = row;
                        rowsVisited[newRow] = 1;
                        queue.push(newRow);
                        updateSlacks(newRow);
                    }
                }
            }
            while (found == -1 && queue.empty()) {
                // no augmenting path found, update potential
                updatePotential(rowsVisited, colsVisited);
                // check tree for new edges
                REP(col, n) {
                    if (!colsVisited[col] && colSlacks[col] == 0) {
                        if (colMatches[col] == -1) {
                            // unmatched col now reachable
                            found = col;
                            foundRow = colSlackPartners[col];
                            break;
                        } else {
                            // matched col reachable, add edges to tree
                            colsVisited[col] = 1;
                            int newRow = colMatches[col];
                            if (!rowsVisited[newRow]) {
                                rowGrandParents[newRow] = colSlackPartners[col];
                                rowsVisited[newRow] = 1;
                                queue.push(newRow);
                                updateSlacks(newRow);
                            }

                        }
                    }
                }
            }
        }
        // invert edges along augmenting path
        invertPath(found, foundRow, rowGrandParents);

    }

    void initSlacks(int root) {
        colSlackPartners = vi(n);
        colSlacks = vll(n);
        REP(col, n) {
            colSlacks[col] = rowPotentials[root] + colPotentials[col] - profits[root][col];
            colSlackPartners[col] = root;
        }
    }

    bool tight(int row, int col) {
        return rowPotentials[row] + colPotentials[col] == profits[row][col];
    }

    void updateSlacks(int row) {
        // update slacks after adding row to the tree
        REP(col, n) {
            ll tentativeSlack = rowPotentials[row] + colPotentials[col] - profits[row][col];
            if (tentativeSlack < colSlacks[col]) {
                colSlacks[col] = tentativeSlack;
                colSlackPartners[col] = row;
            }
        }
    }

    void updatePotential(vi const &rowsVisited, vi const &colsVisited) {
        ll delta = INF;
        REP(col, n) {
            if (!colsVisited[col]) {
                delta = std::min(delta, colSlacks[col]);
            }
        }
        REP(row, n) {
            if (rowsVisited[row]) {
                rowPotentials[row] -= delta;
            }
        }
        REP(col, n) {
            if (colsVisited[col]) {
                colPotentials[col] += delta;
            } else {
                colSlacks[col] -= delta;
            }
        }
    }

    void invertPath(int col, int row, vi const &rowGrandParents) {
        while (row != -2) {
            int temp = rowMatches[row];
            colMatches[col] = row;
            rowMatches[row] = col;
            row = rowGrandParents[row];
            col = temp;
        }
    }

public:
    // call with square matrix of nonnegative profits
    HungarianMethod(vvll _profits) {
        profits = _profits;
        n = profits.size();
        colPotentials = vll(n, 0);
        rowPotentials = vll(n, 0);
        rowMatches = vi(n, -1);
        colMatches = vi(n, -1);
        computeBestMatching();
    }

    ll getMatchingScore() {
        ll score = 0;
        REP(i, n) {
            score += profits[i][rowMatches[i]];
        }
        return score;
    }

    vi getMatching() {
        // matching[row] -> col
        vi matching(n);
        REP(row, n) {
            matching[row] = rowMatches[row];
        }
        return matching;
    }

    vll getRowPotentials() { return rowPotentials; }

    vll getColPotentials() { return colPotentials; }

};

#endif //HUNGARIANMETHOD_H

