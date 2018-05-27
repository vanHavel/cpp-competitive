//
// Created by Lukas Huwald on 27.05.18.
//

#ifndef PRIMESIEVE_H
#define PRIMESIEVE_H

#include "Prelude.h"
#include <bitset>

class PrimeSieve {
private:
    ll sieveSize;
    static const int maxSieveSize = 20000000;
    std::bitset<maxSieveSize> prime;
    vi primes;

    void sieve() {
        prime.set();
        prime[0] = prime[1] = false;
        for (ll i = 2; i <= sieveSize; ++i) {
            if (prime[i]) {
                for (ll j = i*i; j <= sieveSize; j += i) {
                    prime[j] = 0;
                }
                primes.push_back((int) i);
            }
        }
    }

public:
    // this works on the stack for upper bounds up to 10^7, otherwise we need heap allocation
    PrimeSieve(ll upperBound) {
        if (upperBound > maxSieveSize) {
            abort();
        }
        primes = vi();
        sieveSize = upperBound + 1;
        sieve();
    }

    vi getPrimes() {
        return primes;
    }

    // n can be up to p^2 where p is the largest prime sieved
    bool isPrime(ll n) {
        if (n <= sieveSize) {
            return prime[n];
        }
        for (int i = 0; i < (int) primes.size(); ++i) {
            if (n % primes[i] == 0) { return false; }
        }
        return true;
    }
};

#endif //PRIMESIEVE_H
