#include "../../template.h"

namespace treap {
    __gnu_cxx::sfmt19937 mt((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
    using ptr = struct Node*;
    struct Node {
        ptr l, r;
        int pri, sz, k;
        Node(int k) : k(k), l(0), r(0), pri(mt()), sz(1) {}
    };

    inline int sz(ptr n) { return n ? n->sz : 0; }

    inline ptr pull(ptr n) {
        n->sz = sz(n->l) + 1 + sz(n->r);
        return n;
    }

    void split(ptr n, int k, ptr &lhs, ptr &rhs) {
        if (!n) { lhs = rhs = 0; return; }
        if (k <= n->k) split(n->l, k, lhs, n->l), rhs = pull(n);
        else split(n->r, k, n->r, rhs), lhs = pull(n);
    }

    ptr merge(ptr l, ptr r) {
        if (!l || !r) return max(l, r);
        if (l->pri > r->pri) return l->r = merge(l->r, r), pull(l);
        else return r->l = merge(l, r->l), pull(r);
    }

    int count_right(ptr n, int k) {
        if (!n) return 0;
        if (k <= n->k) return count_right(n->l, k) + 1 + sz(n->r);
        else return count_right(n->r, k);
    }

    int query(ptr n, int lo, int hi) { return count_right(n, lo) - count_right(n, hi); }

    void ins(ptr& n, ptr it) {
        if (!n) { n = it; return; }
        if (n->pri < it->pri) {
            ptr l, r;
            split(n, it->k, l, r);
            it->l = l, it->r = r, n = it;
        } else if (it->k <= n->k) ins(n->l, it);
        else ins(n->r, it);
        pull(n);
    }

    void del(ptr& n, int k) {
        if (!n) return;
        if (n->k == k) n = merge(n->l, n->r);
        else (k <= n->k ? del(n->l, k) : del(n->r, k)), pull(n);
    }
};

struct RangeDistinctQuery {
    struct SegTree {
        int n;
        vector<treap::ptr> seg;

        void init(int _n) {
            n = _n;
            seg.resize(2 * n);
        }

        int query(int l, int r, int lo, int hi) {
            int res = 0;
            for (l += n, r += n; l < r; l /= 2, r /= 2) {
                if (l & 1) res += treap::query(seg[l++], lo, hi);
                if (r & 1) res += treap::query(seg[--r], lo, hi);
            }
            return res;
        }

        void erase(int i, int j) {
            del(seg[i += n], j);
            while (i /= 2) del(seg[i], j);
        }

        void ins(int i, int j) {
            treap::ins(seg[i += n], new treap::Node(j));
            while (i /= 2) treap::ins(seg[i], new treap::Node(j));
        }
    };

    int n;
    vector<int> a;
    map<int, set<int>> locs;
    SegTree seg;

    void rem(int i) {
        auto &st = locs[a[i]];
        auto it = st.find(i);
        if (it != st.begin()) seg.erase(*prev(it), *it);
        if (next(it) != st.end()) seg.erase(*it, *next(it));
        if (it != st.begin() && next(it) != st.end()) seg.ins(*prev(it), *next(it));
        st.erase(it);
    }

    void add(int i, int x) {
        auto &st = locs[x];
        auto it = st.insert(i).first;
        if (it != st.begin() && next(it) != st.end()) seg.erase(*prev(it), *next(it));
        if (it != st.begin()) seg.ins(*prev(it), *it);
        if (next(it) != st.end()) seg.ins(*it, *next(it));
    }

    void upd(int i, int x) { rem(i); add(i, a[i] = x); }

    int query(int l, int r) { return r - l - seg.query(l, n, 0, r); }

    void init(vector<int> &_a) {
        a = _a;
        n = size(a);
        seg.init(n);
        for (int i = 0; i < n; i++) add(i, a[i]);
    }
};