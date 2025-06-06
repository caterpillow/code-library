#include "../../template.h"

// 1 indexed O(nm)
struct Blossom {
    int n, h, t, cnt;
    vpi edges;
    vi vis, q, mate, col, fa, pre, he;
    void ae(int u, int v) {
        assert(u && v);
        edges.pb({he[u], v}); he[u] = size(edges) - 1;
        edges.pb({he[v], u}); he[v] = size(edges) - 1;
    }
    inline int get(int u) { return fa[u] == u ? u : fa[u] = get(fa[u]); }
    void aug(int u, int v) {
        for (int p; u; u = p, v = pre[p])
            p = mate[v], mate[mate[u] = v] = u;
    }
    void init(int _n) {
        n = _n;
        vis = q = mate = col = fa = pre = he = vi(n + 1);
    }
    int lca(int u, int v) {
        for (cnt++;; u = pre[mate[u]]) {
            if (v) swap(u, v);
            if (vis[u = get(u)] == cnt) return u;
            vis[u] = cnt;
        }
    }
    void blo(int u, int v, int f) {
        for (int p; get(u) != f; v = p, u = pre[p]) {
            p = mate[u]; pre[u] = v; fa[u] = fa[p] = f;
            if (col[p] != 1) col[q[++t] = p] = 1;
        }
    }
    bool bfs(int u) {
        FOR (i, 1, n + 1) col[i] = 0, fa[i] = i;
        h = 0; q[t = 1] = u; col[u] = 1;
        while (h != t) {
            int x = q[++h];
            for (int i = he[x]; i; i = edges[i].f) {
                int y = edges[i].s;
                if (!col[y]) {
                    if (!mate[y]) { aug(y, x); return 1; }
                    pre[y] = x; 
                    col[y] = 2; 
                    col[q[++t] = mate[y]] = 1;
                } else if (col[y] == 1 && get(x) != get(y)) {
                    int p = lca(x, y); 
                    blo(x, y, p); 
                    blo(y, x, p);
                }
            }
        }
        return 0;
    }
    int solve() {
        int ans = 0;
        FOR (i, 1, n + 1) if (!mate[i]) ans += bfs(i);
        return ans;
    }
};