#include "../../template.h"

using ptr = struct Node*;
const int sz = 1 << 18;
 
struct Node {
    #define func(a, b) min(a, b)
    #define ID inf
    int v;
    ptr lc, rc;
 
    ptr pull(ptr lc, ptr rc) {
        return new Node {func(lc->v, rc->v), lc, rc};
    }
 
    ptr upd(int i, int nv, int l = 0, int r = sz) {
        if (r - l == 1) return new Node {nv};
        int m = (l + r) / 2;
        if (i < m) return pull(lc->upd(i, nv, l, m), rc);
        else return pull(lc, rc->upd(i, nv, m, r));
    }
 
    int query(int lo, int hi, int l = 0, int r = sz) {
        if (lo >= r || hi <= l) return ID;
        if (lo <= l && r <= hi) return v;
        int m = (l + r) / 2;
        return func(lc->query(lo, hi, l, m), 
            rc->query(lo, hi, m, r)); 
    }
    #undef id
    #undef func
};