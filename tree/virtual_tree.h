#include "../template.h"

// pos is dfs time
vt<pl> virtual_tree(vt<ll>& nodes) { // pairs of {ancestor, child}
    auto cmp = [&] (ll u, ll v) { return pos[u] < pos[v]; };
    sort(all(nodes), cmp);
    int sz = size(nodes);
    FOR (i, sz - 1) nodes.pb(lca(nodes[i], nodes[i + 1]));
    sort(all(nodes), cmp);
    nodes.erase(unique(all(nodes)), nodes.end());
    vt<pl> res;
    FOR (i, (int) size(nodes) - 1) res.pb({lca(nodes[i], nodes[i + 1]), nodes[i + 1]});
    return res;
}