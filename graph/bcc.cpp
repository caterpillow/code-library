#include "../template.h"

struct BCC { 
    int n, t; 
    vt<vt<int>> adj, comps;
    vt<int> tin, low, stk;

    void init(int _n) {
        n = _n;
        adj.resize(n);
    }

    void ae(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void dfs(int u) {
        tin[u] = low[u] = ++t;
        stk.pb(u);   
        for (int v : adj[u]) {
            if (tin[v]) low[u] = min(low[u], tin[v]);
            else {
                dfs(v);
                low[u] = min(low[u], low[v]);
                if (low[v] == tin[u]) {
                    comps.pb({u});
                    for (int w = -1; w != v;) {
                        comps.back().pb(w = stk.back());
                        stk.pop_back();
                    }
                }
            }
        }
    }

    void gen() {
        t = 0;
        tin = low = vt<int>(n);
        F0R (u, n) if (!tin[u]) dfs(u); 
        F0R (u, n) if (!size(adj[u])) comps.pb({u});   
    }
};