#include "../ds/range_queries/sparse_table.cpp"

struct LCA {
    int n; 
    vt<vt<int>> adj;
    vt<int> depth, pos, par; 
    vt<pl> tmp; 
    RMQ<pl> rmq;
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
        for (int y : adj[x]) 
            if (y != par[x]) {
                depth[y] = depth[par[y] = x] + 1, dfs(y);
                tmp.pb({depth[x], x}); 
            }
    }
    void gen(int R = 0) { 
        par[R] = R; 
        dfs(R); rmq.init(tmp); 
    }
    int lca(int u, int v) {
        u = pos[u], v = pos[v]; 
        if (u > v) swap(u, v);
        return rmq.query(u, v + 1).s;
    }
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)]; 
    }
};