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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 100 + 5;

vector<int> adj[2*maxn], vis(2*maxn), match(2*maxn);

int FindAugmentingPath(int now) {
    for (auto x : adj[now]) {
        if (vis[x]) continue;
        vis[x] = 1;
        if (match[x] == -1 or FindAugmentingPath(match[x])) {
            match[x] = now; return 1;
        }
    }
    return 0;
}

int BipartiteMatching() {
    fill(ALL(match), -1);
    int cnt = 0;
    for (int i = 0; i < maxn; ++i) {
        fill(ALL(vis), 0), cnt += FindAugmentingPath(i);
    }
    // cout << cnt << "\n";
    return cnt;
}

void solve() {
    int N; cin >> N;
    
    vector<vector<int>> A(N, vector<int>(N));
    for (auto &vec : A) for (auto &x : vec) cin >> x;
    
    int match_cnt = 0;
    for (int tp = -N; tp <= N; ++tp) {
        if (tp == 0) continue;
        for (int i = 0; i < 2*maxn; ++i) vector<int>().swap(adj[i]);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == tp) adj[i].eb(maxn+j);
            }
        }
        match_cnt += BipartiteMatching();
    }
    cout << N*N - match_cnt << "\n";
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