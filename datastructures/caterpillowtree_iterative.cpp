#include "../template.h"

/*

parent of i is (i - 1) / 64
the j'th child of i is i * 64 + 1 + j (0 indexed)

*/


const ll sz = 1 << 18;
const ll mxv = 2e6;
struct CaterpillowTree {
    int freq[mxv];
    ll tree[(sz - 1) / 63];
    
    CaterpillowTree() { 
        memset(freq, 0, sizeof(freq)); 
        memset(tree, 0, sizeof(tree));
    }

    void toggle(int x) {
        int i = (x >> 6) + ((sz >> 6) - 1) / 63;
        tree[i] ^= 1ll << (x & 63);
        do {
            x >>= 6;
            int p = (i - 1) >> 6;
            if ((1ll & (tree[p] >> (x & 63))) ^ (!!tree[i])) tree[p] ^= 1ll << (x & 63);
            i = p;
        } while (i);
    }

    int find_min() {
        ll r = sz, ans = 0;
        int i = 0;
        while (r != 1) {
            r >>= 6;
            int j = __builtin_ctzl(tree[i]);
            ans += j * r;
            i = (i << 6) + 1 + j;
        }
        return ans;
    }
    
    void insert(int x) { if (++freq[x] == 1) toggle(x); }
    void erase(int x) { if (--freq[x] == 0) toggle(x); }
};