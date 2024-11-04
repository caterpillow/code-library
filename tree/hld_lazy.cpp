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

const Node NID = {-INF, 0};
const Lazy LID = {0, true};
const int sz = 1 << 17;

struct LazySeg {
    vt<Node> seg;
    vt<Lazy> lazy;
    void init() {
        seg.resize(2 * sz, NID);
        lazy.resize(2 * sz, LID);
    }
    void pull(int i) {
        seg[i] = seg[2 * i] + seg[2 * i + 1];
    }
    void push(int i, int l, int r) {
        seg[i].upd(lazy[i], l, r);
        if (l != r)  F0R (j, 2) lazy[2 * i + j] += lazy[i];
        lazy[i] = LID;
    }
    void build() {
        for (int i = sz - 1; i > 0; i--) pull(i);
    }
    void upd(int lo, int hi, Lazy val, int i = 1, int l = 0, int r = sz - 1) {
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
    Node query(int lo = 0, int hi = sz - 1, int i = 1, int l = 0, int r = sz - 1) {
        push(i, l, r);
        if (r < lo || l > hi) return NID;
        if (lo <= l && r <= hi) return seg[i];
        int m = (l + r) / 2;
        return query(lo, hi, 2 * i, l, m) + query(lo, hi, 2 * i + 1, m + 1, r);
    }
    Node& operator[](int i) {
        return seg[i + sz];
    }
};

template<bool in_edges> struct HLD {
    vt<int> adj[sz];
    int par[sz], root[sz], depth[sz], size[sz], pos[sz], time;
    vt<int> rpos;
    LazySeg tree;

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
    void modify(int u, int v, Lazy upd) {
        process(u, v, [&] (int l, int r) { tree.upd(l, r, upd); });
    }
    Node query(int u, int v) {
        Node res = NID;
        process(u, v, [&] (int l, int r) { res = res + tree.query(l, r); });
        return res;
    }
    void modify_subtree(int u, Lazy upd) {
        tree.upd(pos[u] + in_edges, pos[u] + size[u] - 1, upd);
    }
    Node query_subtree(int u) {
        return tree.query(pos[u] + in_edges, pos[u] + size[u] - 1);
    }
};