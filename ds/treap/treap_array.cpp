#include "../../template.h"

// missing lots of features

#include <ext/random>

random_device rd;
__gnu_cxx::sfmt19937 mt(rd());

struct Node { int l, r, pri, sz; } m[1000001];

inline int pull(int n) {
    m[n].sz = m[m[n].l].sz + 1 + m[m[n].r].sz;
    return n;
}

pair<int, int> spliti(int n, int i) {
    if (!n) return {};
    if (i <= m[m[n].l].sz) {
        auto [l, r] = spliti(m[n].l, i);
        m[n].l = r;
        return {l, pull(n)};
    } else {
        auto [l, r] = spliti(m[n].r, i - m[m[n].l].sz - 1);
        m[n].r = l;
        return {pull(n), r};
    }
}

int merge(int l, int r) {
    if (!l || !r) return max(l, r);
    if (m[l].pri > m[r].pri) return m[l].r = merge(m[l].r, r), pull(l);
    else return m[r].l = merge(l, m[r].l), pull(r);
}

int ins(int n, int i, int v) {
    if (!n) return v;
    if (m[v].pri > m[n].pri) {
        tie(m[v].l, m[v].r) = spliti(n, i);
        return pull(v);
    }
    if (i <= m[m[n].l].sz) m[n].l = ins(m[n].l, i, v);
    else m[n].r = ins(m[n].r, i - m[m[n].l].sz - 1, v);
    return pull(n);
}