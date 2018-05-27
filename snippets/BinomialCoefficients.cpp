//
// Created by Lukas Huwald on 27.05.18.
//

int main() {
    int n = 5;
    ll table[n+1][n+1];

    table[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        table[i][0] = 1;
        table[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            table[i][j] = table[i-1][j] + table[i-1][j-1];
        }
    }

}