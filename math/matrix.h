#include "../template.h"

const ll MOD = 1e9 + 7;
using Mat = vt<vt<ll>>;

Mat makeMat(int r, int c) { return Mat(r, vt<ll>(c)); }
Mat makeId(int n) { 
	Mat m = makeMat(n, n); FOR(i, n) m[i][i] = 1;
	return m;
}
Mat operator*(const Mat& a, const Mat& b) {
	int x = size(a), y = size(a[0]), z = size(b[0]); 
	Mat c = makeMat(x, z);
	FOR(i, x) FOR(j, y) FOR(k, z) c[i][k] = (c[i][k] + a[i][j] * b[j][k]) % MOD;
	return c;
}
Mat& operator*=(Mat& a, const Mat& b) { return a = a * b; }
Mat pow(Mat m, ll p) {
	int n = size(m); assert(n == size(m[0]) && p >= 0);
	Mat res = makeId(n);
	for (; p; p /= 2, m *= m) if (p & 1) res *= m;
	return res;
}