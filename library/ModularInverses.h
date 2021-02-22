//
// Created by Lukas Huwald on 27.05.18.
//

#ifndef MODINV_H
#define MODINV_H

// returns d, x, y
// a * x + b * y = d = gcd(a,b);
std::tuple<ll, ll, ll> extendedEuclid(ll a, ll b) {
    if (b == 0) {
        return {a, 1, 0};
    }
    auto [d, x, y] = extendedEuclid(b, a % b);
    ll x1 = y;
    ll y1 = x - (a / b) * y;
    return {d, x1, y1};
}

ll modularInverse(ll a, ll n) {
    auto [d, x, y] = extendedEuclid(a, n);
    return (x + n) % n;
}

ll gcd(ll a, ll b) {
    if (b == 0) { return a; }
    return gcd(b, a % b);
}

// find x with x % m1 = a1, x % m2 = a2. m1 and m2 must be coprime
// if m1*m2 > 10^9: risk of integer overflow
ll crt(ll m1, ll a1, ll m2, ll a2) {
    auto [d, x, y] = extendedEuclid(m1, m2);
    ll m = m1 * m2;
    ll part1 = (a1 * m2) % m;
    part1 = (part1 * y) % m;
    part1 = (part1 + m) % m;
    ll part2 = (a2 * m1) % m;
    part2 = (part2 * x) % m;
    part2 = (part2 + m) % m;
    ll res = (part1 + part2) % m;
    return res;
}

// attempt crt on x % a_i = m_i with moduli not coprime. Returns -1 on no solution
// if lcm(m1, m2) > 10^9: risk of integer overflow
ll generalCrt(ll m1, ll a1, ll m2, ll a2) {
    auto [d, x, y] = extendedEuclid(m1, m2);
    if ((a1 % d) != (a2 % d)) {
        return -1;
    }
    ll m = m1 * m2 / d;
    ll part1 = (a1 * m2 / d) % m;
    part1 = (part1 * y) % m;
    part1 = (part1 + m) % m;
    ll part2 = (a2 * m1 / d) % m;
    part2 = (part2 * x) % m;
    part2 = (part2 + m) % m;
    ll res = (part1 + part2) % m;
    return res;
}

#endif // MODINV_H