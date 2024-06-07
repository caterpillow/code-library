#include "../template.h"

struct Dinic {
    struct Edge {
        int to; 
        ll flo, cap; 
    };
    int N; 
    vt<Edge> eds; 
    vt<vt<int>> adj;
    void init(int _N) {
        N = _N; 
        adj.resize(N), cur.resize(N); 
    }
    void ae(int u, int v, ll cap, ll rcap = 0) { 
        assert(min(cap, rcap) >= 0); 
        adj[u].pb(eds.size()); 
        eds.pb({v, 0, cap});
        adj[v].pb(eds.size()); 
        eds.pb({u, 0, rcap});
    }
    vt<int> lev; 
    vt<vt<int>::iterator> cur;
    bool bfs(int s, int t) {
        lev = vt<int>(N, -1); 
        F0R(i, N) cur[i] = begin(adj[i]);
        queue<int> q({s}); 
        lev[s] = 0; 
        while (q.size()) { 
            int u = q.front(); 
            q.pop();
            for(auto &e : adj[u]) { 
                const Edge& E = eds[e];
                int v = E.to; 
                if (lev[v] < 0 && E.flo < E.cap) q.push(v), lev[v] = lev[u] + 1;
            }
        }
        return lev[t] >= 0;
    }
    ll dfs(int v, int t, ll flo) {
        if (v == t) return flo;
        for (; cur[v] != end(adj[v]); cur[v]++) {
            Edge& E = eds[*cur[v]];
            if (lev[E.to] != lev[v] + 1 || E.flo == E.cap) continue;
            ll df = dfs(E.to, t, min(flo, E.cap-E.flo));
            if (df) { 
                E.flo += df; eds[*cur[v]^1].flo -= df;
                return df; 
            }       
        }
        return 0;
    }
    ll maxFlow(int s, int t) {
        ll tot = 0; 
        while (bfs(s, t)) while (ll df = dfs(s, t, numeric_limits<ll>::max())) tot += df;
        return tot;
    }
};