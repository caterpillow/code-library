#include "../template.h"

// finds two integers x and y, such that ax + by = gcd(a, b)
ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a / b * x, d;
}

