#include "point.h"

// use segDist for floats
template<class P> bool on_segment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}