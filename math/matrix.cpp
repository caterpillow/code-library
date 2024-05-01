#include "../template.h"

const ll MOD = 1e9 + 7;
using Mat = vt<vt<ll>>;

Mat makeMat(int r, int c) { return Mat(r, vt<ll>(c)); }
Mat makeId(int n) { 
	Mat m = makeMat(n, n); F0R(i, n) m[i][i] = 1;
	return m;
}
Mat operator*(const Mat& a, const Mat& b) {
	int x = a.size(), y = a[0].size(), z = b[0].size(); 
	Mat c = makeMat(x, z);
	F0R(i, x) F0R(j, y) F0R(k, z) c[i][k] = (c[i][k] + a[i][j] * b[j][k]) % MOD;
	return c;
}
Mat& operator*=(Mat& a, const Mat& b) { return a = a * b; }
Mat pow(Mat m, ll p) {
	int n = m.size(); assert(n == m[0].size() && p >= 0);
	Mat res = makeId(n);
	for (; p; p /= 2, m *= m) if (p & 1) res *= m;
	return res;
}