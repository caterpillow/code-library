#include "../template.h"

int n;
vt<vt<ll>> adj;
vt<bool> done;
vt<vt<pl>> pars;
vt<int> sz;

int dfs_sz(int u, int p = -1) {
    sz[u] = 1;
    for (int v : adj[u]) {
				if (v == p || done[v]) continue;
        sz[u] += dfs_sz(v, u);
    }
    return sz[u];
}

int find_centroid(int u, int tsz, int p = -1) {
    for (int v : adj[u]) {
        if (v == p || done[v]) continue;
        if (sz[v] * 2 > tsz) return find_centroid(v, tsz, u);
    }
    return u;
}

// calculates {centroid, distance} pairs for each node
void process(int u, int r, int d, int par = -1) {
    pars[u].pb({r, d});
    for (int v : adj[u]) {
        if (v != par && !done[v]) process(v, r, d + 1, u);
    }
}

void decomp(int u = 0) {
    u = find_centroid(u, dfs_sz(u)); // keep in mind subtree sizes are not correct after this
    // do stuff
    process(u, u, 0);
    // end stuff
    done[u] = true;
    for (int v : adj[u]) {
        if (!done[v]) decomp(v);
    }
}