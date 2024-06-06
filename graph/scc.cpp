#include "../template.h"

struct SCC {
    ll n; 
    vt<vt<ll>> adj, radj;
    vt<ll> todo, comp, comps; 
    vt<bool> seen;
    void init(ll _n) { 
        n = _n; 
        adj.resize(n);
        radj.resize(n);
        comp = vt<ll>(n, -1);
        seen.resize(n); 
    }
    void ae(ll x, ll y) { adj[x].pb(y), radj[y].pb(x); }
    void dfs(ll x) {
        seen[x] = 1; 
        for(ll y : adj[x]) if (!seen[y]) dfs(y);
        todo.pb(x); 
    }
    void dfs2(ll x, ll v) {
        comp[x] = v; 
        for (ll y : radj[x]) if (comp[y] == -1) dfs2(y, v); 
    }
    void gen() {
        F0R (i, n) if (!seen[i]) dfs(i);
        reverse(all(todo)); 
        for (ll x : todo) if (comp[x] == -1) dfs2(x, x), comps.pb(x);
    }
};