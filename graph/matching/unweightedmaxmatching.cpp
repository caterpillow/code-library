#include "../template.h"

random_device rd;
mt19937 rng(rd());

struct MCM {
    int n, t = 0;
    vt<vt<int>> adj;
    vt<int> mt, us;

    void init(int _n) {
        n = _n;
        adj.resize(n);
        mt.resize(n + 1, n);
        us.resize(n + 1);
    }

    int dfs(int u) {
        us[u] = t;
        shuffle(all(adj[u]), rng);
        for (int h : adj[u]) {
            int hm = mt[h];
            if (us[hm] != t) {
                mt[u] = h, mt[h] = u, mt[hm] = n;
                if (hm == n || dfs(hm)) return 1;
                mt[h] = hm, mt[hm] = h, mt[u] = n;
            }
        }
        return 0;
    }

    void ae(int x, int y) {
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    const int MAGIC = 10; // make bigger if wa
    vt<pi> calc() {
        int ans = 0;
        F0R (bad, MAGIC) {
            int was = ans;
            F0R (i, n) {
                if (mt[i] == n) t++, ans += dfs(i);
            }
            if (ans != was) bad = 0;
        }
        vt<pi> out;
        F0R (i, n) {
            if (mt[i] < i) out.pb({mt[i], i});
        }
        return out;
    }
};