#include "../template.h"

vt<int> pref(const string& s) {
	vt<int> p(size(s));
	FOR (i, 1, size(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g - 1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vt<int> match(const string& s, const string& pat) {
	vt<int> p = pref(pat + '\0' + s), res;
	FOR (i, size(p) - size(s), size(p))
		if (p[i] == size(pat)) res.pb(i - 2 * size(pat));
	return res;
}