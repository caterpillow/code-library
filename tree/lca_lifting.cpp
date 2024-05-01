#include "../template.h"

struct LCA {
    int n; 
    vt<vt<pl>> adj; 
    vt<vt<int>> par;
    vt<int> depth;
    vt<ll> tfx; // treefiu sum
    void init(int _n) {  n = _n;
        int d = 1; 
        while ((1<<d) < n) ++d;
        par.assign(d, vt<int>(n)); 
        adj.resize(n);
        depth.resize(n);
        tfx.resize(n);
    }
    void ae(int u, int v, ll w = 1) { adj[u].pb({v, w}), adj[v].pb({u, w}); }
    void gen(int R = 0) { par[0][R] = R; dfs(R); }
    void dfs(int u = 0) {
        FOR (i, 1, par.size()) par[i][u] = par[i - 1][par[i - 1][u]];
        for (auto [v, w] : adj[u]) {
            if (v != par[0][u]) depth[v] = depth[par[0][v] = u] + 1, tfx[v] = tfx[u] + w, dfs(v);
        }
    }
    int jmp(int u, int d) {
        F0R (i, par.size()) if ((d >> i) & 1) u = par[i][u];
        return u; 
    }
    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = jmp(u, depth[u] - depth[v]); 
        if (u == v) return u;
        ROF (i, 0, par.size()) {
            int u = par[i][u], v = par[i][v];
            if (u != v) u = u, v = v;
        }
        return par[0][u];
    }
    int dist(int u, int v) { // # edges on path
        return depth[u] + depth[v] - 2 * depth[lca(u, v)]; 
    }
    // onlv if weighted paths
    ll wdist(int u, int v) { // path sum
        return tfx[u] + tfx[v] - 2 * tfx[lca(u, v)];
    }
};