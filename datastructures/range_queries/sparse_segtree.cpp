#include "../../template.h"

using ptr = struct Node*;
const int sz = 1 << 30;
struct Node {
    int val;
    ptr lc, rc;

    ptr get(ptr& p) { return p ? p : p = new Node {inf}; }

    int query(int lo, int hi, int l = 0, int r = sz) {
        if (lo >= r || hi <= l) return inf;
        if (lo <= l && r <= hi) return val;
        int m = (l + r) / 2;
        return min(get(lc)->query(lo, hi, l, m), get(rc)->query(lo, hi, m, r));
    }

    int upd(int i, int nval, int l = 0, int r = sz) {
        if (l == r) return val = nval;
        int m = (l + r) / 2;
        if (i < m) get(lc)->upd(i, nval, l, m);
        else get(rc)->upd(i, nval, m, r);
        return val = min(get(lc)->val, get(rc)->val);
    }
};