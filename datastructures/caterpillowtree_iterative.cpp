#include "../template.h"

inline int child(int i, int j) { return (i << 6) + 1 + j; } // gets index of node i's jth child
inline int par(int i) { return (i - 1) >> 6; } // gets index of node i's parent
inline ll clear(ll x, int i) { return i < 64 ? x & ~((1ull << i) - 1) : 0; } // clear smallest i bits
inline ll rclear(ll x, int i) { return x & ((1ull << i) - 1); } // clear largest bits up to and including i
inline int bit(ll x, int i) { return 1ll & (x >> i); } // returns ith bit's state

const int sz = 1 << 18;
const int OFF = (sz / 64 - 1) / 63;

struct CaterpillowTree {
    int freq[sz];
    ll tree[(sz - 1) / 63];
    
    CaterpillowTree() { 
        memset(freq, 0, sizeof(freq)); 
        memset(tree, 0, sizeof(tree));
    }

    void toggle(int x) {
        int i = (x >> 6) + OFF;
        tree[i] ^= 1ll << (x & 63);
        do {
            x >>= 6;
            int p = par(i);
            if (bit(tree[p], x & 63) ^ !!tree[i]) tree[p] ^= 1ll << (x & 63);
            i = p;
        } while (i);
    }

    int min() {
        if (empty()) return -1;
        int r = sz >> 6, ans = 0, i = 0;
        while (r) {
            int j = __builtin_ctzll(tree[i]);
            ans += j * r;
            i = child(i, j);
            r >>= 6;
        }
        return ans;
    }

    int max() {
        if (empty()) return -1;
        int r = sz >> 6, ans = 0, i = 0;
        while (r) {
            int j = 63 - __builtin_clzll(tree[i]);
            ans += j * r;
            i = child(i, j);
            r >>= 6;
        }
        return ans;
    }

    int next(int x) {
        int i = (x >> 6) + OFF; // leaf index
        int r = 1; // range represented by each bit in tree[i]'s mask
        int ans = x;
        while (true) {
            if (clear(tree[i], (x & 63) + 1)) { // found larger number
                int j = __builtin_ctzll(clear(tree[i], (x & 63) + 1));
                ans += (j - (x & 63)) * r; 
                i = child(i, j);
                r >>= 6;
                break;
            }
            // go to parent
            if (!i) return -1;
            ans -= (x & 63) * r;
            x >>= 6;
            r <<= 6;
            i = par(i);
        };  
        while (r) { // run min
            int j = __builtin_ctzll(tree[i]);
            ans += j * r;
            i = child(i, j);
            r >>= 6;
        }
        return ans;
    }

    inline int lower_bound(int x) { return (*this)[x] ? x : next(x); }
    inline int upper_bound(int x) { return next(x); }

    int prev(int x) {
        int i = (x >> 6) + OFF; // leaf index
        int r = 1; // range represented by each bit in tree[i]'s mask
        int ans = x;
        while (true) {
            if (rclear(tree[i], x & 63)) { // found larger number
                int j = 63 - __builtin_clzll(rclear(tree[i], x & 63));
                ans += (j - (x & 63)) * r; 
                i = child(i, j);
                r >>= 6;
                break;
            }
            // go to parent
            if (!i) return -1;
            ans -= (x & 63) * r;
            x >>= 6;
            r <<= 6;
            i = par(i);
        };  
        while (r) { // run max
            int j = 63 - __builtin_clzll(tree[i]);
            ans += j * r;
            i = child(i, j);
            r >>= 6;
        }
        return ans;
    }

    inline void insert(int x) { if (++freq[x] == 1) toggle(x); }
    inline void erase(int x) { if (freq[x] && --freq[x] == 0) toggle(x); }
    inline bool empty() { return !tree[0]; }
    inline int operator[](int i) { return bit(tree[(x >> 6) + OFF], x & 63); }
};