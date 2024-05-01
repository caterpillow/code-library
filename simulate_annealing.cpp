#pragma optimize "Ofast,unroll-all-loops,inline"
 
#include <bits/stdc++.h>
#include <sys/time.h>
 
using namespace std;
 
using ll = long long;
using db = long double;
#define uid uniform_int_distribution
#define urd uniform_real_distribution
using pl = pair<int, int>;
#define vt vector
#define f first
#define s second
#define all(x) x.begin(), x.end() 
#define pb push_back
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define F0R(i, b) FOR (i, 0, b)
#define debug(x) do{auto _x = x; cerr << #x << " = " << _x << endl;} while(0)
const ll INF = 1e18;
 
double get_time() { timeval tv; gettimeofday(&tv, NULL); return tv.tv_sec + tv.tv_usec * 1e-6; }
double start_time;
double elapsed() { return get_time() - start_time; }
 
random_device rd;
mt19937 mt(rd());
 
uniform_real_distribution<db> rdist(0, 1);
inline db next_double() { return rdist(mt); }
 
int rnd(int lo, int hi) {
    return mt() % (hi - lo + 1) + lo;
}

 
// start and end temperatures (dependant on cost function)
db t0 = 1;
const db tn = 0.0001;
 
const db MAX_TIME = 25000;

ifstream fin;
ofstream fout;
 
// stuff


// end stuff
 
struct State {
    db value;

    db calc_value() {
        db tot = 0;

 
        return value = tot;
    }
 
    void get_neighbour() { // modify current state into some neighbour state

    }
 
    void print() {
        cerr << "cost: " << value;
    }
 
    db comp(const State& b) { // positive if a < b (b is better than a) 
        return value - b.value;
    }
};
 
State best;
 
void solve(int test_case) {

    cerr << "\nsolving test case " << test_case << endl;

    fin = ifstream("/home/caterpillow/cp/orac2/contests/fario/2008/leafin/leaf." + to_string(test_case) + ".in");
    fout = ofstream("/home/caterpillow/cp/orac2/contests/fario/2008/leafout/leaf." + to_string(test_case) + ".out");

    start_time = get_time();

    State cur {};

    // input (and set cur state)



    // end input
 
    int its = 0;
    t0 = 0.001;

    cur.calc_value();
    best = cur;

    // t0 = cur.value;

    while (true) {
        its++;
        db time_passed = elapsed() / MAX_TIME;
        if (time_passed > 1) break;
        
        State neighbour = cur;
        neighbour.get_neighbour();
        neighbour.calc_value();

        db temp = t0 * pow(tn / t0, time_passed);

        if (cur.comp(neighbour) >= 0 || next_double() < exp((cur.comp(neighbour)) / temp)) { 
            cur = neighbour;
        }
 
        if (best.comp(cur) > 0) {
            best = cur;
        }
    }
 
    cerr << "Time elapsed: " << elapsed() << endl;
    cerr << "States checked: " << its << endl;
    best.print();
} 

main() {
    cin.tie(0)->sync_with_stdio(0);

    vt<int> cases = {3, 4, 5, 9, 10};

    for (int i : cases) {
        solve(i);
    }
}