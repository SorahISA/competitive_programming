#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define eb emplace_back
#define pb pop_back
#define X first
#define Y second
#ifdef local
#define debug(...) \
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__),\
    _do(__VA_ARGS__);
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S &&..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs){return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs){return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    vector<int> out(N), deg_i(N, 0);
    for (int &x : out) cin >> x, ++deg_i[--x];
    
    int ans = 1;
    vector<int> vis(N, 0), len(N, 0);
    for (int i = 0; i < N; ++i) {
        if (!deg_i[i]) {
            deque<int> deq;
            int now = i, cnt = 0;
            while (!vis[now]) deq.eb(now), ++cnt, vis[now] = 1, now = out[now];
            chmax(ans, cnt + len[now]);
            
            int cyc = 1;
            while (cyc <= SZ(deq) and deq[SZ(deq)-cyc] != now) ++cyc;
            if (cyc <= SZ(deq)) {
                for (int j = 0; j < cyc; ++j) len[deq.back()] = cyc, deq.pb();
            }
            while (SZ(deq)) len[deq.back()] = len[out[deq.back()]] + 1, deq.pb();
        }
    }
    
    for (int i = 0; i < N; ++i) {
        if (!vis[i]) {
            int now = i, cnt = 0;
            while (!vis[now]) ++cnt, vis[now] = 1, now = out[now];
            chmax(ans, cnt);
        }
    }
    cout << ans << "\n";
    
    // for (int i = 0; i < N; ++i) debug(len[i]);
}

signed main() {
    IOS();
    int _ = 1;
    // cin >> _;
    for (int i=1;i<=_;++i) {
        solve();
    }
}
