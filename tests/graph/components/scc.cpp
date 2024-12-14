#include "../../../graph/components/strongly_connected_components.h"

SCC scc;

main() {
    IO::initO();
    ri(n, m);
    scc.init(n);
    rep(m) {
        ri(u, v);
        scc.ae(u, v);
    }
    scc.gen();
    println(size(scc.comps));
    vvi bruh(n);
    enum(i, par, scc.comp) bruh[par].pb(i);
    each(comp, scc.comps) {
        print(size(bruh[comp]));
        println(bruh[comp]);
    }
}

