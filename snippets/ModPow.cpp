//
// Created by Lukas Huwald on 18.06.18.
//

ll fastModPow(ll base, ll exponent, ll modulus) {
    ll res = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            res = (res * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return res;
}

