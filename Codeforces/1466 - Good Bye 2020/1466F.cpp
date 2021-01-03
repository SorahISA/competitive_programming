#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int mod = 1E9 + 7;
const int maxm = 5E5 + 5;

int cc_sz, cc_fl;
vector<int> adj[maxm], col(maxm), vis(maxm);
vector<int> p(maxm), chosed(maxm);

int R(int x) {
    return x ^ p[x] ? p[x] = R(p[x]) : x;
}

int U(int x, int y) {
    x = R(x), y = R(y);
    if (x == y) return 0;
    chosed[y] |= chosed[x], p[x] = y;
    return 1;
}

void dfs(int now) {
    vis[now] = 1, ++cc_sz;
    if (col[now]) cc_fl = 1;
    for (auto x : adj[now]) {
        if (!vis[x]) dfs(x);
    }
}

int fastpow(int base, int exp, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        base = base * base % mod, exp >>= 1;
    }
    return ans;
}

void solve() {
    int n, m; cin >> n >> m;
    iota(ALL(p), 0);
    
    vector<vector<int>> v(n);
    for (int i = 0; i < n; ++i) {
        int k, tmp1, tmp2; cin >> k;
        if (k == 1) {
            cin >> tmp1, col[tmp1] = 1, v[i].eb(tmp1);
        }
        else {
            cin >> tmp1, v[i].eb(tmp1);
            cin >> tmp2, v[i].eb(tmp2);
            adj[tmp1].eb(tmp2), adj[tmp2].eb(tmp1);
        }
    }
    
    int ansT = 0;
    for (int i = 1; i <= m; ++i) {
        if (!vis[i]) {
            cc_sz = cc_fl = 0, dfs(i);
            ansT += cc_sz - (cc_fl ? 0 : 1);
            // cout << "! " << i << " " << cc_sz << " " << cc_fl << "\n";
        }
    }
    ansT = fastpow(2, ansT);
    
    vector<int> pick;
    for (int i = 0; i < n; ++i) {
        if (v[i].size() == 1) {
            int x = v[i][0];
            if (!chosed[R(x)]) chosed[R(x)] = 1, pick.eb(i+1);
        }
        else {
            int x = v[i][0], y = v[i][1];
            if ((!chosed[R(x)] or !chosed[R(y)]) and U(x, y)) pick.eb(i+1);
        }
    }
    
    cout << ansT << " " << pick.size() << "\n";
    for (auto x : pick) cout << x << " ";
    cout << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
