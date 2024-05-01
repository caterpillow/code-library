#include "../template.h"

struct DSU {
    vt<int> e; 
    void init(int n) { 
        e.resize(n, -1);
    }
    int find(int x) { 
        return e[x] < 0 ? x : e[x] = find(e[x]); 
    }   
    bool unite(int x, int y) {
        x = find(x), y = find(y); 
        if (x == y) return 0;
        if (e[x] > e[y]) swap(x,y);
        e[x] += e[y]; 
        e[y] = x; 
        return 1;
    }
    // optional
    bool sameSet(int a, int b) { 
        return find(a) == find(b); 
    }
    int size(int x) { 
        return -e[find(x)]; 
    }
};