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

template<typename T>
bool chmin(T &lhs, T rhs) {return lhs <= rhs ? 0 : (lhs = rhs, 1);}

template<typename T>
bool chmax(T &lhs, T rhs) {return lhs >= rhs ? 0 : (lhs = rhs, 1);}

void solve() {
    int N; cin >> N;
    
    vector<int> vec(N);
    for (auto &x : vec) cin >> x;
    
    vector<int> pre(N, 0), suf(N, 0);
    for (int i = 1; i < N; ++i) {
        if (pre[i-1] == -1) pre[i] = -1;
        else pre[i] = max(vec[i-1] - pre[i-1], (int)-1);
    }
    for (int i = N-2; i >= 0; --i) {
        if (suf[i+1] == -1) suf[i] = -1;
        else suf[i] = max(vec[i+1] - suf[i+1], (int)-1);
    }
    
    int flag = suf[0] == vec[0];
    for (int i = 0; i+1 < N and !flag; ++i) {
        if (pre[i] == -1 or suf[i+1] == -1) continue;
        flag |= (vec[i+1] >= pre[i] and vec[i] >= suf[i+1] and vec[i+1] - pre[i] == vec[i] - suf[i+1]);
    }
    cout << (flag ? "YES" : "NO") << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}