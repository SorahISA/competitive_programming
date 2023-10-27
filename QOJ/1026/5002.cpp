#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

#define ALL(x) begin(x), end(x)
#define SZ(x) ((int)(x).size())
#define eb emplace_back
#define ee emplace

const int INF = INT_MAX;
const int maxn = 1E5 + 5;


vector<int> dep;
deque<int> depth[2 * maxn];
vector<pii> edges;

bool exit_flag = false;

void WA() {
    if (!exit_flag) cout << -1 << "\n";
    exit_flag = true;
}

void recur(int l, int r, int d) {
    // cerr << l << " " << r << " " << d << "\n";
    if (d >= 100004) return WA();
    if (r == l + 1) return;
    if (SZ(depth[d])) recur(l, min(depth[d][0], r), d + 1);
    if (exit_flag) return;
    
    while (SZ(depth[d]) and depth[d][0] <= r) {
        if (dep[l] == d - 1) edges.eb(depth[d][0], l);
        else if (dep[r] == d - 1) edges.eb(depth[d][0], r);
        else return WA();
        
        if (SZ(depth[d]) > 1) recur(depth[d][0], min(depth[d][1], r), d + 1);
        else                  recur(depth[d][0], r, d + 1);
        depth[d].pop_front();
        if (exit_flag) return;
    }
}

void solve() {
    int N; cin >> N;
    
    dep.resize(2 * N);
    
    for (int i = 0; i < N; ++i) {
        cin >> dep[i], dep[i+N] = dep[i];
        depth[dep[i]].eb(i);
    }
    if (SZ(depth[0]) != 1) return WA();
    
    int root = depth[0][0];
    for (int i = 0; i < N; ++i) {
        for (int &x : depth[i]) x = (x < root ? x + N : x);
        sort(ALL(depth[i]));
    }
    
    recur(root, root + N, 1);
    
    if (SZ(edges) != N-1) return WA();
    
    for (auto [u, v] : edges) {
        if (u >= N) u -= N;
        if (v >= N) v -= N;
        cout << u + 1 << " " << v + 1 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve();
    }
    
    return 0;
}
