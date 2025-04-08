#include "../../template.h"

struct DSU {
    vt<int> e; 
    void init(int n) { 
        e.resize(n, -1);
    }
    int operator[](int x) { 
        return e[x] < 0 ? x : e[x] = (*this)[e[x]]; 
    }   
    bool operator()(int x, int y) {
        x = (*this)[x], y = (*this)[y]; 
        if (x == y) return 0;
        if (e[x] > e[y]) swap(x,y);
        e[x] += e[y]; 
        e[y] = x; 
        return 1;
    }
    // optional
    bool same_set(int a, int b) { 
        return (*this)[a] == (*this)[b]; 
    }
    int sz(int x) { return -e[(*this)[x]]; }
    int add() { e.pb(-1); return size(e) - 1; }
};