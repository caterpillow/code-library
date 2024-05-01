#include "../template.h"

struct Lazy {
    ll v;
    bool inc;
    void operator+=(const Lazy &b) {
        if (b.inc) v += b.v;
        else v = b.v, inc = false;
    }
};
 
struct Node {
    ll mx, sum;
    Node operator+(const Node &b) {
        return {max(mx, b.mx), sum + b.sum};
    }
    void upd(const Lazy &u, int l, int r) {
        if (!u.inc) mx = sum = 0;
        mx += u.v, sum += u.v * (r - l + 1);
    }
};

const Node NID = {0, 0};
const Lazy UID = {0, true};
 
template<class T, class U, int SZ> struct LazySeg { 
    vt<T> seg;
    vt<U> lazy;
    void init() {
        seg.resize(2 * SZ, NID);
        lazy.resize(2 * SZ, UID);
    }
    void pull(int i) {
        seg[i] = seg[2 * i] + seg[2 * i + 1];
    }
    void push(int i, int l, int r) {
        seg[i].upd(lazy[i], l, r);
        if (l != r)  F0R (j, 2) lazy[2 * i + j] += lazy[i];
        lazy[i] = UID;
    }
    void build() {
        for (int i = SZ - 1; i > 0; i--) pull(i);
    }
    void upd(int lo, int hi, U val, int i = 1, int l = 0, int r = SZ - 1) {
        push(i, l, r);
        if (r < lo || l > hi) return;
        if (lo <= l && r <= hi) {
            lazy[i] += val;
            push(i, l, r);
            return;
        }
        int m = (l + r) / 2;
        upd(lo, hi, val, 2 * i, l, m);
        upd(lo, hi, val, 2 * i + 1, m + 1, r);
        pull(i);
    }
    T query(int lo = 0, int hi = SZ - 1, int i = 1, int l = 0, int r = SZ - 1) {
        push(i, l, r);
        if (r < lo || l > hi) return NID;
        if (lo <= l && r <= hi) return seg[i];
        int m = (l + r) / 2;
        return query(lo, hi, 2 * i, l, m) + query(lo, hi, 2 * i + 1, m + 1, r);
    }
    T& operator[](int i) {
        return seg[i + SZ];
    }
};

template<class T, class U, int sz, bool in_edges> struct HLD {
    vt<int> adj[sz];
    int par[sz], root[sz], depth[sz], size[sz], pos[sz], time;
    vt<int> rpos;
    LazySeg<T, U, sz> tree;

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
        rpos.pb(u);
        for (int& v : adj[u]) {
            root[v] = (v == adj[u][0] ? root[u] : v);
            dfs_hld(v);
        }
    }
    void init(int r = 0) {
        par[r] = depth[r] = time = 0;
        dfs_sz(r);
        root[r] = r;
        dfs_hld(r);
        tree.init();
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
            op(pos[root[v]], pos[v]);
            v = par[root[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u] + in_edges, pos[v]);
    }
    void modify(int u, int v, U upd) {
        process(u, v, [&] (int l, int r) { tree.upd(l, r, upd); });
    }
    T query(int u, int v) {
        T res = NID;
        process(u, v, [&] (int l, int r) { res = res + tree.query(l, r); });
        return res;
    }
    void modify_subtree(int u, U upd) {
        tree.upd(pos[u] + in_edges, pos[u] + size[u] - 1, upd);
    }
    T query_subtree(int u) {
        return tree.query(pos[u] + in_edges, pos[u] + size[u] - 1);
    }
};

ll n, k;
HLD<Node, Lazy, 1 << 16, false> hld;