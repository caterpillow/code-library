#include "../template.h"

// skip the stuff that starts with r if you dont care about reverse functions
struct H {
    ull x; H(ull x = 0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t) x * o.x;
        return H((ull) m) + (ull)(m >> 64); }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};

static const H C = (ll) 1e11 + 3; // (order ~ 3e9; random also ok)

struct HashInterval {
    vector<H> ha, pw, rha; 
    template<class T>
    HashInterval(T& str) : ha(size(str) + 1), pw(ha), rha(ha) {
        pw[0] = 1;
        FOR (i, size(str)) {
            ha[i + 1] = ha[i] * C + str[i] + 1;
            pw[i + 1] = pw[i] * C;
        }
        ROF (i, size(str)) rha[i] = rha[i + 1] * C + str[i] + 1;
    }
    H hash_interval(int a, int b) { // hash [a, b)
        return ha[b] - ha[a] * pw[b - a];
    }
    H rhash_interval(int a, int b) { // hash [a, b) but from right to left
        return rha[a] - rha[b] * pw[b - a];
    }
};

// get all hashes of length <len>
template<class T>
vector<H> get_hashes(T& str, int length) {
    if (size(str) < length) return {};
    H h = 0, pw = 1;
    FOR (i, length) h = h * C + str[i] + 1, pw = pw * C;
    vector<H> ret = {h};
    FOR (i, length, size(str)) {
        ret.push_back(h = h * C + str[i] + 1 - pw * (str[i - length] + 1));
    }
    return ret;
}

template<class T>
H hash_string(T& s) { H h = 1; for (auto c : s) h = h * C + c + 1; return h; }