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
        mx += u.v, sum += u.v * (r - l);
    }
};

const Lazy LID = {0, true};
const Node NID = {-INF, 0};
 
struct LazySeg { 
    int n;
    vt<Node> seg;
    vt<Lazy> lazy;
    void init(int _n) {
        for (n = 1; n < _n; n *= 2);
        seg.resize(2 * n, NID);
        lazy.resize(2 * n, LID);
    }
    void pull(int i) {
        seg[i] = seg[2 * i] + seg[2 * i + 1];
    }
    void push(int i, int l, int r) {
        seg[i].upd(lazy[i], l, r);
        if (r - l > 1) FOR (j, 2) lazy[2 * i + j] += lazy[i];
        lazy[i] = LID;
    }
    void build() {
        for (int i = n - 1; i > 0; i--) pull(i);
    }
    void upd(int lo, int hi, Lazy val) { upd(lo, hi, val, 1, 0, n); }
    void upd(int lo, int hi, Lazy val, int i, int l, int r) {
        if (r == -1) r = n;
        push(i, l, r);
        if (r <= lo || l >= hi) return;
        if (lo <= l && r <= hi) {
            lazy[i] += val;
            push(i, l, r);
            return;
        }
        int m = (l + r) / 2;
        upd(lo, hi, val, 2 * i, l, m);
        upd(lo, hi, val, 2 * i + 1, m, r);
        pull(i);
    }
    Node query() { return query(0, n, 1, 0, n); }
    Node query(int lo, int hi) { return query(lo, hi, 1, 0, n); }
    Node query(int lo, int hi, int i, int l, int r) {
        push(i, l, r);
        if (r <= lo || l >= hi) return NID;
        if (lo <= l && r <= hi) return seg[i];
        int m = (l + r) / 2;
        return query(lo, hi, 2 * i, l, m) + query(lo, hi, 2 * i + 1, m, r);
    }
    Node& operator[](int i) {
        return seg[i + n];
    }
};