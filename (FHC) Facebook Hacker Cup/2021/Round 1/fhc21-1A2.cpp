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

const int mod = 1E9 + 7;

void solve() {
    int N; cin >> N;
    string W; cin >> W;
    
    int ans = 0;
    for (int i = 0, lst_p = -1; i < N; ++i) {
        if (W[i] != 'F') {
            if (lst_p != -1 and W[i] != W[lst_p]) ans += (lst_p + 1) * (N - i);
            lst_p = i;
        }
    }
    cout << ans % mod << "\n";
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