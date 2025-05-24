#include "../template.h"

int n, m;
vector<vector<pair<int, int>>> adj;
vector<int> ret, used;

// for edges, print the edge u came from instead of current node
void dfs(int u) {
    while (size(adj[u])) {
        auto [v, ei] = adj[u].back();
        adj[u].pop_back();
        if (used[ei]++) continue;
        dfs(v);
    }
    ret.push_back(u);
}