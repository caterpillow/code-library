#include "../components/strongly_connected_components.h"

struct TwoSAT {
    int n = 0; 
    vt<pi> edges;
    void init(int _n) { n = _n; }
    int add() { return n++; }
    void either(int x, int y) { // x | y
        x = max(2 * x, -1 - 2 * x); // ~(2 * x)
        y = max(2 * y, -1 - 2 * y); // ~(2 * y)
        edges.pb({x, y}); 
    }
    // x -> y
    void implies(int x, int y) { either(~x, y); } 
    void force(int x) { either(x, x); } // x = true
    // xor
    void exactly_one(int x, int y) { 
        either(x, y), either(~x, ~y); 
    }
    // x and y have the same value
    void tie(int x, int y) { 
        implies(x, y), implies(~x, ~y); 
    } 
    // x and y are not both true
    void nand(int x, int y ) { either(~x, ~y); } 
    // at most one of li is true
    void at_most_one(const vt<int>& li) { 
        if (size(li) <= 1) return;
        int cur = ~li[0];
        FOR (i, 2, size(li)) {
            int next = add();
            either(cur, ~li[i]); 
            either(cur,next);
            either(~li[i], next); 
            cur = ~next;
        }
        either(cur, ~li[1]);
    }
    vt<bool> solve() {
        SCC scc; 
        scc.init(2 * n);
        for(auto& e : edges) {
            scc.ae(e.f ^ 1, e.s);
            scc.ae(e.s ^ 1, e.f);
        }
        scc.gen(); 
        reverse(all(scc.comps)); // reverse topo order
        for (int i = 0; i < 2 * n; i += 2) 
            if (scc.comp[i] == scc.comp[i ^ 1]) return {};
        vt<int> tmp(2 * n); 
        for (auto i : scc.comps) {
            if (!tmp[i]) tmp[i] = 1, tmp[scc.comp[i ^ 1]] = -1;
        }
        vt<bool> ans(n); 
        FOR (i, n) ans[i] = tmp[scc.comp[2 * i]] == 1;
        return ans;
    }
};