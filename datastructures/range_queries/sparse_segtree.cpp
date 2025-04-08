#include "../../template.h"

using ptr = struct Node*;
const int sz = 1 << 30;
struct Node {
    #define func(a, b) min(a, b)
    #define ID INF
    ll val;
    ptr lc, rc;

    ptr get(ptr& p) { return p ? p : p = new Node {ID}; }

    ll query(int lo, int hi, int l = 0, int r = sz) {
        if (lo >= r || hi <= l) return ID;
        if (lo <= l && r <= hi) return val;
        int m = (l + r) / 2;
        return func(get(lc)->query(lo, hi, l, m), 
            get(rc)->query(lo, hi, m, r));
    }

    ll upd(int i, ll nval, int l = 0, int r = sz) {
        if (r - l == 1) return val = nval;
        int m = (l + r) / 2;
        if (i < m) get(lc)->upd(i, nval, l, m);
        else get(rc)->upd(i, nval, m, r);
        return val = func(get(lc)->val, get(rc)->val);
    }
    #undef ID
    #undef func
};