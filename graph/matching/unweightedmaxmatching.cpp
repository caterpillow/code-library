#include "../../template.h"

random_device rd;
mt19937 rng(rd());

struct MCM {
    int n, t = 0;
    vt<vt<int>> adj;
    vt<int> mate, last_seen;

    void init(int _n) {
        n = _n;
        adj.resize(n);
        mate.resize(n + 1, n);
        last_seen.resize(n + 1);
    }

    int dfs(int u) {
        last_seen[u] = t;
        shuffle(all(adj[u]), rng);
        for (int v : adj[u]) {
            int m = mate[v];
            if (last_seen[m] != t) {
                mate[u] = v, mate[v] = u, mate[m] = n;
                if (m == n || dfs(m)) return 1;
                mate[v] = m, mate[m] = v, mate[u] = n;
            }
        }
        return 0;
    }

    void ae(int u, int v) {
        if (u == v) return;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    const int MAGIC = 1; // make bigger if wa
    vt<pi> calc() {
        F0R (bad, MAGIC) {
            int found = 0;
            F0R (u, n) if (mate[u] == n) t++, found |= dfs(u);
            if (found) bad = 0;
        }
        vt<pi> out;
        F0R (i, n) {
            if (mate[i] < i) out.pb({mate[i], i});
        }
        return out;
    }
};