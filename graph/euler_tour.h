#include "../template.h"

// returns cycle/trail, empty vec if impossible
// degree is defined as sum of in + out edges
// circuit = all even deg, start anywhere
// trail: circuit, or 2 odd deg, start at odd deg
// returns vector of {node, edge_taken} (ret[0].s == -1)
// adj is {dest, edge_id} (undirected edges need same id)
// care m = 0
vpi euler_tour(vt<vt<pi>>& adj, int m, int src) {
	int n = size(adj);
    vpi ret, stk {{src, -1}};
	vi its(n), used(m), deg(n); // skip deg if def valid
	deg[src]++; // allows trails (comment for only cycles)
	while (size(stk)) {
		int u = stk.back().first;
		if (its[u] == size(adj[u])) { 
            ret.pb(stk.back()); 
            stk.pop_back(); 
            continue; 
        }
		auto [v, ei] = adj[u][its[u]++];
		if (used[ei]++) continue; // skip if def valid
        deg[u]--, deg[v]++; // skip if def valid
        stk.eb(v, ei);
    }
    // check valid
	for (int x : deg) 
        if (x < 0 || size(ret) != m + 1) 
            return {};
	return {ret.rbegin(), ret.rend()};
}