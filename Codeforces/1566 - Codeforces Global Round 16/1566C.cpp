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
    string S, T; cin >> S >> T;
    
    auto MEX = [&](int L, int R) -> int {
        int ans = 0;
        for (auto num : {'0', '1'}) {
            int flag = 0;
            for (int i = L; i <= R; ++i) {
                if (S[i] == num or T[i] == num) {++ans, flag = 1; break;}
            }
            if (!flag) break;
        }
        return ans;
    };
    
    vector<int> dp(N);
    dp[0] = MEX(0, 0);
    for (int i = 1; i < N; ++i) {
        dp[i] = max(dp[i-1] + MEX(i, i), (i >= 2 ? dp[i-2] : (int)0) + MEX(i-1, i));
    }
    // cout << dp << "\n";
    cout << dp[N-1] << "\n";
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