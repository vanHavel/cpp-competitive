//
// Created by Lukas Huwald on 17.06.18.
//

#ifndef FFT_H
#define FFT_H

#include <complex>
#include <valarray>
#include "Prelude.h"

typedef std::valarray<std::complex<ld>> vcom;

// perform fft in place
void fft(vcom &a) {
    int n = (int) a.size();
    for (int i = n / 2; i >= 1; i /= 2) {
        std::complex<ld> omega = 1.0L;
        std::complex<ld> omegaI = std::exp(std::complex<ld>(0.0, -M_PI / i));

        for (int j = 0; j < i; ++j) {
            for (int k = j; k < n; k += 2 * i) {
                int m = k + i;
                std::complex<ld> tmp = a[k] + a[m];
                a[m] = (a[k] - a[m]) * omega;
                a[k] = tmp;
            }
            omega *= omegaI;
        }
    }

    for (int i = 0, j = 0; i < (n - 1); ++i) {
        if (i < j) {
            std::complex<ld> tmp = a[j];
            a[j] = a[i];
            a[i] = tmp;
        }

        int k;
        for (k = n / 2; k <= j; k /= 2) {
            j = j - k;
        }

        j += k;
    }
}


// perform inverse fft in place
void ifft(vcom &a) {
    a = a.apply(std::conj);
    fft(a);
    a = a.apply(std::conj);
    a /= a.size();
}

// multiply polynomials using fft
vll multiplyPolynomials(vll p1, vll p2) {
    ll n = (ll) std::max(p1.size(), p2.size());
    ll power = 1;
    while (power < n) {
        power <<= 1;
    }
    power <<= 1;

    vcom ac(std::complex<ld>(0,0), (size_t) power);
    vcom bc(std::complex<ld>(0,0), (size_t) power);
    REP(i, n) {
        ac[i] = std::complex<ld>(i < p1.size() ? p1[i] : 0, 0);
        bc[i] = std::complex<ld>(i < p2.size() ? p2[i] : 0, 0);
    }

    fft(ac);
    fft(bc);
    vcom tc((size_t) power);

    REP(i, power) {
        tc[i] = ac[i] * bc[i];
    }

    ifft(tc);
    vll res((size_t) power);
    REP(i, power) {
        res[i] = std::llroundl(tc[i].real());
    }
    while (res.size() > 0 && res.back() == 0) {
        res.pop_back();
    }

    return res;
}

#endif //FFT_H
