#pragma GCC optimize("O3", "unroll-loops")

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
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int maxn = 1 << 17;

vector<int> p;
vector<tuple<int, int, int>> Query[2*maxn];
vector<pii> LR(2*maxn);

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
void U(int x, int y) {x = R(x), y = R(y); p[x] = y;}


void solve() {
    int n, q; cin >> n >> q, p.resize(n+1);
    
    vector<pii> edge;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j*j <= i; ++j) {
            if (i % j == 0) {
                if (i-j >= 1) edge.eb(i-j, i);
                if (i+j <= n) edge.eb(i, i+j);
                if (j*j == i or j == 1) continue;
                if (i-i/j >= 1) edge.eb(i-i/j, i);
                if (i+i/j <= n) edge.eb(i, i+i/j);
            }
        }
    }
    sort(ALL(edge), [](auto p1, auto p2) {
        return p1.Y - p1.X > p2.Y - p2.X;
    });
    
    for (int i = 0; i < q; ++i) {
        int a, b; cin >> a >> b;
        Query[1].eb(a, b, i);
    }
    
    for (int i = maxn; i < 2*maxn; ++i) LR[i] = pii{2*maxn-i-1, 2*maxn-i-1};
    for (int i = maxn-1; i >= 1; --i) LR[i] = pii{LR[i<<1].X, LR[i<<1|1].Y};
    // for (int i = 1; i < 2*maxn; ++i) cout << LR[i].X << " " << LR[i].Y << "\n";
    
    for (int i = 1, tok = 0; i < maxn; ++i) {
        if (LR[i].X == maxn-1) iota(ALL(p), 0), tok = 0;
        for (; tok < edge.size() and edge[tok].Y - edge[tok].X >= LR[i].Y; ++tok) {
            // cout << "merge " << edge[tok].X << " " << edge[tok].Y << " in segment " << i << "\n";
            U(edge[tok].X, edge[tok].Y);
        }
        for (auto [x, y, _] : Query[i]) {
            // cout << "check " << x << " " << y << " in segment " << i << "\n";
            if (R(x) == R(y)) Query[i<<1].eb(x, y, _);
            else Query[(i<<1)+2].eb(x, y, _);
        }
    }
    
    vector<int> ans(q, -1);
    for (int i = maxn, tok = 0; i < 2*maxn; ++i) {
        if (LR[i].X == maxn-1) iota(ALL(p), 0), tok = 0;
        for (; tok < edge.size() and edge[tok].Y - edge[tok].X >= LR[i].Y; ++tok) {
            // cout << "merge " << edge[tok].X << " " << edge[tok].Y << " in segment " << i << "\n";
            U(edge[tok].X, edge[tok].Y);
        }
        for (auto [x, y, _] : Query[i]) {
            // cout << "check " << x << " " << y << " in segment " << i << "\n";
            if (R(x) == R(y)) ans[_] = LR[i].X;
            else ans[_] = LR[i].X - 1;
        }
    }
    for (auto x : ans) cout << x << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}