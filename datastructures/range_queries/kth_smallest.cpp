#include "../../template.h"

using ptr = struct Node*;
const ll sz = 1 << 30;
 
struct Node {
    int cnt;
    ptr lc, rc;
 
    ptr pull(ptr lc, ptr rc) {
        return new Node {lc->cnt + rc->cnt, lc, rc};
    }
 
    ptr upd(int i, int l = 0, int r = sz - 1) {
        if (l == r) return new Node {cnt + 1};
        int m = (l + r) / 2;
        if (i <= m) return pull(lc->upd(i, l, m), rc);
        else return pull(lc, rc->upd(i, m + 1, r));
    }
};

int walk(ptr lo, ptr hi, int k, int l = 0, int r = sz - 1) {
    if (l == r) return l;
    int m = (l + r) / 2;
    int lhs = hi->lc->cnt - lo->lc->cnt;
    if (lhs >= k) return walk(lo->lc, hi->lc, k, l, m);
    else return walk(lo->rc, hi->rc, k - lhs, m + 1, r);
}