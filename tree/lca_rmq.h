#include "../template.h"

template<class T> struct RMQ {
    vt<vt<T>> dp;
    void init(const vt<T>& v) {
        dp.resize(32 - __builtin_clz(size(v)), vt<T>(size(v)));
        copy(all(v), begin(dp[0]));
        for (int j = 1; 1 << j <= size(v); ++j) {
            FOR (i, size(v) - (1 << j) + 1) dp[j][i] = min(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
        }
    }
    T query(int l, int r) {
        int d = 31 - __builtin_clz(r - l + 1);
        return min(dp[d][l], dp[d][r - (1 << d) + 1]); 
    }
};

struct LCA {
    int n; 
    vt<vt<int>> adj;
    vt<int> depth, pos, par; // rev is for compress
    vt<pl> tmp; 
    RMQ<pl> r;
    void init(int _n) { 
        n = _n; 
        adj.resize(n); 
        depth = pos = par = vt<int>(n); 
    }
    void ae(int x, int y) { 
        adj[x].pb(y), adj[y].pb(x); 
    }
    void dfs(int x) {
        pos[x] = size(tmp); 
        tmp.pb({depth[x], x}); 
        for(int y : adj[x]) 
            if (y != par[x]) {
                depth[y] = depth[par[y] = x] + 1, dfs(y);
                tmp.pb({depth[x], x}); 
            }
    }
    void gen(int R = 0) { 
        par[R] = R; 
        dfs(R); r.init(tmp); 
    }
    int lca(int u, int v) {
        u = pos[u], v = pos[v]; 
        if (u > v) swap(u,v);
        return r.query(u,v).s;
    }
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)]; 
    }
};