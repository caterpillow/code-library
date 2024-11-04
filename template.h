#include <bits/extc++.h>
#include <ext/random>

using namespace std;

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

const int precision = 24;
using db = long double;

template<class T> using vt = vector<T>;
using str = string;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;
using vi = vt<int>;
using vl = vt<ll>;
using vb = vt<bool>;
using vvi = vt<vt<int>>;
using vvl = vt<vt<ll>>;
using vvb = vt<vt<bool>>;
using vpi = vt<pi>;
using vpl = vt<pl>;

#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define bg(x) begin(x)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define size(x) ((int) (x).size())
#define sq(x) ((x) * (x))
#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#ifndef LOCAL
#define endl '\n'
#endif

#define lb lower_bound
#define ub upper_bound
template<class T> int lwb(vt<T>& a, const T& b) { return int(lb(all(a), b) - bg(a)); }
template<class T> int upb(vt<T>& a, const T& b) { return int(ub(all(a), b) - bg(a)); }
template<class T> void rem_dup(vt<T>& v) { sort(all(v)); v.erase(unique(all(v)), v.end()); }
#define cmp(exp) [&] (const auto& x, const auto& y) { return exp; }

#define __NARG__(...)  __NARG_I_(__VA_ARGS__,__RSEQ_N())
#define __NARG_I_(...) __ARG_N(__VA_ARGS__)
#define __ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define __RSEQ_N() 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define _VFUNC_(name, n) name##n
#define _VFUNC(name, n) _VFUNC_(name, n)
#define VFUNC(func, ...) _VFUNC(func, __NARG__(__VA_ARGS__)) (__VA_ARGS__)

#define FOR3(i, a, b) for (int i = (a); i < (b); i++)
#define FOR2(i, b) for (int i = 0; i < (b); i++)
#define ROF3(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define ROF2(i, b) for (int i = (b) - 1; i >= 0; i--)
#define rep(x) FOR (_, x)

#define each2(a, x) for (auto& a : x)
#define each3(a, b, x) for (auto& [a, b] : x)
#define each4(a, b, c, x) for (auto& [a, b, c] : x)

#define enum3(i, a, x) if (int i = 0; 1) for (auto it = begin(x); it != end(x); it++, i++) if (auto& a = *it; 1)
#define enum4(i, a, b, x) if (int i = 0; 1) for (auto it = begin(x); it != end(x); it++, i++) if (auto& [a, b] = *it; 1)
#define enum5(i, a, b, c, x) if (int i = 0; 1) for (auto it = begin(x); it != end(x); it++, i++) if (auto& [a, b, c] = *it; 1)

#define FOR(...) VFUNC(FOR, __VA_ARGS__)
#define ROF(...) VFUNC(ROF, __VA_ARGS__)
#define each(...) VFUNC(each, __VA_ARGS__)
#define enum(...) VFUNC(enum, __VA_ARGS__)

__gnu_cxx::sfmt19937 mt((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
const ll mod = 1e9 + 7;
ll mpow(ll x, ll y = mod - 2) {
    ll res = 1;
    for (; y; x = (x * x) % mod, y >>= 1) if (y & 1) res = (res * x) % mod;
    return res;
}
ll gen(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(mt); }

int rs, cs;
const int dr[5] {0, -1, 0, 1, 0}, dc[5] {1, 0, -1, 0, 0};
bool valid(int r, int c) { return r >= 0 && c >= 0 && r < rs && c < cs; }
vpi get_adj(int r, int c) {
    vpi ret(4);
    FOR (i, 4) ret[i] = {r + dr[i], c + dc[i]};
    return ret;
}
vpi get_valid_adj(int r, int c) {
    vpi ret;
    FOR (i, 4) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (valid(nr, nc)) ret.eb(nr, nc);
    }
    return ret;
}

constexpr int pct(int x) { return __builtin_popcount(x); }
constexpr int pct(ll x) { return __builtin_popcountll(x); }
constexpr int p2(int x) { return 1 << x; }
constexpr int msk2(int x) { return p2(x) - 1; }

ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); }
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }

namespace IO {
#ifndef LOCAL
    const int BSZ = 1 << 15;
    char ibuf[BSZ]; int ipos, ilen;
    char _next_char() {
        if (ipos == ilen) {
            ipos = 0;
            ilen = fread(ibuf, 1, BSZ, stdin);
            if (!ilen) return EOF;
        }
        return ibuf[ipos++];
    }
    char _nc() {
        char ch;
        while (isspace(ch = _next_char()));
        return ch;
    }
    void _rc(char& ch) {
        while (isspace(ch = _next_char()));
    }
    string _ns() {
        string x;
        char ch; while (isspace(ch = _next_char()));
        do { x += ch; } while (!isspace(ch = _next_char()) && ch != EOF);
        return x;
    }
    void _rs(string& x) {
        char ch; while (isspace(ch = _next_char()));
        do { x += ch; } while (!isspace(ch = _next_char()) && ch != EOF);
    }
    int _ni() {
        int x, sgn = 1;
        char ch;
        while (!isdigit(ch = _next_char())) if (ch == '-') sgn *= -1;
        x = ch - '0';
        while (isdigit(ch = _next_char())) x = x * 10 + (ch - '0');
        return x * sgn;
    }
    ll _nl() {
        ll x, sgn = 1;
        char ch;
        while (!isdigit(ch = _next_char())) if (ch == '-') sgn *= -1;
        x = ch - '0';
        while (isdigit(ch = _next_char())) x = x * 10 + (ch - '0');
        return x * sgn;
    }
    template<class T> void _ri(T& x) {
        char ch;
        int sgn = 1;
        while (!isdigit(ch = _next_char())) if (ch == '-') sgn *= -1;
        x = ch - '0';
        while (isdigit(ch = _next_char())) x = x * 10 + (ch - '0');
        x *= sgn;
    }
    template<class T, class... Ts> void _ri(T& t, Ts&... ts) { _ri(t); _ri(ts...); }
    char obuf[BSZ], numBuf[100]; int opos;
    void flushOut() {
        fwrite(obuf, 1, opos, stdout); opos = 0;
    }
    void _wc(char c) {
        if (opos == BSZ) flushOut();
        obuf[opos++] = c;
    }
    void _ws(string s) { for (char& c : s) _wc(c); }
    template<class T> void _wi(T x) {
        if (x < 0) _wc('-'), x *= -1;
        int len = 0;
        for (; x >= 10; x /= 10) numBuf[len++] = '0' + (x % 10);
        _wc('0' + x);
        for (int i = len - 1; i >= 0; i--) _wc(numBuf[i]);
    }
    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value>::type _rf(T &x) {
        str in; _rs(in); x = stold(in);
    }
    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value>::type _wf(T& x) {
        ostringstream sout;
        sout << std::fixed << std::setprecision(precision) << x;
        str out = sout.str();
        each(c, out) _wc(c);
    }
    long double _nf() { long double x; _rf(x); return x; }
    void initO() { assert(atexit(flushOut) == 0); }
#else
    char _nc() { char ch; cin >> ch; return ch; }
    void _rc(char& ch) { cin >> ch; }
    string _ns() { string x; cin >> x; return x; }
    void _rs(string& x) { cin >> x; }
    int _ni() { int x; cin >> x; return x; }
    ll _nl() { ll x; cin >> x; return x; }
    template<class T> void _ri(T& x) { cin >> x; }
    template<class T, class... Ts> void _ri(T& t, Ts&... ts) { ri(t); ri(ts...); }
    void _wc(char c) {
        if (c == '\n') cout << endl;
        else cout << c;
    }
    void _ws(string s) { cout << s; }
    template<class T> void _wi(T x) { cout << x; }
    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value>::type _rf(T &x) { cin >> x; }
    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value>::type _wf(T& x) { cout << std::fixed << std::setprecision(precision) << x; }
    long double _nf() { long double x; _rf(x); return x; }
    void initO() { cin.tie(0)->sync_with_stdio(0); }
#endif
}

void setfileaio(string name) {
#ifndef LOCAL
    if (name == "") return;
    freopen((name + "in.txt").c_str(), "r", stdin);
    freopen((name + "out.txt").c_str(), "w", stdout);
#endif
}

void setfile(string pfx) {
#ifndef LOCAL
    if (pfx == "") return;
    freopen((pfx + ".in").c_str(), "r", stdin);
    freopen((pfx + ".out").c_str(), "w", stdout);
#endif
}

template<typename... Args> // tuples
ostream& operator<<(ostream& os, tuple<Args...> t) {
    apply([&](Args... args) { string dlm = "{"; ((os << dlm << args, dlm = ", "), ...); }, t);
    return os << "}";
}

template<typename T, typename V> // pairs
ostream& operator<<(ostream& os, pair<T, V> p) { return os << "{" << p.f << ", " << p.s << "}"; }

template<typename T, typename V>
istream& operator>>(istream& os, pair<T, V> p) { return os >> p.f >> p.s; }

template<class T, class = decltype(begin(declval<T>()))> // iterables
typename enable_if<!is_same<T, string>::value, ostream&>::type operator<<(ostream& os, const T& v) {
    os << "{";
    string dlm = "";
    for (auto i : v) os << dlm << i, dlm = ", ";
    return os << "}";
}

template<class T, class = decltype(begin(declval<T>()))>
typename enable_if<!is_same<T, string>::value, istream&>::type operator>>(istream& os, T& v) {
    for (auto& i : v) os >> i;
    return os;
}

template<typename T>
typename enable_if<is_integral<T>::value>::type read(T& x) { IO::_ri(x); }
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value>::type read(T &x) { IO::_rf(x); }
void read(bool& x) { char c; read(c); x = (c == '1'); }
void read(string& x) { IO::_rs(x); }
template<class T, class U> void read(pair<T, U>& x) { read(x.f); read(x.s); }
template<class T, class = decltype(begin(declval<T>()))>
typename enable_if<!is_same<T, string>::value>::type read(T& v) { for (auto& i : v) read(i); }
template<class T, class... Ts> void read(T& t, Ts&... ts) { read(t); read(ts...); }

template<typename T>
typename enable_if<is_integral<T>::value>::type _print(T x) { IO::_wi(x); }
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value>::type _print(T& x) { IO::_wf(x); }
void _print(const bool& x) { IO::_wi(x); }
void _print(const char& c) { IO::_wc(c); }
void _print(const string& x) { IO::_ws(x); }
void _print(const char* x) { IO::_ws(x); }
template<class T, class U>
void _print(const pair<T, U>& x) { _print(x.first); _print(' '); _print(x.second); }
template<class T, class = decltype(begin(declval<T>()))>
typename enable_if<!is_same<T, string>::value>::type _print(const T& v) { each(i, v) _print(i), _print(' '); }
template<class T> void print(const T& t) { _print(t); _print(' '); }
template<class T, class... Ts> void print(const T& t, const Ts&... ts) { _print(t); _print(' '); print(ts...); }
template <typename T>
void print(initializer_list<T> args) { each(e, args) _print(e); }
void println() { _print('\n'); }
template<class T> void println(const T& t) { _print(t); _print('\n'); }
template<class T, class... Ts> void println(const T& t, const Ts&... ts) { _print(t); _print(' '); println(ts...); }
template<class T>
void println(initializer_list<T> args) { each(e, args) _print(e); _print('\n'); }

int nxti() { return IO::_ni(); }
ll nxtl() { return IO::_nl(); }
char nxtc() { return IO::_nc(); }

#define ri1(a) int a = IO::_ni()
#define ri2(a, b) int a = IO::_ni(); int b = IO::_ni()
#define ri3(a, b, c) int a = IO::_ni(); int b = IO::_ni(); int c = IO::_ni()
#define ri4(a, b, c, d) int a = IO::_ni(); int b = IO::_ni(); int c = IO::_ni(); int d = IO::_ni()
#define rid1(a) int a = IO::_ni() - 1
#define rid2(a, b) int a = IO::_ni() - 1; int b = IO::_ni() - 1
#define rid3(a, b, c) int a = IO::_ni() - 1; int b = IO::_ni() - 1; int c = IO::_ni() - 1
#define rid4(a, b, c, d) int a = IO::_ni() - 1; int b = IO::_ni() - 1; int c = IO::_ni() - 1; int d = IO::_ni() - 1
#define rl1(a) ll a = IO::_nl()
#define rl2(a, b) ll a = IO::_nl(); ll b = IO::_nl()
#define rl3(a, b, c) ll a = IO::_nl(); ll b = IO::_nl(); ll c = IO::_nl()
#define rl4(a, b, c, d) ll a = IO::_nl(); ll b = IO::_nl(); ll c = IO::_nl(); ll d = IO::_nl()
#define rd1(a) db a = IO::_nf()
#define rd2(a, b) db a = IO::_nf(); db b = IO::_nf()
#define rd3(a, b, c) a = IO::_nf(); b = IO::_nf(); c = IO::_nf()
#define rd4(a, b, c, d) a = IO::_nf(); b = IO::_nf(); c = IO::_nf(), d = IO::_nf()
#define rc(a) char a = IO::_nc()
#define rs1(a) string a = IO::_ns()
#define rs2(a, b) string a = IO::_ns(); string b = IO::_ns()
#define rvi(a, n) vi a(n); FOR (i, n) IO::_ri(a[i])
#define rvid(a, n) vi a(n); FOR (i, n) IO::_ri(a[i]), a[i]--;
#define rvl(a, n) vl a(n); FOR (i, n) IO::_ri(a[i])
#define rvb(a, n) vb a(n); FOR (i, n) a[i] = (nxtc() == '1')

#define ri(...) VFUNC(ri, __VA_ARGS__)
#define rid(...) VFUNC(rid, __VA_ARGS__)
#define rl(...) VFUNC(rl, __VA_ARGS__)
#define rd(...) VFUNC(rd, __VA_ARGS__)
#define rs(...) VFUNC(rs, __VA_ARGS__)

const int inf = 1e9;
const ll INF = 1e18;
const db eps = 1e-9;

vi make_perm(int n) { vi ret(n); iota(all(ret), 0); return ret; }
template<class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }