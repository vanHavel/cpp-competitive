#include "Prelude.h"
#include <random>
#include <chrono>

#ifndef RANDOM_H
#define RANDOM_H



std::mt19937 getMt() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return rng;
}

auto rangeMt(int min, int max) {
    auto rng = std::bind(
            std::uniform_int_distribution<int>(min, max),
            std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count())
        );
    return rng;
}

void seedRand() {
    std::srand(std::time(nullptr))
}
int genRand() {
    return std::rand() * 32768 + std::rand();
}

#endif
