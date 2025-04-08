#include "point.h"

// 2x signed area
// negative for counterclockwise
template<class T>
T polygon_area(vector<Point<T>>& v) {
    T a = v.back().cross(v[0]);
    FOR (i, size(v) - 1) a += v[i].cross(v[i + 1]);
    return a;
}