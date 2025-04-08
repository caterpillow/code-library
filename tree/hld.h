#include "../template.h"

struct SegTree {
    int n;
    vt<int> seg;
    void init(int _n) {
        for (n = 1; n < _n; n *= 2);
        seg.resize(2 * n);
    }
    int query(int i, int balls) {
        int sum = 0;
        for (i += n; i > 0; i /= 2) sum += seg[i];
        return sum;
    }
    void upd(int l, int r, int v) {
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) seg[l++] += v;
            if (r & 1) seg[--r] += v;
        }
    }
};

template<bool in_edges> struct HLD {
    int n;
    vt<vt<int>> adj;
    vt<int> par, root, depth, size, pos;
    int time;
    SegTree tree;
    void ae(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    void dfs_sz(int u) {
        size[u] = 1;
        for (int& v : adj[u]) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            adj[v].erase(find(all(adj[v]), u));
            dfs_sz(v);
            size[u] += size[v];
            if (size[v] > size[adj[u][0]]) swap(v, adj[u][0]);
        }
    }
    void dfs_hld(int u) {
        pos[u] = time++;
        for (int& v : adj[u]) {
            root[v] = (v == adj[u][0] ? root[u] : v);
            dfs_hld(v);
        }
    }
    void init(int _n) {
        n = _n;
        adj.resize(n);
        par = root = depth = size = pos = vt<int>(n);
    }
    void gen(int r = 0) {
        par[r] = depth[r] = time = 0;
        dfs_sz(r);
        root[r] = r;
        dfs_hld(r);
        tree.init(n);
    }
    int lca(int u, int v) {
        while (root[u] != root[v]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            v = par[root[v]];
        }
        return depth[u] < depth[v] ? u : v;
    }
    template <class Op>
    void process(int u, int v, Op op) {
        while (root[u] != root[v]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            op(pos[root[v]], pos[v] + 1);
            v = par[root[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u] + in_edges, pos[v] + 1);
    }
    void upd(int u, int v, ll upd) {
        process(u, v, [&] (int l, int r) { 
            tree.upd(l, r, upd); 
        });
    }
    ll query(int u, int v) {
        ll res = 0;
        process(u, v, [&] (int l, int r) { 
            res = res + tree.query(l, r); 
        });
        return res;
    }
};