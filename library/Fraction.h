//
// Created by Lukas Huwald on 2019-05-19.
//

#ifndef FRACTION_H
#define FRACTION_H

#include "Prelude.h"

class Fraction {
public:
    ll nom, denom;
    friend bool operator< (const Fraction &lhs, const Fraction &rhs);
    friend bool operator> (const Fraction &lhs, const Fraction &rhs);
    friend bool operator<= (const Fraction &lhs, const Fraction &rhs);
    friend bool operator>= (const Fraction &lhs, const Fraction &rhs);
    friend bool operator== (const Fraction &lhs, const Fraction &rhs);
    friend bool operator!= (const Fraction &lhs, const Fraction &rhs);

    friend Fraction operator+ (const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator- (const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator* (const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator/ (const Fraction &lhs, const Fraction &rhs);

    Fraction(ll _nom, ll _denom) {
        nom = _nom;
        denom = _denom;
    }

    Fraction scaled(ll c) {
        return Fraction(c * nom, denom);
    }

    Fraction reduced() {
        ll div = gcd(nom, denom);
        return Fraction(nom / div, denom / div);
    }

    ll truncated() {
        return nom / denom;
    }

    Fraction roundedDown(ll targetDenom) {
        return Fraction(targetDenom * nom / denom, targetDenom);
    }

    Fraction& operator+=(Fraction &rhs) {
        nom = nom * rhs.denom + denom * rhs.nom;
        denom *= rhs.denom;
        return *this;
    }

    Fraction& operator*=(Fraction &rhs) {
        nom *= rhs.nom;
        denom *= rhs.denom;
        return *this;
    }

    Fraction& operator-=(Fraction &rhs) {
        nom = nom * rhs.denom - denom * rhs.nom;
        denom *= rhs.denom;
        return *this;
    }

    Fraction& operator/=(Fraction &rhs) {
        nom *= rhs.denom;
        denom *= rhs.nom;
        return *this;
    }

    static ll gcd(ll a, ll b) {
        if (b == 0) { return a; }
        return gcd(b, a % b);
    }

};

bool operator<(const Fraction &lhs, const Fraction &rhs) {
    return lhs.nom * rhs.denom < lhs.denom * rhs.nom;
}
bool operator>(const Fraction &lhs, const Fraction &rhs) {
    return lhs.nom * rhs.denom > lhs.denom * rhs.nom;
}
bool operator<=(const Fraction &lhs, const Fraction &rhs) {
    return lhs.nom * rhs.denom <= lhs.denom * rhs.nom;
}
bool operator>=(const Fraction &lhs, const Fraction &rhs) {
    return lhs.nom * rhs.denom >= lhs.denom * rhs.nom;
}
bool operator==(const Fraction &lhs, const Fraction &rhs) {
    return lhs.nom * rhs.denom == lhs.denom * rhs.nom;
}
bool operator!=(const Fraction &lhs, const Fraction &rhs) {
    return lhs.nom * rhs.denom != lhs.denom * rhs.nom;
}

Fraction operator+(const Fraction &lhs, const Fraction &rhs) {
    return Fraction(lhs.nom * rhs.denom + lhs.denom * rhs.nom, lhs.denom * rhs.denom);
}
Fraction operator*(const Fraction &lhs, const Fraction &rhs) {
    return Fraction(lhs.nom * rhs.nom, lhs.denom * rhs.denom);
}
Fraction operator/(const Fraction &lhs, const Fraction &rhs) {
    return Fraction(lhs.nom * rhs.denom, lhs.denom * rhs.nom);
}
Fraction operator-(const Fraction &lhs, const Fraction &rhs) {
    return Fraction(lhs.nom * rhs.denom - lhs.denom * rhs.nom, lhs.denom * rhs.denom);
}

#endif //FRACTION_H
