#include "../template.h"

const ll MOD = 1e9 + 7;

ll power(ll x, ll y) { // make y unsigned long long if large numbers
    ll res = 1;
    x %= MOD;
    while (y) {
        if (y & 1) res = (res * x) % MOD;
        y /= 2;
        x = (x * x) % MOD;
    }
    return res;
}

// just use __gcd if available
ll gcd(ll a, ll b){
		if (!a) return b;
	  return gcd(b % a, a);
}

// finds two integers x and y, such that ax + by = gcd(a, b)
ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a / b * x, d;
}

