#include "../../template.h"

struct BIT {
    int n; vt<ll> arr;
    void init(int _n) {
        n = _n;
        arr.resize(n);
    }
    // 1-indexed
    ll sum(int r) {
        ll s = 0;
        while (r) {
            s += arr[r - 1];
            r -= r & -r;
        }
        return s;
    }
    // public
    void add(int p, ll x) {
        for (++p; p <= n; p += p & -p) arr[p - 1] += x;
    }
    ll sum(int l, int r) { // inc exc
        return sum(r) - sum(l);
    }
        // optional
    int lower_bound(ll sum) {
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            int npos = pos + pw;
            if (npos <= n && arr[npos - 1] < sum)
                pos = npos, sum -= arr[pos - 1];
        }
        return pos;
    }
};