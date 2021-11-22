#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 15E4 + 5;
const int maxc = 1E6 + 5;

vector<int> prime_factor[maxc], all_primes, par(maxn+maxc);
vector<pii> valid_sol; /// (R(p), R(q))
bitset<maxc> is_prime;

int R(int x) {return x ^ par[x] ? par[x] = R(par[x]) : x;}
void U(int x, int y) {x = R(x), y = R(y); par[x] = y;}

void solve() {
    int N, Q; cin >> N >> Q;
    
    vector<int> A(N);
    for (auto &x : A) cin >> x;
    
    /**
     * answer will \le 2 since A_i * (A_i + 1) is even
     * add (i, p) for all p \in [1, maxc] \land p | A_i
     * let S_i be {p : p \in [1, maxc] \land p | A_i * (A_i + 1)},
     *     store all pairs in S_i as a map
     * the size of S_i is at most O(lg N^2) = O(lg N)
    **/
    
    for (int i = 0; i < N; ++i) {
        for (auto p : prime_factor[A[i]]) U(i, maxn+p);
    }
    
    for (int i = 0; i < maxn+maxc; ++i) R(i); /// par[i] = R(i)
    
    for (int i = 0; i < N; ++i) {
        static vector<int> tmp;
        tmp.clear();
        for (auto p : prime_factor[A[i]])   tmp.eb(maxn+p);
        for (auto p : prime_factor[A[i]+1]) tmp.eb(maxn+p);
        for (auto p : tmp) for (auto q : tmp) {
            if (par[p] < par[q]) valid_sol.eb(par[p], par[q]);
        }
    }
    sort(ALL(valid_sol));
    valid_sol.resize(unique(ALL(valid_sol)) - begin(valid_sol));
    
    for (int i = 0; i < Q; ++i) {
        int s, t; cin >> s >> t, --s, --t;
        if (par[s] > par[t]) swap(s, t);
        if (par[s] == par[t]) cout << 0 << "\n";
        else if (binary_search(ALL(valid_sol), pii{par[s], par[t]})) cout << 1 << "\n";
        else cout << 2 << "\n";
    }
}

void init() {
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2, j = 2; i < maxc; j = ++i) {
        if (is_prime[i]) {
            all_primes.eb(i);
            prime_factor[i].eb(i);
            while ((j += i) < maxc) {
                prime_factor[j].eb(i), is_prime[j] = 0;
            }
        }
    }
    iota(ALL(par), 0);
}

int32_t main() {
    fastIO();
    init();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}