#include "../template.h"

struct SCC {
    ll N; 
    vt<vt<ll>> adj, radj;
    vt<ll> todo, comp, comps; 
    vt<bool> seen;
    void init(ll _N) { 
        N = _N; 
        adj.resize(N), radj.resize(N);
        comp = vt<ll>(N,-1);
        seen.resize(N); 
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
        F0R (i, N) if (!seen[i]) dfs(i);
        reverse(all(todo)); 
        for (ll x : todo) if (comp[x] == -1) dfs2(x, x), comps.pb(x);
    }
};