//
// Created by Lukas Huwald on 27.05.18.
//

int f (int x) {
    return x;
}

// returns cycle start index and cycle length
ii findCycle(x0) {
    int tortoise = f(x0), hare = f(f(x0));
    while (tortoise != hare) {
        tortoise = f(tortoise);
        hare = f(f(hare));
    }
    int mu = 0;
    ‚hare = x0;
    while (tortoise != hare) {
        tortoise = f(tortoise);
        hare = f(hare);
        mu++;
    }
    int lambda = 1;
    hare = f(tortoise);
    while (tortoise != hare) {
        hare = f(hare);
        lambda++;
    }
    return ii(mu, lambda);
}