#include "sideof.h"

// returns whether point is in a convex hull (ccw, no collinear pts)
using P = Point<ll>;
bool in_hull(const vector<P>& l, P p, bool strict = true) {
    int a = 1, b = size(l) - 1, r = !strict;
    if (size(l) < 3) return r && on_segment(l[0], l.back(), p);
    if (side_of(l[0], l[a], l[b]) > 0) swap(a, b);
    if (side_of(l[0], l[a], p) >= r || side_of(l[0], l[b], p) <= -r)
        return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (side_of(l[0], l[c], p) > 0 ? b : a) = c;
    }
    return sgn(l[a].cross(l[b], p)) < r;
}