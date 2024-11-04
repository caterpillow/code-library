#include "../../template.h"

template<class T> struct SegTree {
    T ID;
    int n; 
    vt<T> seg;
    void init(int _n, T _ID) {
        ID = _ID;
        for (n = 1; n < _n; n *= 2);
        seg.assign(2 * n, ID);
    }
    void upd(int i, T val) {
        seg[i += n] = val;
        while (i /= 2) seg[i] = seg[2 * i] + seg[2 * i + 1];
    }
    T query(int l, int r) { // inc exc
        T a = ID, b = ID;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) a = a + seg[l++];
            if (r & 1) b = seg[--r] + b;
        }
        return a + b;
    }
    T& operator[](int i) {
        return seg[i + n];
    }
};