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

void chmin(int &x, int y) {x = min(x, y);}

void solve() {
    string S; cin >> S;
    int N = S.size(), K; cin >> K;
    
    vector<int> cnt(26, 0);
    for (auto &c : S) ++cnt[c-'A'];
    
    int floyd[26][26];
    memset(floyd, 0x01, sizeof(floyd)); /// = 72'340'172'838'076'673
    for (int i = 0; i < 26; ++i) floyd[i][i] = 0;
    
    for (int i = 0; i < K; ++i) {
        char u, v; cin >> u >> v;
        floyd[u-'A'][v-'A'] = 1;
    }
    
    for (int k = 0; k < 26; ++k) {
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                chmin(floyd[i][j], floyd[i][k] + floyd[k][j]);
            }
        }
    }
    
    int ans = N * 26;
    for (int i = 0; i < 26; ++i) {
        int cost = 0;
        for (int j = 0; j < 26; ++j) cost += cnt[j] * floyd[j][i];
        chmin(ans, cost);
    }
    cout << (ans == N * 26 ? -1 : ans) << "\n";
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