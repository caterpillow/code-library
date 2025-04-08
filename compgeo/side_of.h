#include "onsegment.h"

// returns 1/0/-1 if l/on/r when looking from s to e
// eps is the tolerance for collinearity
template<class P>
int side_of(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int side_of(const P& s, const P& e, const P& p, double eps) {
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist() * eps;
    return (a > l) - (a < -l);
}