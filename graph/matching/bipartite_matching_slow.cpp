#include "../../template.h"

int a, b; // # of nodes on left/right side respectively
vt<vt<int>> adj;
// add directed edges from lhs to rhs
 
vt<int> matched;
vt<bool> seen;
 
int dfs(int cur) {
    if (seen[cur]) return false; 
    seen[cur] = true;
    for (int nxt : adj[cur]){
        if (matched[nxt] == -1 || dfs(matched[nxt])) {
            matched[nxt] = cur;
            return true;
        }
    }
    return false;
}
 
int solve() {
    int flow = 0;
    matched.assign(b, -1);
    F0R (i, a){
        seen.assign(a, false);
        flow += dfs(i);
    }
    return flow;
}