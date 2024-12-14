#include "../../math/sieve.h"

main() {
    IO::initO();

    ri(n, q);
    Sieve sieve;
    sieve.calc(n + 1);
    println(size(sieve.primes));
    rep(q) {
        ri(x);
        println(sieve.is_prime[x]);
    }
}