#include "../../template.h"

struct DynaCon {
    int n, q, t = 0;
    vt<vt<pi>> seg;
    map<pi, int> eds;
    DSU dsu;
    void init(int _n, int _q) {
        for (q = 1; q < _q; q *= 2);
        seg.resize(2 * q);
        dsu.init(n = _n);
    }
    void toggle(int u, int v, bool erase = true) {
        if (u > v) swap(u, v);
        if (eds.count({u, v})) {
            for (int l = eds[{u, v}] + q, r = min(++t + q, 2 * q); l < r; l /= 2, r /= 2) {
                if (l & 1) seg[l++].pb({u, v});
                if (r & 1) seg[--r].pb({u, v});
            }
            if (erase) eds.erase({u, v});
        } else eds[{u, v}] = t++;
    }
    void query() { seg[q + t++].pb({-1, -1}); }
    void dfs(int i, vt<int>& ans) {
        dsu.push();
        for (auto [u, v] : seg[i]) {
            if (u == -1) ans.pb(dsu.comps());
            else dsu.unite(u, v);
        }
        if (i < q) dfs(2 * i, ans), dfs(2 * i + 1, ans);
        dsu.pop();
    }
    vt<int> ans() {
        for (auto [u, v] : eds) toggle(u.f, u.s, false);
        vt<int> res;
        dfs(1, res);
        return res;
    }
};