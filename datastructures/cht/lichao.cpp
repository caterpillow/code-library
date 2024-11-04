#include "../../template.h"

struct Line {
    ll m, c;
    ll operator()(ll x) {
        return m * x + c;
    }
};

const ll sz = 1ll << 30;

using ptr = struct Node*;
struct Node {
    ptr lc, rc;
    Line line;

    Node(Line _line) {
        line = _line;
        lc = rc = 0;
    }
};

// min tree (flip signs for max)
void add(ptr& n, Line loser, ll l = 0, ll r = sz) {
    if (n ? 0 : n = new Node(loser)) return;
    ll m = (l + r) / 2;
    if (loser(m) < n->line(m)) swap(loser, n->line);
    if (r - l == 1) return;
    if (loser(l) < n->line(l)) add(n->lc, loser, l, m);
    else add(n->rc, loser, m, r);
}

ll query(ptr n, ll x, ll l = 0, ll r = sz) {
    if (!n) return sz;
    ll m = (l + r) / 2;
    if (x < m) return min(n->line(x), query(n->lc, x, l, m));
    else return min(n->line(x), query(n->rc, x, m, r));
}