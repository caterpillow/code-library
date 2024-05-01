#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pl = pair<ll, ll>;
#define vt vector
#define f first
#define s second
#define all(x) x.begin(), x.end() 
#define pb push_back
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define F0R(i, b) FOR (i, 0, b)
#define endl '\n'
const ll INF = 1e18;

template<template<typename> class Container, typename T>
ostream& operator<<(ostream& os, Container<T> o) {
    os << "{"; 
    int g = o.size(); 
    for (auto i : o) os << i << ((--g) == 0 ? "" : ", "); 
    os << "}";
    return os;
}

void _print() {
    cerr << "\n";
}

template<typename T, typename ...V>
void _print(T t, V... v) {
    cerr << t; if (sizeof...(v)) cerr << ", "; _print(v...);
}

#ifdef LOCAL
#define dbg(x...) cerr <<__func__ << ":" <<__LINE__ << " " << #x << " = "; _print(x);
#else
#define dbg(x...)
#endif

main() {
    cin.tie(0)->sync_with_stdio(0);
    
    $0
}