#include "../template.h"

ll solve(int n, vt<vt<ll>>& cost) {
    vt<vt<ll>> dp(1 << n, vt<ll>(n, INF));

    // initialise starting states
    FOR (i, n) {
        dp[1 << i][i] = 0;
    }

    // iterative dp
    FOR (i, 1 << n) {
        FOR (j, n) {
            if (dp[i][j] == INF) continue; // skip infinity
            FOR (k, n) {
                if (i & (1 << k)) continue; // skip things already in bitmask
                dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + cost[j][k]); // push dp values
            }
        }
    }

    // find minimum of all complete walks
    ll ans = INF;
    FOR (i, n) {
        ans = min(ans, dp[(1 << n) - 1][i]);
    }
}