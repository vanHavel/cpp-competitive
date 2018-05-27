//
// Created by Lukas Huwald on 27.05.18.
//

// a * x + b * y = d = gcd(a,b);
int x, y, d;

void extendedEuclid(int a, int b) {
    if (b == 0) {
        x = 1;
        y = 0;
        d = a;
        return;
    }
    extendedEuclid(b, a % b);
    int x1 = y;
    int y1 = x - (a / b) * y;
    x = x1;
    y = y1;
}

int modularInverse(int a, int n) {
    extendedEuclid(a, n);
    return x;
}