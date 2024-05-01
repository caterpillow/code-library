#include "../../template.h"

struct SegTree {
    int n;
    vt<int> seg;
    void init(int _n) {
        for (n = 1; n < _n; n *= 2);
        seg.resize(2 * n);
    }
    void upd(int i, int v) {
        seg[i += n] = v;
        while (i /= 2) seg[i] = seg[2 * i] + seg[2 * i + 1];
    }
    int query(int l, int r) { // inc inc
        int res = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) res += seg[l++];
            if (r & 1) res += seg[--r];
        }
        return res;
    }
};