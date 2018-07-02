//
// Created by Lukas Huwald on 02.07.18.
//

#ifndef MODLONG_H
#define MODLONG_H

#include "Prelude.h"
#include <limits>

class ModLong {
private:
    static ll mod = 1;
public:
    ll value;

    ModLong(ll l) {
        value = l % mod;
    }

    ModLong operator+(ModLong &rhs) {
        return ModLong(value + rhs.value);
    }
    ModLong operator*(ModLong &rhs) {
        return ModLong(value * rhs.value);
    }
    ModLong operator-(ModLong &rhs) {
        ll intermediate = (value - rhs.value) % mod;
        return ModLong(intermediate + mod);
    }
    ModLong& operator+=(ModLong &rhs) {
        value = (value + rhs.value) % mod;
        return *this;
    }
    ModLong& operator*=(ModLong &rhs) {
        value = (value * rhs.value) % mod;
        return *this;
    }
    ModLong& operator-=(ModLong &rhs) {
        value = (value - rhs.value) % mod;
        value = (value + mod) % mod;
        return *this;
    }

    static void setModulus(ll newMod) {
        ModLong::mod = newMod;
    }


};

#endif //MODLONG_H
