#include "point.h"

// returns 4n edges that are guaranteed to contain an mst
// {distance, u, v}
vector<array<int, 3>> manhattan_mst(vector<P> ps) {
	vi id(size(ps));
	iota(all(id), 0);
	vector<array<int, 3>> edges;
    FOR (k, 4) {
		sort(all(id), [&] (int i, int j) {
		     return (ps[i] - ps[j]).x < (ps[j] - ps[i]).y;} );
		map<int, int> sweep;
		for (int i : id) {
			for (auto it = sweep.lower_bound(-ps[i].y);
                    it != sweep.end(); sweep.erase(it++)) {
				int j = it->second;
				P d = ps[i] - ps[j];
				if (d.y > d.x) break;
				edges.push_back({d.y + d.x, i, j});
			}
			sweep[-ps[i].y] = i;
		}
		for (P& p : ps) if (k & 1) p.x = -p.x; else swap(p.x, p.y);
	}
	return edges;
}