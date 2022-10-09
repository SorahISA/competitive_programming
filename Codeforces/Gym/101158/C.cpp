#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
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

void solve() {
    int N, M; cin >> N >> M;
    
    vector<pii> robot(M);
    for (auto &[x, y] : robot) cin >> x >> y;
    sort(RALL(robot));
    
    vector<int> seq[N];
    for (int i = 0; i < N; ++i) seq[i].eb(i);
    for (int i = 0; i < M; ++i) {
        auto [x, y] = robot[i];
        seq[y-1].eb(2*N+i), seq[y].eb(2*N+i);
    }
    for (int i = 0; i < N; ++i) seq[i].eb(N+i);
    
    vector<int> nxt[2*N+M];
    for (int i = 0; i < N; ++i) {
        int sz = SZ(seq[i]);
        for (int j = 1; j < sz; ++j) {
            nxt[seq[i][j-1]].eb(seq[i][j]);
        }
    }
    
    vector<pii> val(2*N+M, {N-1, 0});
    for (int i = 0; i < N; ++i) val[N+i] = {i, i};
    
    for (int i = 2*N+M-1; i >= 2*N; --i) {
        // assert(SZ(nxt[i]) == 2);
        for (auto x : nxt[i]) {
            chmin(val[i].X, val[x].X);
            chmax(val[i].Y, val[x].Y);
        }
    }
    
    for (int i = 0; i < N; ++i) {
        // assert(SZ(nxt[i]) == 1);
        for (auto x : nxt[i]) {
            chmin(val[i].X, val[x].X);
            chmax(val[i].Y, val[x].Y);
        }
    }
    
    for (int i = 0; i < N; ++i) {
        cout << val[i].Y - val[i].X + 1 << " \n"[i == N-1];
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
