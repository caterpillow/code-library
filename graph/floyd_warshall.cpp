#include "../template.h"

void apsp(vt<vt<ll>> &m) {
    int n = m.size();
    F0R (i, n) m[i][i] = min(m[i][i], 0ll);
    F0R (k, n) F0R(i, n) F0R(j, n)
        if (m[i][k] != INF && m[k][j] != INF) {
            auto newDist = max(m[i][k] + m[k][j], -INF);
            m[i][j] = min(m[i][j], newDist);
        }
    F0R (k, n) if (m[k][k] < 0) F0R (i, n) F0R(j, n)
        if (m[i][k] != INF && m[k][j] != INF) m[i][j] = -INF;
}

// for validated input (no neg cycles, etc, m[i][i] = 0)
void apsp(vt<vt<ll>>& m) {
    F0R(k, n) F0R(i, n) F0R(j, n) m[i][j] = min(m[i][j], m[i][k] + m[k][j]);
}