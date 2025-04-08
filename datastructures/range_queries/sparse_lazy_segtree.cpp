#include "../../template.h"

struct Lazy {
    int v;
    bool inc;

    void operator+=(const Lazy& oth) {
        if (!oth.inc) v = 0, inc = 0;
        v += oth.v;
    }
};

struct Val {
    ll sum;
    int mx;

    Val operator+(const Val& oth) const {
        return {sum + oth.sum, max(mx, oth.mx)};
    }

    void upd(Lazy& lazy, ll l, ll r) {
        if (!lazy.inc) sum = mx = 0;
        sum += lazy.v * (r - l);
        mx += lazy.v;
    }
};

const Lazy lid = {0, 1};
const Val vid = {0, -inf};

using ptr = struct Node*;
const int sz = 1 << 30;
struct Node {
    Val val;
    Lazy lazy;
    ptr lc, rc;

    ptr get(ptr& p) { return p ? p : p = new Node {vid, lid}; }

    void push(ll l, ll r) {
        val.upd(lazy, l, r);
        if (r - l > 1) get(lc)->lazy += lazy, get(rc)->lazy += lazy;
        lazy = lid;
    }

    Val query(ll lo, ll hi, ll l = 0, ll r = sz) {
        push(l, r);
        if (lo >= r || hi <= l) return vid;
        if (lo <= l && r <= hi) return val;
        ll m = (l + r) / 2;
        return get(lc)->query(lo, hi, l, m) + get(rc)->query(lo, hi, m, r);
    }

    void upd(ll lo, ll hi, Lazy v, ll l = 0, ll r = sz) {
        push(l, r);
        if (lo >= r || hi <= l) return;
        if (lo <= l && r <= hi) {
            lazy += v;
            push(l, r);
            return;
        }
        ll m = (l + r) / 2;
        get(lc)->upd(lo, hi, v, l, m);
        get(rc)->upd(lo, hi, v, m, r);
        val = get(lc)->val + get(rc)->val;
    }
};