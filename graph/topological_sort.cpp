#include "../template.h"

int n;
vt<bool> seen;
vt<int> top;

void dfs(int u) {
    if (seen[u]) return;
    seen[u] = true;
    for (int v : adj[u]) dfs(v);
    top.pb(u);
}

void topsort() {
    seen.assign(n, 0);
    FOR (u, n) dfs(u);
    reverse(all(top)); // reverse to make edges point to the right
}