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

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 200 + 5;

vector<vector<double>> floyd(maxn, vector<double>(maxn, 1.1e9));
vector<pii> node;
vector<tuple<pii, pii, double>> edge;

double dist(pii p0, pii p1, int spd) {
    int distsq = (p0.X - p1.X) * (p0.X - p1.X) + (p0.Y - p1.Y) * (p0.Y - p1.Y);
    return sqrt(distsq) / spd;
}

void solve() {
    pii pS, pT; cin >> pS.X >> pS.Y >> pT.X >> pT.Y;
    edge.eb(pS, pT, dist(pS, pT, 10));
    node.eb(pS), node.eb(pT);
    
    int xi, yi;
    while (cin >> xi >> yi) {
        vector<pii> v{{xi, yi}};
        while (cin >> xi >> yi and xi != -1) v.eb(xi, yi);
        for (int i = 1; i < v.size(); ++i) edge.eb(v[i-1], v[i], dist(v[i-1], v[i], 40));
        for (auto x : v) node.eb(x);
    }
    sort(ALL(node));
    node.resize(unique(ALL(node)) - begin(node));
    
    for (auto [p0, p1, dis] : edge) {
        int id0 = lower_bound(ALL(node), p0) - begin(node);
        int id1 = lower_bound(ALL(node), p1) - begin(node);
        floyd[id0][id1] = floyd[id1][id0] = min(floyd[id0][id1], dis);
    }
    
    int n = node.size();
    for (int i = 0; i < n; ++i) {
        floyd[i][i] = 0.0;
        for (int j = i+1; j < n; ++j) {
            if (floyd[i][j] > 1e9) {
                floyd[i][j] = floyd[j][i] = dist(node[i], node[j], 10);
            }
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                floyd[i][j] = min(floyd[i][j], floyd[i][k] + floyd[k][j]);
            }
        }
    }
    
    // for (auto x : node) cout << x.X << " " << x.Y << "\n";
    
    // for (int i = 0; i < n; ++i) {
        // for (int j = 0; j < n; ++j) {
            // cout << setprecision(9) << floyd[i][j] << " \n"[j == n-1];
        // }
    // }
    
    int idS = lower_bound(ALL(node), pS) - begin(node);
    int idT = lower_bound(ALL(node), pT) - begin(node);
    cout << round(floyd[idS][idT] * 0.06) << "\n";
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