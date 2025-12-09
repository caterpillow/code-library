struct DSU {
    int comps;
    vt<int> e, nxt; 
    void init(int n) { 
        e.assign(n, -1);
        nxt.assign(n, 0);
        FOR (i, n) nxt[i] = i;
        comps = n;
    }
    int operator[](int x) { 
        return e[x] < 0 ? x : e[x] = (*this)[e[x]]; 
    }   
    bool operator()(int x, int y) {
        x = (*this)[x], y = (*this)[y]; 
        if (x == y) return 0;
        if (e[x] > e[y]) swap(x,y);
        e[x] += e[y]; 
        e[y] = x; 
        comps--;
        swap(nxt[x], nxt[y]);
        return 1;
    }

    bool same_set(int a, int b) { return (*this)[a] == (*this)[b]; }
    int sz(int x) { return -e[(*this)[x]]; }
    int add() {
        nxt.pb(size(e));
        e.pb(-1); 
        return size(e) - 1; 
    }

    struct CompRange {
        const DSU* d;
        int start;

        struct It {
            const DSU* d;
            int start;
            int cur; 

            bool operator!=(const It& o) const { return cur != o.cur; }
            int operator*() const { return cur; }
            It& operator++() {
                cur = d->nxt[cur];
                if (cur == start) cur = -1; 
                return *this;
            }
        };

        It begin() const { return It{d, start, start}; }
        It end()   const { return It{d, start, -1}; }
    };

    CompRange iter(int x) const {
        int r = const_cast<DSU*>(this)->operator[](x); 
        return CompRange{this, r};
    }
};