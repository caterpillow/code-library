#include "../template.h"

using ull = unsigned long long;
const int depth = 3;
const int sz = 1 << (depth * 6);

struct Tree {
    vt<ull> seg[depth];
    
    Tree() {
        F0R (i, depth) seg[i].resize(1 << (6 * i));
    }

    void insert(int x) {
        ROF (d, 0, depth) {
            seg[d][x >> 6] |= 1ull << (x & 63);
            x >>= 6;
        }
    } 

    void erase(int x) {
        ull b = 0;
        ROF (d, 0, depth) {
            seg[d][x >> 6] &= ~(1ull << (x & 63));
            seg[d][x >> 6] |= b << (x & 63);
            x >>= 6;
            b = bool(seg[d][x]);
        }
    }

    int next(int x) {
        if (x >= sz) return sz;
        x = std::max(x, 0);
        int d = depth - 1;
        while (true) {
            if (ull m = seg[d][x >> 6] >> (x & 63)) {
                x += __builtin_ctzll(m);
                break;
            }
            x = (x >> 6) + 1;
            if (d == 0 || x >= (1 << (6 * d))) return sz;
            d--;
        }
        while (++d < depth) {
            x = (x << 6) + __builtin_ctzll(seg[d][x]);
        }
        return x;
    }

    int prev(int x) {
        if (x < 0) return -1;
        x = std::min(x, sz - 1);
        int d = depth - 1;
        while (true) {
            if (ull m = seg[d][x >> 6] << (63 - (x & 63))) {
                x -= __builtin_clzll(m);
                break;
            }
            x = (x >> 6) - 1;
            if (d == 0 || x == -1) return -1;
            d--;
        }
        while (++d < depth) {
            x = (x << 6) + 63 - __builtin_clzll(seg[d][x]);
        }
        return x;
    }

    int min() {
        if (empty()) return sz;
        int ans = 0;
        F0R (d, depth) {
            ans <<= 6;
            ans += __builtin_ctzll(seg[d][ans >> 6]);
        }
        return ans;
    }

    int max() {
        if (empty()) return -1;
        int ans = 0;
        F0R (d, depth) {
            ans <<= 6;
            ans += 63 - __builtin_clzll(seg[d][ans >> 6]);
        }
        return ans;
    }

    inline bool empty() { return !seg[0][0]; }
    inline int operator[](int i) { return 1 & (seg[depth - 1][i >> 6] >> (i & 63)); }
};