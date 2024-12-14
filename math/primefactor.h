#include "../template.h"

template<class T>
vt<pair<T, int>> prime_factor(T x) {
    vt<pair<T, int>> ret;
    for (T i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            int p = 0;
            while (x % i == 0) x /= i, p++;
            ret.pb({i, p});
        }
    }
    if (x > 1) ret.eb(x, 1);
    return ret;
}