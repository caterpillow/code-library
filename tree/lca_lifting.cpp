#include "../template.h"

struct BinaryLifting {
    int n, r; 
    vt<vt<int>> adj; 
    vt<int> par, jmp, depth;
    void init(int _n) {  
        n = _n;
        adj.resize(n);
        par = jmp = depth = vt<int>(n);
    }
    void ae(int u, int v, ll w = 1) { adj[u].pb(v), adj[v].pb(u); }
    void gen(int _r = 0) { r = _r, par[r] = jmp[r] = r; dfs(r); }
    void dfs(int u = 0) {
        for (int v : adj[u]) {
            depth[v] = depth[u] + 1;
            par[v] = u;
            if (depth[jmp[jmp[u]]] + depth[u] == 2 * depth[jmp[u]]) jmp[v] = jmp[jmp[u]];
            else jmp[v] = u;
            adj[v].erase(find(all(adj[v]), u));
            dfs(v);
        }
    }
    int lift(int u, int d) {
        if (d == 0) return r;
        while (depth[par[u]] >= d) {
            if (depth[jmp[u]] >= d) u = jmp[u];
            else u = par[u];
        }
        return u;
    }
    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = lift(u, depth[v]); 
        if (u == v) return u;
        while (u != v) {
            if (jmp[u] != jmp[v]) u = jmp[u], v = jmp[v];
            else u = par[u], v = par[v];
        }
        return u;
    }
    int dist(int u, int v) { // # of edges on path
        return depth[u] + depth[v] - 2 * depth[lca(u, v)]; 
    }
};
