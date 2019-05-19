//
// Created by Lukas Huwald on 2019-05-19.
//

#ifndef FRACTION_H
#define FRACTION_H

#include "Prelude.h"

class Fraction {
public:
    ll nom, denom;

    Fraction(ll _nom, ll _denom) {
        assert(denom != 0);
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

    Fraction operator+(Fraction &rhs) {
        return Fraction(nom * rhs.denom + denom * rhs.nom, denom * rhs.denom);
    }

    Fraction operator*(Fraction &rhs) {
        return Fraction(nom * rhs.nom, denom * rhs.denom);
    }

    Fraction operator-(Fraction &rhs) {
        return Fraction(nom * rhs.denom - denom * rhs.nom, denom * rhs.denom);
    }

    Fraction operator+=(Fraction &rhs) {
        nom = nom * rhs.denom + denom * rhs.nom;
        denom *= rhs.denom;
        return *this;
    }

    Fraction operator*=(Fraction &rhs) {
        nom *= rhs.nom;
        denom *= rhs.denom;
        return *this;
    }

    Fraction operator-=(Fraction &rhs) {
        nom = nom * rhs.denom - denom * rhs.nom;
        denom *= rhs.denom;
        return *this;
    }

    bool operator==(Fraction &rhs) {
        return nom * rhs.denom == denom * rhs.nom;
    }

    bool operator!=(Fraction &rhs) {
        return *this != rhs;
    }

    bool operator<(Fraction &rhs) {
        return nom * rhs.denom < denom * rhs.nom;
    }

    bool operator>(Fraction &rhs) {
        return rhs < *this;
    }

    bool operator<=(Fraction &rhs) {
        return *this < rhs || *this == rhs;
    }

    bool operator>=(Fraction &rhs) {
        return rhs <= *this;
    }

    static ll gcd(ll a, ll b) {
        if (b == 0) { return a; }
        return gcd(b, a % b);
    }

};

#endif //FRACTION_H
