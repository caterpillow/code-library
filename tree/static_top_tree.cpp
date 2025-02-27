#include "../../template.h"

struct Path { };
struct Child { };

// merge path clusters a and b, with b being closer to the root
Path merge_paths(const Path& a, const Path& b) {
    return {};
}

// attach child cluster b to unit path cluster a
Path attach_child(const Path& a, const Child& b) {
    return {};
}

Child merge_children(const Child& a, const Child& b) {
    return {};
}

Child make_child(const Path& a) {
    return {};
}

enum Type { MakeVertex, MergePaths, AttachChild, MergeChildren, MakeChild };

struct StaticTopTree {
    int n;
    vector<vector<int>> adj;
    int root, stt_root;
    vector<int> par, lc, rc;
    vector<Type> type;
    int nxt;

    vector<Path> path;
    vector<Child> child;
    function<Path(int)> make_vertex;

    void init(int _n, vector<vector<int>>& _adj, function<Path(int)> _make_vertex, int _root = 0) {
        n = _n;
        adj = _adj;
        make_vertex = _make_vertex;
        root = _root;
        type.resize(4 * n);
        par = lc = rc = vector<int>(4 * n, -1);
        path.resize(4 * n);
        child.resize(4 * n);
        nxt = n;
        build_stt();
        build(stt_root);
    }

    void build(int u = -2) {
        if (u == -1) return;
        build(lc[u]);
        build(rc[u]);
        pull(u);
    }

    void update(int u) {
        while (u != -1) pull(u), u = par[u];
    }

    Path query() {
        return path[stt_root];
    }

    Path query(int u) {
        Path res = path[u];
        while (true) {
            int p = par[u];
            if (p == -1 || type[p] != MergePaths) break;
            if (rc[p] == u) res = merge_paths(path[lc[p]], res);
            u = p;
        }
        return res;
    }

    void print_stt(int u = -2) {
        if (u == -2) {
            u = stt_root;
            for (int i = 0; i <= stt_root; i++) {
                cerr << i << ": ";
                switch (type[i]) {
                    case MakeVertex:
                        cerr << "MakeVertex";
                    break;
                    case MergePaths:
                        cerr << "MergePaths";
                    break;
                    case AttachChild:
                        cerr << "AttachChild";
                    break;
                    case MergeChildren:
                        cerr << "MergeChildren";
                    break;
                    case MakeChild:
                        cerr << "MakeChild";
                    break;
                }
                cerr << endl;
            }
        }
        if (u == -1) return;
        print_stt(lc[u]);
        print_stt(rc[u]);
        if (~lc[u]) cerr << lc[u] << " " << u << endl;
        if (~rc[u]) cerr << rc[u] << " " << u << endl;
    }

    private:
    int dfs(int u) {
        int sz = 1, mx = 0;
        for (int& v : adj[u]) {
            adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
            int res = dfs(v);
            sz += res;
            if (res > mx) mx = res, swap(v, adj[u][0]);
        }
        return sz;
    }

    int add(int u, int l, int r, Type t) {
        if (u == -1) u = nxt++;
        par[u] = -1, lc[u] = l, rc[u] = r, type[u] = t;
        if (l != -1) par[l] = u;
        if (r != -1) par[r] = u;
        return u;
    }

    pair<int, int> merge(const vector<pair<int, int>>& nodes, Type t) {
        if (size(nodes) == 1) return nodes[0];
        int totsz = 0;
        for (auto& [_, sz] : nodes) totsz += sz;
        vector<pair<int, int>> lhs, rhs;
        for (auto& [i, sz] : nodes) (totsz > sz ? lhs : rhs).emplace_back(i, sz), totsz -= sz * 2;
        auto [l, szl] = merge(lhs, t);
        auto [r, szr] = merge(rhs, t);
        return {add(-1, l, r, t), szl + szr};
    }

    pair<int, int> _merge_path(int u) {
        vector<pair<int, int>> nodes {_attach_child(u)};
        while (!adj[u].empty()) nodes.push_back(_attach_child(u = adj[u][0]));
        reverse(nodes.begin(), nodes.end());
        return merge(nodes, Type::MergePaths);
    }

    pair<int, int> _merge_children(int u) {
        vector<pair<int, int>> nodes;
        for (int j = 1; j < size(adj[u]); j++) nodes.push_back(_make_child(adj[u][j]));
        return nodes.empty() ? make_pair(-1, 0) : merge(nodes, Type::MergeChildren);
    }

    pair<int, int> _make_child(int u) {
        auto [v, szv] = _merge_path(u);
        return {add(-1, v, -1, Type::MakeChild), szv};
    }

    pair<int, int> _attach_child(int u) {
        auto [v, szv] = _merge_children(u);
        return {add(u, -1, v, v == -1 ? Type::MakeVertex : Type::AttachChild), szv + 1};
    }

    void pull(int u) {
        switch (type[u]) {
            case MakeVertex:
                path[u] = make_vertex(u);
            break;
            case MergePaths:
                path[u] = merge_paths(path[lc[u]], path[rc[u]]);
            break;
            case AttachChild:
                path[u] = attach_child(make_vertex(u), child[rc[u]]);
            break;
            case MergeChildren:
                child[u] = merge_children(child[lc[u]], child[rc[u]]);
            break;
            case MakeChild:
                child[u] = make_child(path[lc[u]]);
            break;
        }
    }

    void build_stt() {
        dfs(root);
        auto [i, n] = _merge_path(root);
        stt_root = i;
    }
};