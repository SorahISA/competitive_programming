#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define pf pop_front
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

const int maxq = 1E6 + 5;

int par[maxq], sz[maxq], val[maxq], anc_val[maxq][3];

void solve() {
    val[0] = INT_MAX;
    for (int qid = 1, now = 0, op, x; cin >> op; ++qid) {
             if (op == 0) cin >> now;
        else if (op == 1) cin >> x, par[qid] = now, sz[qid] = sz[now] + 1, val[qid] = x, now = qid;
        else if (op == 2) now = par[now];
        else if (op == 3) {
            if (val[now] != INT_MAX) cout << val[now] << " ";
            if (val[par[now]] != INT_MAX) cout << val[par[now]] << " ";
            if (val[par[par[now]]] != INT_MAX) cout << val[par[par[now]]] << " ";
            if (sz[now] > 3) cout << "... ";
            cout << "]\n";
        }
        par[qid] = par[now], sz[qid] = sz[now], val[qid] = val[now];
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}