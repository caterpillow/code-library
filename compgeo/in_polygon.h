#include "onsegment.h"

template<class P>
bool in_polygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = sz(p);
	FOR (i, n) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}