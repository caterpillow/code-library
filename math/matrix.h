#include "../template.h"

using mat = vt<vt<ll>>;

mat make_mat(int r, int c) { return mat(r, vt<ll>(c)); }
mat make_id(int n) { 
    mat m = make_mat(n, n); FOR(i, n) m[i][i] = 1;
    return m;
}
mat operator*(const mat& a, const mat& b) {
    int x = size(a), y = size(a[0]), z = size(b[0]); 
    mat c = make_mat(x, z);
    FOR(i, x) FOR(j, y) FOR(k, z) 
        c[i][k] = (c[i][k] + a[i][j] * b[j][k]) % mod;
    return c;
}
mat& operator*=(mat& a, const mat& b) { return a = a * b; }
mat pow(mat m, ll p) {
    int n = size(m); assert(n == size(m[0]) && p >= 0);
    mat res = make_id(n);
    for (; p; p /= 2, m *= m) if (p & 1) res *= m;
    return res;
}