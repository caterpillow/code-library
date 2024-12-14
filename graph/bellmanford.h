#include "../template.h"

struct BellmanFord {
    int n;
    vt<pair<pl, int>> edges;
    vt<ll> dist;
    void ae(int u, int v, int w) { 
        edges.pb({{u, v}, w}); 
    }
    // returns if there is a negative cycle
    void init(int _n) {
        n = _n;
        n = _n; 
        dist.resize(n, INF);
    }
    bool gen(int s = 0) {
        dist[s] = 0;
        FOR (i, n) {
            for (auto& a : edges) {
                if (dist[a.f.f] < INF) {
                    dist[a.f.s] = min(dist[a.f.s], dist[a.f.f] + a.s);
                }
            }
        }
        for (auto& a : edges) {
            if (dist[a.f.f] < INF && dist[a.f.s] > dist[a.f.f] + a.s) {
                return true;
            }
        }
        return false;
    }
};