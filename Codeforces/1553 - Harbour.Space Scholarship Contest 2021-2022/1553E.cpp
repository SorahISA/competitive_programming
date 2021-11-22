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

void solve() {
    int N, M; cin >> N >> M;
    
    vector<int> goal(N);
    for (auto &x : goal) cin >> x, --x;
    
    /// M \le N/3 --> at least N/3 of the element must be in the right order ///
    
    vector<int> perm_type_cnt(N, 0);
    for (int i = 0; i < N; ++i) ++perm_type_cnt[(i-goal[i]+N) % N];
    
    vector<int> ans;
    for (int shift = 0; shift < N; ++shift) {
        if (3 * perm_type_cnt[shift] < N) continue;
        vector<int> nxt(N);
        for (int i = 0; i < N; ++i) nxt[goal[i]] = (i-shift+N) % N;
        // cerr << nxt << "\n";
        
        int cnt = 0, now, sz;
        vector<int> vis(N, 0);
        for (int i = 0; i < N; ++i) {
            if (!vis[i]) {
                now = i, sz = 0;
                do ++sz, now = nxt[now], vis[now] = 1; while (!vis[i]);
                // cerr << sz << "!";
                cnt += sz-1;
            }
        }
        if (cnt <= M) ans.eb(shift);
    }
    cout << ans.size() << " " << ans << "\n";
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