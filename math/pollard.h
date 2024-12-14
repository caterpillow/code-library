#include "../template.h"

using ul = unsigned long long;

ul mod_mul(ul a, ul b, const ul mod) {
	ll ret = a * b - mod * (ul) ((db) a * b / mod);
	return ret + ((ret < 0) - (ret >= (ll) mod)) * mod; 
}
ul mod_pow(ul a, ul b, const ul mod) {
	if (b == 0) return 1;
	ul res = mod_pow(a, b / 2, mod); 
    res = mod_mul(res, res, mod);
	return b & 1 ? mod_mul(res, a,mod) : res;
}
 
bool prime(ul n) { // not ll!
	if (n < 2 || n % 6 % 4 != 1) return n - 2 < 2;
	ul A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n - 1), d = n >> s;
	for (auto a : A) {   // ^ count trailing zeroes
		ul p = mod_pow(a, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--) p = mod_mul(p, p, n);
		if (p != n - 1 && i != s) return 0;
	}
	return 1;
}
 
ul pollard(ul n) { // return some nontrivial factor of n
    if (n % 2 == 0) return 2;
	auto f = [n](ul x) { return mod_mul(x, x, n) + 1; };
	ul x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || gcd(prd, n) == 1) { /// speedup: don't take gcd every it
		if (x == y) x = ++i, y = f(x);
		if ((q = mod_mul(prd, max(x,y) - min(x, y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return gcd(prd, n);
}

void factor_rec(ul n, map<ul, int>& cnt) {
	if (n == 1) return;
	if (prime(n)) { ++cnt[n]; return; }
	ul u = pollard(n);
	factor_rec(u, cnt), factor_rec(n / u,cnt);
}