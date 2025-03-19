#include "../../template.h"

template<class T> struct RangeQuery {
    #define comb(a, b) (a) + (b)
    int lg, n;
    T id; // identity element
    vt<vt<T>> stor;
    vt<T> a;
    void fill(int l, int r, int ind) {
        if (ind < 0) return;
        int m = (l + r) / 2;
        T prod = id; 
        FOR (i, m, r) stor[i][ind] = prod = comb(prod, a[i]);
        prod = id; 
        ROF (i, l, m) stor[i][ind] = prod = comb(a[i], prod);
        fill(l, m, ind - 1); 
        fill(m, r, ind - 1);
    }
    template <typename It>
    void build(It l, It r, T _id) {
        lg = 1, id = _id;
        while ((1 << lg) < r - l) lg++;
        n = 1 << lg;
        a.resize(n, id);
        for (It i = l; i != r; i++) a[i - l] = *i;
        stor.resize(n, vt<T>(32 - __builtin_clz(n)));
        fill(0, n, lg - 1);
    }
    T query(int l, int r) {
        if (l == r) return a[l];
        int t = 31 - __builtin_clz(r ^ l);
        return comb(stor[l][t], stor[r][t]);
    }
    #undef comb
};