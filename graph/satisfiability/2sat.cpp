#include "../../template.h"

struct SCC {
    ll n; 
    vt<vt<ll>> adj, radj;
    vt<ll> todo, comp, comps; 
    vt<bool> seen;
    void init(ll _n) { 
        n = _n; 
        adj.resize(n);
        radj.resize(n);
        comp = vt<ll>(n, -1);
        seen.resize(n); 
    }
    void ae(ll x, ll y) { adj[x].pb(y), radj[y].pb(x); }
    void dfs(ll x) {
        seen[x] = 1; 
        for(ll y : adj[x]) if (!seen[y]) dfs(y);
        todo.pb(x); 
    }
    void dfs2(ll x, ll v) {
        comp[x] = v; 
        for (ll y : radj[x]) if (comp[y] == -1) dfs2(y, v); 
    }
    void gen() {
        F0R (i, n) if (!seen[i]) dfs(i);
        reverse(all(todo)); 
        for (ll x : todo) if (comp[x] == -1) dfs2(x, x), comps.pb(x);
    }
};

using pi = pair<int, int>;

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
	void implies(int x, int y) { either(~x, y); } // x -> y
	void force(int x) { either(x, x); } // x = true
    void exactly_one(int x, int y) { either(x, y), either(~x, ~y); } // xor
    void tie(int x, int y) { implies(x, y), implies(~x, ~y); } // x and y have the same value
    void nand(int x, int y ) { either(~x, ~y); } // x and y are not both true
	void at_most_one(const vt<int>& li) { // at most one of li is true
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
        F0R (i, n) ans[i] = tmp[scc.comp[2 * i]] == 1;
		return ans;
	}
};