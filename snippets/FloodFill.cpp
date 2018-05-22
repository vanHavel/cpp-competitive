//
// Created by Lukas Huwald on 22.05.18.
//

#include "../library/prelude.h"

//  number of directions
const int dirs = 4;
// const int dirs = 8;

// direction array
int dh[4] = {1,0,-1,0};
int dv[4] = {0,1,0,-1};
// int dh[8] = {1,1,0,-1,-1,-1,0,1};
// int dv[8] = {0,1,1,1,0,-1,-1,-1};

// grid sizes
const int rows = 1000, cols = 1000;
char grid[rows][cols];

int floodfill(int r, int c, char searched, char transformed) {
    if (r < 0 || r >= rows || c < 0 || c >= cols) { return 0; }
    if (grid[r][c] != searched) { return 0; }
    int ans = 1;
    grid[r][c] = transformed;
    REP(i, dirs) {
        ans += floodfill(r + dh[i], c + dv[i], searched, transformed);
    }
    return ans;
}