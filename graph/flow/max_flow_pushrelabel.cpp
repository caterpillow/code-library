#include "../../template.h"

// O(VE sqrt E)

template<typename flow_t = long long>
struct PushRelabel {
    struct Edge {
        int to, rev;
        flow_t f, c;
    };
    vt<vt<Edge> > g;
    vt<flow_t> ec;
    vt<Edge*> cur;
    vt<vt<int> > hs;
    vt<int> h;

    void init(int n) {
        g.resize(n);
        ec.resize(n);
        cur.resize(n);
        hs.resize(2 * n);
        h.resize(n);
    }

    void ae(int s, int t, flow_t cap, flow_t rcap = 0) {
        if (s == t) return;
        Edge a = {t, size(g[t]), 0, cap};
        Edge b = {s, size(g[s]), 0, rcap};
        g[s].push_back(a);
        g[t].push_back(b);
    }
    void add_flow(Edge& e, flow_t f) {
        Edge &back = g[e.to][e.rev];
        if (!ec[e.to] && f)
            hs[h[e.to]].push_back(e.to);
        e.f += f; e.c -= f;
        ec[e.to] += f;
        back.f -= f; back.c += f;
        ec[back.to] -= f;
    }
    flow_t calc(int s, int t) {
        int v = size(g);
        h[s] = v;
        ec[t] = 1;
        vt<int> co(2 * v);
        co[0] = v - 1;
        for(int i=0;i<v;++i) cur[i] = g[i].data();
        for(auto &e:g[s]) add_flow(e, e.c);
        if(size(hs[0]))
        for (int hi = 0; hi>=0; ) {
            int u = hs[hi].back();
            hs[hi].pop_back();
            while (ec[u] > 0) // discharge u
                if (cur[u] == g[u].data() + size(g[u])) {
                    h[u] = 1e9;
                    for(auto &e : g[u])
                        if (e.c && h[u] > h[e.to] + 1)
                            h[u] = h[e.to] + 1, cur[u] = &e;
                    if (++co[h[u]], !--co[hi] && hi < v)
                        for (int i=0; i<v; ++i)
                            if (hi < h[i] && h[i] < v){
                                --co[h[i]];
                                h[i] = v + 1;
                            }
                    hi = h[u];
                } else if (cur[u]->c && h[u] == h[cur[u]->to] + 1)
                    add_flow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
            while (hi>=0 && hs[hi].empty()) --hi;
        }
        return -ec[s];
    }
    bool leftOfMinCut(int a) { return h[a] >= sz(g); }
};