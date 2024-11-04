#include "../../template.h"

using ptr = struct Node*;
const int sz = 1 << 18;
 
struct Node {
    int v;
    ptr lc, rc;
 
    ptr pull(ptr lc, ptr rc) {
        return new Node {min(lc->v, rc->v), lc, rc};
    }
 
    ptr upd(int i, int nv, int l = 0, int r = sz) {
        if (l == r) return new Node {nv};
        int m = (l + r) / 2;
        if (i < m) return pull(lc->upd(i, nv, l, m), rc);
        else return pull(lc, rc->upd(i, nv, m, r));
    }
 
    int query(int lo, int hi, int l = 0, int r = sz) {
        if (lo > r || hi < l) return 1e9;
        if (lo <= l && r <= hi) return v;
        int m = (l + r) / 2;
        return min(lc->query(lo, hi, l, m), rc->query(lo, hi, m, r)); 
    }
};