#include "../../template.h"

struct Lazy {
    ll v;
    bool inc;
    void operator+=(const Lazy &b) {
        if (b.inc) v += b.v;
        else v = b.v, inc = false;
    }
};
 
struct Node {
    ll mx, sum;
    Node operator+(const Node &b) {
        return {max(mx, b.mx), sum + b.sum};
    }
    void upd(const Lazy &u, int l, int r) {
        if (!u.inc) mx = sum = 0;
        mx += u.v, sum += u.v * (r - l + 1);
    }
};

const Lazy LID = {0, true};
const Node NID = {-INF, 0};
 
const int sz = 1 << 17;
struct LazySeg { 
    vt<Node> seg;
    vt<Lazy> lazy;
    void init() {
        seg.resize(2 * sz, NID);
        lazy.resize(2 * sz, LID);
    }
    void pull(int i) {
        seg[i] = seg[2 * i] + seg[2 * i + 1];
    }
    void push(int i, int l, int r) {
        seg[i].upd(lazy[i], l, r);
        if (l != r) F0R (j, 2) lazy[2 * i + j] += lazy[i];
        lazy[i] = LID;
    }
    void build() {
        for (int i = sz - 1; i > 0; i--) pull(i);
    }
    void upd(int lo, int hi, Lazy val, int i = 1, int l = 0, int r = sz - 1) {
        push(i, l, r);
        if (r < lo || l > hi) return;
        if (lo <= l && r <= hi) {
            lazy[i] += val;
            push(i, l, r);
            return;
        }
        int m = (l + r) / 2;
        upd(lo, hi, val, 2 * i, l, m);
        upd(lo, hi, val, 2 * i + 1, m + 1, r);
        pull(i);
    }
    Node query(int lo = 0, int hi = sz - 1, int i = 1, int l = 0, int r = sz - 1) {
        push(i, l, r);
        if (r < lo || l > hi) return NID;
        if (lo <= l && r <= hi) return seg[i];
        int m = (l + r) / 2;
        return query(lo, hi, 2 * i, l, m) + query(lo, hi, 2 * i + 1, m + 1, r);
    }
    Node& operator[](int i) {
        return seg[i + sz];
    }
};