#include "../../template.h"

using K = ll; // key type
random_device rd;
mt19937 mt(rd());

ll ID = INF;
ll cmb(ll a, ll b) {
    return min(a, b);
}

using ptr = struct Node*;
struct Node {
	K key;
	int pri;
    ptr l, r;
	int sz; 

	// custom
	ll val;
	ll agg;

	Node(K _key, ll _val) {
        pri = mt(); 
        sz = 1; 
        l = r = nullptr;
        val = agg = _val;
        key = _key;
	}

	~Node() { 
        delete l;
        delete r;
	}
};

int sz(ptr n) { return n ? n->sz : 0; }
ll val(ptr n) { return n ? n->val : ID; }
ll agg(ptr n) { return n ? n->agg : ID; }

ptr pull(ptr n) {
    ptr a = n->l, b = n->r;
    n->sz = sz(a) + 1 + sz(b);
    n->agg = cmb(agg(a), cmb(n->val, agg(b)));
    return n;
}

pair<ptr, ptr> split(ptr n, K k) { // splits before k
	if (!n) return {n, n};
    if (k <= n->key) {
        auto [l, r] = split(n->l, k); 
        n->l = r;
        return {l, pull(n)};
	} else {
		auto [l, r] = split(n->r, k); 
    	n->r = l;
		return {pull(n), r};
	}
}

pair<ptr, ptr> spliti(ptr n, int i) { // splits before i
	if (!n) return {n, n};
    if (i <= sz(n->l)) {
        auto [l, r] = spliti(n->l, i); 
        n->l = r;
        return {l, pull(n)};
    } else {
		auto [l, r] = spliti(n->r, i - sz(n->l) - 1); 
        n->r = l;
		return {pull(n), r};
	}
}

ptr merge(ptr l, ptr r) { //  keys in l < keys in r
	if (!l || !r) return l ? l : r;
	ptr t;
	if (l->pri > r->pri) l->r = merge(l->r, r), t = l;
	else r->l = merge(l, r->l), t = r;
	return pull(t);
}

ptr ins(ptr n, K k, ll val) { // insert k 
	auto [l, r] = split(n, k);
	return merge(l, merge(new Node(k, val), r));
}

ptr insi(ptr n, int i, K k, ll val) { // insert before i	
	auto [l, r] = spliti(n, i);
	return merge(l, merge(new Node(k, val), r));
}

ptr del(ptr n, K k) { // delete k 
	auto a = split(n, k), b = spliti(a.s, 1);
	return merge(a.f, b.s);
}

ptr deli(ptr n, int i) {
	auto b = spliti(n, i + 1), a = spliti(b.f, i);
	return merge(a.f, b.s);
}

ptr find(ptr n, K k) {
	if (!n || n->key == k) return n;
	if (n->key < k) return find(n->l, k);
	else return find(n->r, k);
}

ptr findi(ptr n, int i) {
    if (!n || n->sz == i) return n;
    if (i < sz(n->l)) return find(n->l, i);
    else return find(n->r, i - sz(n->l) - 1);
}

ll query(ptr &n, K lo, K hi) {
	auto [lm, r] = split(n, hi + 1); // only works for integer key types 
	auto [l, m] = split(lm, lo);
	ll res = agg(m);
	n = merge(l, merge(m, r));
	return res;
}

ll queryi(ptr &n, int lo, int hi) {
    auto [lm, r] = spliti(n, hi + 1);
    auto [l, m] = spliti(lm, lo);
    ll res = agg(m);
    n = merge(l, merge(m, r));
    return res;
}

void upd(ptr& n, K k, ll nv) { // assumes no duplicate keys
    auto [l, mr] = split(n, k);
    auto [m, r] = split(mr, k + 1);
    if (m) m->val = m->agg = nv;
    else m = new Node(k, nv);
    n = merge(l, merge(m, r));
}

void updi(ptr& n, int i, ll nv) {
    auto [l, mr] = spliti(n, i);
    auto [m, r] = spliti(n, 1);
    assert(m);
    m->val = m->agg = nv;
    n = merge(l, merge(m, r));
}

int mn(ptr n) {
    if (n->l) return mn(n->l);
    else return n->key;
}

int mx(ptr n) {
    if (n->r) return mx(n->r);
    else return n->key;
}

int ord(ptr n, int k) { // 0-index of k if it was inserted
    if (!n) return 0;
    else if (n->key >= k) return ord(n->l, k); // k is on the left
    else return ord(n->r, k) + sz(n->l) + 1; // k is on the right
}

ptr unite(ptr l, ptr r) {
    if (!l || !r) return l ? l : r;
    // l has the smallest key
    if (mn(l) > mn(r)) swap(l, r);
    ptr res = 0;
    while (r) {
        auto [lt, rt] = split(l, mn(r) + 1);
        res = merge(res, lt);
        tie(l, r) = make_pair(r, rt);
    }   
    return merge(res, l);
}

// doesnt have the amortized complexity of the other union, 
// but is fast in practice for general unions
ptr unite_fast(ptr l, ptr r) {
    if (!l || !r) return l ? l : r;
    if (l->pri < r->pri) swap(l, r);
    auto [lhs, rhs] = split(r, l->key);
    l->l = unite(l->l, lhs);
    l->r = unite(l->r, rhs);
    return pull(l);
}

void heapify(ptr n) {
	if (!n) return;
	ptr mx = n;
	if (n->l && n->l->pri > mx->pri) mx = n->l;
	if (n->r && n->r->pri > mx->pri) mx = n->r;
	if (mx != n) swap(n->pri, mx->pri), heapify(mx);
}

ptr build(int l, int r, vt<ptr>& ns) {
	if (l > r) return nullptr;
	if (l == r) return ns[l];
	int m = (r + l) / 2;
	ns[m]->l = build(l, m - 1, ns);
	ns[m]->r = build(m + 1, r, ns);
	heapify(ns[m]);
	return pull(ns[m]);
}

Node* tree;