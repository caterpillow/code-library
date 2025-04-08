#include "../template.h"

// remember to add 0.5 before casting to int dumbass
typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
    int n = size(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);  // (^ 10% faster if double) (wtf does this mean?)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); 
        rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        FOR (i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vi rev(n);
    FOR (i, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    FOR (i, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) FOR (j, 0, k) {
            auto x = (double *) &rt[j + k], y = (double *) &a[i + j + k];
            C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
            a[i + j + k] = a[i + j] - z;
            a[i + j] += z;
        }
}

vd conv(const vd& a, const vd& b) {
    if (a.empty() || b.empty()) return {};
    vd res(size(a) + size(b) - 1);
    int L = 32 - __builtin_clz(size(res)), n = 1 << L;
    vector<C> in(n), out(n);
    copy(all(a), begin(in));
    FOR (i, size(b)) in[i].imag(b[i]);
    fft(in);
    for (C &x : in) x *= x;
    FOR (i, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    FOR (i, size(res)) res[i] = imag(out[i]) / (4 * n);
    return res;
}

// inputs [0, mod)
// N log_2(N) * mod < 8.6e14 (in practice 1e16+)
template<ll mod, class T> vt<T> convMod(const vt<T> &a, const vt<T> &b) {
    if (a.empty() || b.empty()) return {};
    vt<T> res(size(a) + size(b) - 1);
    int B = 32 - __builtin_clz(size(res)), n = 1 << B, cut = int(sqrt(mod));
    vector<C> L(n), R(n), outs(n), outl(n);
    FOR (i, size(a)) L[i] = C((int) a[i] / cut, (int) a[i] % cut);
    FOR (i, size(b)) R[i] = C((int) b[i] / cut, (int) b[i] % cut);
    fft(L), fft(R);
    FOR (i, n) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    FOR (i, size(res)) {
        ll av = ll(real(outl[i]) + 0.5), cv = ll(imag(outs[i]) + 0.5);
        ll bv = ll(imag(outl[i]) + 0.5) + ll(real(outs[i]) + 0.5);
        res[i] = ((av % mod * cut + bv) % mod * cut + cv) % mod;
    }
    return res;
}