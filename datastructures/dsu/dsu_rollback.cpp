#include "../../template.h"

struct DSU {
    int n;
    vt<int> e;
    vt<vt<pi>> stk; 
    void init(int _n) { n = _n; e.resize(n + 1, -1); e[n] = n; }
    void push() { stk.pb({}); }
    void pop() { 
        reverse(all(stk.back()));
        for (auto [i, v] : stk.back()) e[i] = v;
        stk.pop_back();
    }
    void upd(int i, int v) { stk.back().pb({i, e[i]}); e[i] = v; }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (e[x] < e[y]) swap(x, y);
        upd(y, e[x] + e[y]);
        upd(x, y);
        upd(n, e[n] - 1);
    }
    int comps() { return e[n]; }
};