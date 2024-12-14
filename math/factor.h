#include "../template.h"

template<class T>
vt<T> factor(T x) {
    vt<T> factors;
    for (T i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            factors.pb(i);
            if (i * i != x) factors.pb(x / i);
        }
    }
    return factors;
}