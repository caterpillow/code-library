#include "../template.h"

struct BCT { 
    int n, t = 0; 
    vt<vt<int>> adj, comps;
    vt<int> tin, low, stk, is_art;

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
                    is_art[u] = (tin[u] > 1 || tin[v] > 2);
                    comps.pb({u});
                    for (int w = -1; w != v;) {
                        comps.back().pb(w = stk.back());
                        stk.pop_back();
                    }
                }
            }
        }
    }

    // make sure the graph is connected!
    void gen(int& n0, vt<vt<int>>& adj0, vt<int>& id) {
        t = 0;
        tin = low = is_art = vt<int>(n);
        F0R (u, n) if (!tin[u]) dfs(u); 
        F0R (u, n) if (!size(adj[u])) comps.pb({u});   

        id.resize(n);   
        F0R (u, n) {
            if (is_art[u]) {
                id[u] = n0++;
                adj0.pb({});
            }
        }

        for (auto& comp : comps) {
            adj0.pb({});
            for (int u : comp) {
                if (is_art[u]) {
                    adj0[n0].pb(id[u]);
                    adj0[id[u]].pb(n0);
                } else id[u] = n0;
            }
            n0++;
        }
    }
};

template<class T> struct RMQ {
    vt<vt<T>> dp;
    void init(const vt<T>& v) {
        dp.resize(32 - __builtin_clz(size(v)), vt<T>(size(v)));
        copy(all(v), begin(dp[0]));
        for (int j = 1; 1 << j <= size(v); ++j) {
            F0R (i, size(v) - (1 << j) + 1) dp[j][i] = min(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
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
    vt<int> depth, pos, par, id;
    vt<pl> tmp; 
    RMQ<pl> rmq;
    void init(BCT& bct) { 
        n = 0;
        bct.gen(n, adj, id);
        depth = pos = par = vt<int>(n); 
    }
    void dfs(int x) {
        pos[x] = size(tmp); 
        tmp.pb({depth[x], x}); 
        for(int y : adj[x]) {
            if (y != par[x]) {
                depth[y] = depth[par[y] = x] + 1, dfs(y);
                tmp.pb({depth[x], x}); 
            }
        }
    }
    void gen(int rt = 0) { 
        par[rt] = rt; 
        dfs(rt); 
        rmq.init(tmp); 
    }
    int lca(int u, int v) {
        u = pos[u], v = pos[v]; 
        if (u > v) swap(u,v);
        return rmq.query(u,v).s;
    }
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)]; 
    }
};