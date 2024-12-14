#include "../template.h"

void apsp(vt<vt<ll>> &m) {
    int n = size(m);
    FOR (i, n) m[i][i] = min(m[i][i], 0ll);
    FOR (k, n) FOR(i, n) FOR(j, n)
        if (m[i][k] != INF && m[k][j] != INF) {
            auto newDist = max(m[i][k] + m[k][j], -INF);
            m[i][j] = min(m[i][j], newDist);
        }
    FOR (k, n) if (m[k][k] < 0) FOR (i, n) FOR(j, n)
        if (m[i][k] != INF && m[k][j] != INF) m[i][j] = -INF;
}

// for validated input (no neg cycles, etc, m[i][i] = 0)
void apsp(vt<vt<ll>>& m) {
    FOR (k, n) FOR (i, n) FOR (j, n) m[i][j] = min(m[i][j], m[i][k] + m[k][j]);
}