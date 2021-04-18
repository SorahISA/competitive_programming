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

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 2E5 + 5;

int maxDis, maxDisID;
vector<int> adj[maxn], isheavy(maxn), val;

void dfsDia(int now, int lst = -1, int dis = 0) {
    if (dis > maxDis) tie(maxDis, maxDisID) = {dis, now};
    for (auto x : adj[now]) {
        if (x != lst) dfsDia(x, now, dis+1);
    }
}

void dfsHeavy(int now, int lst = -1) {
    for (auto x : adj[now]) {
        if (x != lst) dfsHeavy(x, now), isheavy[now] |= isheavy[x];
    }
}

void dfsAns(int now, int lst = -1) {
    static int tok = 1;
    val[now] = tok++;
    
    int heavy = -1;
    for (auto x : adj[now]) {
        if (x != lst and !isheavy[x]) dfsAns(x, now);
        if (x != lst and  isheavy[x]) heavy = x;
    }
    if (heavy != -1) dfsAns(heavy, now);
    
    ++tok;
}

void solve() {
    int n; cin >> n, val.resize(n);
    
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v, --u, --v;
        adj[u].eb(v), adj[v].eb(u);
    }
    
    /// find diameter ///
    int rt;
    maxDis = -1, dfsDia(0), rt = maxDisID;
    maxDis = -1, dfsDia(rt);
    
    /// find heavy node (node on diameter) ///
    isheavy[maxDisID] = 1, dfsHeavy(rt);
    
    dfsAns(rt);
    cout << val << "\n";
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