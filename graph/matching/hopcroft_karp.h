#include "../../template.h"

// O(m sqrt(n)) bipartite matching
vpi max_matching(int l, int r, const vpi &edges) {
    vt<vi> adj = vt<vi>(l);
    vi nxt(l, -1),  prv(r, -1), lev, ptr;
    FOR (i, size(edges)) adj.at(edges[i].f).pb(edges[i].s);
    while (true) {
        lev = ptr = vi(l); 
        int max_lev = 0;
        queue<int> q; 
        FOR (i, l) if (nxt[i] == -1) lev[i] = 1, q.push(i);
        while (size(q)) {
            int x = q.ft; q.pop();
            for (int y : adj[x]) {
                int z = prv[y];
                if (z == -1) max_lev = lev[x];
                else if (!lev[z]) lev[z] = lev[x] + 1, q.push(z);
            }
            if (max_lev) break;
        }
        if (!max_lev) break;
        FOR (i, l) if (lev[i] > max_lev) lev[i] = 0;
        function<int(int)> dfs = [&] (int x) -> bool {
            for (; ptr[x] < size(adj[x]); ++ptr[x]) {
                int y = adj[x][ptr[x]], z = prv[y];
                if (z == -1 || (lev[z] == lev[x] + 1 && dfs(z))) 
                    return nxt[x] = y, prv[y] = x, ptr[x] = size(adj[x]), 1;
            }
            return 0;
        };
        FOR (i, l) if (nxt[i] == -1) dfs(i);
    }
    vpi ans; 
    FOR (i, l) if (nxt[i] != -1) ans.pb({i, nxt[i]});
    return ans;
}