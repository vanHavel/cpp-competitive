#include "Prelude.h"
#include <random>
#include <chrono>

#ifndef RANDOM_H
#define RANDOM_H

// gets raw safe random generator
std::mt19937 getMt() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return rng;
}

// safely generates random ints in range [min, max]
auto rangeMt(int min, int max) {
    auto rng = std::bind(
            std::uniform_int_distribution<int>(min, max),
            std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count())
        );
    return rng;
}

// seed rand with time
void seedRand() {
    std::srand(std::time(nullptr));
}

// two invocations of rand for decent randomness. Only use as quick workaround.
int genRand() {
    return std::rand() * 32768 + std::rand();
}

#endif
