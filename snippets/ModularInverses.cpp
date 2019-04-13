//
// Created by Lukas Huwald on 27.05.18.
//

// a * x + b * y = d = gcd(a,b);
ll x, y, d;

void extendedEuclid(ll a, ll b) {
    if (b == 0) {
        x = 1;
        y = 0;
        d = a;
        return;
    }
    extendedEuclid(b, a % b);
    ll x1 = y;
    ll y1 = x - (a / b) * y;
    x = x1;
    y = y1;
}

ll modularInverse(ll a, ll n) {
    extendedEuclid(a, n);
    return (x + n) % n;
}

ll gcd(ll a, ll b) {
    if (b == 0) { return a; }
    return gcd(b, a % b);
}

ll crt(ll m1, ll a1, ll m2, ll a2) {
    extendedEuclid(m1, m2);
    ll m = m1 * m2;
    ll part1 = (a1 * m2) % m;
    part1 = (part1 * y) % m;
    ll part2 = (a2 * m1) % m;
    part2 = (part2 * x) % m;
    ll res = (part1 + part2) % m;
    res = (res + m) % m;
    return res;
}