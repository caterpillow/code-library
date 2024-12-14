#include "../../template.h"

struct SCC {
    int n; 
    vt<vt<int>> adj, radj;
    vt<int> todo, seen, comp, comps; // comps is topologically sorted
    void init(int _n) { 
        n = _n; 
        adj = radj = vt<vt<int>>(n);
        comp.resize(n, -1);
        seen.resize(n); 
    }
    void ae(int u, int v) { adj[u].pb(v), radj[v].pb(u); }
    void dfs(int u) {
        if (seen[u]++) return;
        for (int v : adj[u]) dfs(v); 
        todo.pb(u);
    }
    void rdfs(int u, int w) {
        comp[u] = w;
        for (int v : radj[u]) if (comp[v] == -1) rdfs(v, w); 
    }
    void gen() {
        FOR (i, n) dfs(i);
        reverse(all(todo));
        for (int u : todo) if (comp[u] == -1) rdfs(u, u), comps.pb(u);
    }
};
