#include "../../template.h"

template<class T> struct SegTree {
    T id;
    int n; 
    vector<T> seg;
    void init(int _n, T _id) {
        id = _id;
        for (n = 1; n < _n; n *= 2);
        seg.assign(2 * n, id);
    }
    void upd(int i, T val) {
        seg[i += n] = val;
        while (i /= 2) seg[i] = seg[2 * i] + seg[2 * i + 1];
    }
    T query(int l, int r) { 
        T a = id, b = id;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) a = a + seg[l++];
            if (r & 1) b = seg[--r] + b;
        }
        return a + b;
    }
    T& operator[](int i) {
        return seg[i + n];
    }
};