#include "../../template.h"

template<class T> struct RMQ {
    #define func min
    vector<vector<T>> dp;
    void init(const vector<T>& v) {
        dp.resize(32 - __builtin_clz(size(v)), vector<T>(size(v)));
        copy(v.begin(), v.end(), begin(dp[0]));
        for (int j = 1; 1 << j <= size(v); ++j) {
            for (int i = 0; i < size(v) - (1 << j) + 1; i++) 
                dp[j][i] = func(dp[j - 1][i], 
                    dp[j - 1][i + (1 << (j - 1))]);
        }
    }
    T query(int l, int r) {
        int d = 31 - __builtin_clz(r - l);
        return func(dp[d][l], dp[d][r - (1 << d)]); 
    }
    #undef func
};