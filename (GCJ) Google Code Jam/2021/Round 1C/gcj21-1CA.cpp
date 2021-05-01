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
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

void solve() {
    int N, K; cin >> N >> K;
    
    vector<int> v(N);
    for (auto &x : v) cin >> x;
    sort(ALL(v)), v.resize(unique(ALL(v)) - begin(v));
    N = v.size();
    
    // cout << v << "\n";
    
    vector<int> cost1, cost2;
    if (v.front() > 1) cost1.eb(v.front() - 1);
    if (v.back() < K) cost1.eb(K - v.back());
    for (int i = 1; i < N; ++i) {
        if (v[i] - v[i-1] > 1) {
            cost1.eb((v[i] - v[i-1]) / 2);
            cost2.eb(v[i] - v[i-1] - 1);
        }
    }
    sort(RALL(cost1));
    
    int max_cost1 = (cost1.size() >= 1 ? cost1[0] : (int)0)
                  + (cost1.size() >= 2 ? cost1[1] : (int)0);
    int max_cost2 = cost2.size() >= 1 ? *max_element(ALL(cost2)) : (int)0;
    cout << fixed << setprecision(9);
    cout << (double)max(max_cost1, max_cost2) / K << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}