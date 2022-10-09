#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T>
bool chmin(T &x, T y) {
    if (x > y) return x = y, true;
    return false;
}

template<typename T>
bool chmax(T &x, T y) {
    if (x < y) return x = y, true;
    return false;
}

const int mod1 =  998244353;
const int p1 = 257;
const int mod2 = 1000000007;
const int p2 = 299;

pii _hash(vector<int> &app) {
    int ans1 = 0, ans2 = 0;
    for (auto x : app) {
        ans1 = ((int64_t)ans1 * p1 + x) % mod1;
        ans2 = ((int64_t)ans2 * p2 + x) % mod2;
    }
    return {ans1, ans2};
}

void solve() {
    string S, T; cin >> S >> T;
    int N = SZ(S), M = SZ(T);
    
    vector<vector<int>> app_S(N, vector<int>(26, 0));
    vector<vector<int>> app_T(M, vector<int>(26, 0));
    set<pii> st;
    int ans = 0;
    
    for (int len = 0; len < min(N, M); ++len) {
        st.clear();
        for (int i = 0; i+len < N; ++i) {
            ++app_S[i][S[i+len]-'a'];
            st.insert(_hash(app_S[i]));
        }
        for (int i = 0; i+len < M; ++i) {
            ++app_T[i][T[i+len]-'a'];
            if (st.count(_hash(app_T[i]))) chmax(ans, len+1);
        }
    }
    
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
