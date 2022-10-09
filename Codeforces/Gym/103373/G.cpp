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
#define ef push_front
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())
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
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int maxn = 2E5 + 5;

struct Node {
    int ans = 0, inc = 1, dec = 1;
};

ostream& operator << (ostream &os, Node &g) {
    os << "(ans=" << g.ans << ", inc=" << g.inc << ", dec=" << g.dec << ")";
    return os;
}

vector<pii> adj[maxn];

Node dfs(int now, int pval = -1, int lst = -1) {
    Node g;
    vector<pii> ch_inc, ch_dec; /// (val, cnt)
    for (auto [x, val] : adj[now]) {
        if (x != lst) {
            Node tmp = dfs(x, val, now);
            g.ans += tmp.ans + tmp.inc + tmp.dec;
            if (val > pval) g.inc += tmp.inc;
            if (val < pval) g.dec += tmp.dec;
            ch_inc.eb(val, tmp.inc), ch_dec.eb(val, tmp.dec);
        }
    }
    sort(ALL(ch_inc)), sort(ALL(ch_dec));
    for (int tok_inc = 0, tok_dec = 0, sum_dec = 0; tok_inc < SZ(ch_inc); ++tok_inc) {
        while (tok_dec < SZ(ch_dec) and ch_dec[tok_dec].X < ch_inc[tok_inc].X) {
            sum_dec += ch_dec[tok_dec++].Y;
        }
        g.ans += ch_inc[tok_inc].Y * sum_dec;
    }
    // cout << now << ": " << g << "\n";
    return g;
}

void solve() {
    int N; cin >> N;
    
    for (int i = 0, u, v, w; i < N-1; ++i) {
        cin >> u >> v >> w, adj[u].eb(v, w), adj[v].eb(u, w);
    }
    cout << dfs(1).ans << "\n";
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
