#include "../template.h"

ll reduce(vl& b, ll x) { 
    each(t, b) chmin(x, x ^ t);
	return x; 
}

bool add(vl& b, ll x) {
	if (!(x = reduce(b, x))) return 0;
	int ind = 0; 
    while (ind < size(b) && b[ind] > x) ind++;
	b.insert(begin(b) + ind, x); 
    return 1;
}