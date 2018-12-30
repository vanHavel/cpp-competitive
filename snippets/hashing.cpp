#include "prelude.h"

vll hash1;
vll powers1;
vll hash2;
vll powers2;

ll base1 = 97;
ll base2 = 89;
ll prime = 1000000007;

void prepareHashes() {
    int n;
    ss t;

    hash1 = vll(n);
    powers1 = vll(n);
    hash2 = vll(n);
    powers2 = vll(n);

    powers1[0] = 1;
    hash1[0] = t[0] - 'a' + 1;
    powers2[0] = 1;
    hash2[0] = t[0] - 'a' + 1;
    for (int i = 1; i < n; ++i) {
        powers1[i] = (base1 * powers1[i-1]) % prime;
        hash1[i] = (base1 * hash1[i-1] + t[i] - 'a' + 1) % prime;
        powers2[i] = (base2 * powers2[i-1]) % prime;
        hash2[i] = (base2 * hash2[i-1] + t[i] - 'a' + 1) % prime;
    }

}

llll getHash(int pos, int len) {
    if (pos == 0) {
        return llll(hash1[len-1], hash2[len-1]);
    }
    else {
        ll h1 = (hash1[pos + len - 1] - hash1[pos - 1] * powers1[len]) % prime;
        ll h2 = (hash2[pos + len - 1] - hash2[pos - 1] * powers2[len]) % prime;
        h1 = (h1 + prime) % prime;
        h2 = (h2 + prime) % prime;
        return llll(h1, h2);
    }
}