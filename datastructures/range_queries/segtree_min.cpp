#include "../../template.h"

struct SegTree {
    #define func min
    // dont forget to change identity too
    int n;
    vt<ll> seg;
    void init(int _n) {
        for (n = 1; n < _n; n *= 2);
        seg.resize(2 * n, INF);
    }
    void upd(int i, ll v) {
        seg[i += n] = v;
        while (i /= 2) seg[i] = func(seg[2 * i], seg[2 * i + 1]);
    }
    ll query(int l, int r) { // inc exc 
        ll res = INF;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) res = func(res, seg[l++]);
            if (r & 1) res = func(seg[--r], res);
        }
        return res;
    }
    #undef func
};