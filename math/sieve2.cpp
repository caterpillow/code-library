#include "../template.h"

struct Sieve {
    vi lp, primes;
    void calc(int n) {
        lp.rsz(n);
		FOR (i, 2, n) { 
			if (lp[i] == 0) lp[i] = i, primes.pb(i); 
			for (int p : primes) {
				if (p > lp[i] || i * p >= n) break;
				lp[i * p] = p;
			}
		}
    }
    void get_prime_fact(int x, vpi& out) {
        if (x == 1) return;
        if (out.empty() || out.back().f != lp[x]) 
            out.eb(x, 1);
        else out.back().s++;
    }
};