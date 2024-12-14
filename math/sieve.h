#include "../template.h"

struct Sieve {
    vb is_prime;
    vi primes;
    void calc(int n) {
        is_prime.rsz(n, 1);
        is_prime[0] = is_prime[1] = 0;
        for (int i = 4; i < n; i += 2) is_prime[i] = 0;
        for (int i = 3; i * i < n; i += 2) {
            if (is_prime[i]) {
                for (int j = i * i; j < n; j += i * 2) is_prime[j] = 0;
            }
        }
        FOR (i, n) if (is_prime[i]) primes.pb(i);
    }
};