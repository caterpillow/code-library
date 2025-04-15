#include "../template.h"

using ull = unsigned long long;
const int depth = 3;
const int sz = 1 << (depth * 6);

struct Tree {
    vt<ull> seg[depth];

    Tree() {
        FOR (i, depth) seg[i].resize(1 << (6 * i));
    }

    void insert(int x) {
        seg[2][x >> 6] |= 1ull << (x & 63);
        x >>= 6;
        seg[1][x >> 6] |= 1ull << (x & 63);
        x >>= 6;
        seg[0][x >> 6] |= 1ull << (x & 63);
    }

    void erase(int x) {
        ull b = 0;
        seg[2][x >> 6] &= ~(1ull << (x & 63));
        seg[2][x >> 6] |= b << (x & 63);
        x >>= 6;
        b = !!seg[2][x];
        seg[1][x >> 6] &= ~(1ull << (x & 63));
        seg[1][x >> 6] |= b << (x & 63);
        x >>= 6;
        b = !!seg[1][x];
        seg[0][x >> 6] &= ~(1ull << (x & 63));
        seg[0][x >> 6] |= b << (x & 63);
    }

    int next(int x) {
        if (x >= sz) return sz;
        if (ull m = seg[2][x >> 6] >> (x & 63)) return x + __builtin_ctzll(m);
        x = (x >> 6) + 1;
        if (x >= (1 << (12))) return sz;

        if (ull m = seg[1][x >> 6] >> (x & 63)) {
            x += __builtin_ctzll(m);
            return (x << 6) + __builtin_ctzll(seg[2][x]);
        }
        x = (x >> 6) + 1;
        if (x >= (1 << 6)) return sz;

        if (ull m = seg[0][x >> 6] >> (x & 63)) {
            x += __builtin_ctzll(m);
            x = (x << 6) + __builtin_ctzll(seg[1][x]);
            return (x << 6) + __builtin_ctzll(seg[2][x]);
        }
        return sz;
    }

    int prev(int x) {
        if (x < 0) return -1;

        if (ull m = seg[2][x >> 6] << (63 - (x & 63))) return x - __builtin_clzll(m);
        x = (x >> 6) - 1;
        if (x == -1) return -1;

        if (ull m = seg[1][x >> 6] << (63 - (x & 63))) {
            x -= __builtin_clzll(m);
            return (x << 6) + 63 - __builtin_clzll(seg[2][x]);
        }
        x = (x >> 6) - 1;
        if (x == -1) return -1;

        if (ull m = seg[0][x >> 6] << (63 - (x & 63))) {
            x -= __builtin_clzll(m);
            x = (x << 6) + 63 - __builtin_clzll(seg[1][x]);
            return (x << 6) + 63 - __builtin_clzll(seg[2][x]);
        }
        return -1;
    }
};