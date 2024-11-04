#include "../../template.h"

template<class T> struct RMQ {
    #define func min
    vt<vt<T>> dp;
    void init(const vt<T>& v) {
        dp.resize(32 - __builtin_clz(size(v)), vt<T>(size(v)));
        copy(all(v), begin(dp[0]));
        for (int j = 1; 1 << j <= size(v); ++j) {
            FOR (i, size(v) - (1 << j) + 1) dp[j][i] = func(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
        }
    }
    T query(int l, int r) {
        int d = 31 - __builtin_clz(r - l + 1);
        return func(dp[d][l], dp[d][r - (1 << d) + 1]); 
    }
    #undef func
};