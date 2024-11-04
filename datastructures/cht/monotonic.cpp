#include "../../template.h"

// u can usually just get away with a / b
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down

struct Line {
    ll m, c;
 
    ll inter(Line& oth) {
        return (c - oth.c) / (oth.m - m);
    }
 
    ll operator()(ll x) {
        return x * m + c;
    }
};
 
struct CHT {
		// always draw out the hull on paper just to be safe
    deque<Line> hull;
 
    // dependent on query
    // compare new line with first, and first with second
    void add(Line l) {
        while (size(hull) >= 2 && hull[0].inter(l) <= hull[1].inter(hull[0])) hull.pop_front();
        hull.push_front(l);
    }
 
    ll query(ll x) {
        while (size(hull) >= 2 && hull.end()[-1](x) >= hull.end()[-2](x)) hull.pop_back();
        return hull.back()(x);
    }
};