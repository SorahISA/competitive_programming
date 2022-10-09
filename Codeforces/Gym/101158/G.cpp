#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
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

const int INF = 1E9 + 5;

set<pii> lay;
int lay_sz = 0;

pair<bool, int> _find(int k) {
    auto it = lay.lower_bound({k, INF});
    if (it == begin(lay)) return {false, -1};
    auto [L, R] = *prev(it);
    return {(L <= k and k <= R), L-1};
};

void _merge(int qL, int qR) {
    if (qL > qR) return;
    auto it_L = lay.lower_bound({qL, INF});
    auto it_R = lay.lower_bound({qR, INF});
    auto [pL_L, pL_R] = *prev(it_L);
    auto [pR_L, pR_R] = *prev(it_R);
    lay.erase(prev(it_L), it_R);
    lay.insert({pL_L, pR_R});
};

void _delete(int qL, int qR) {
    if (qL > qR) return;
    auto it_L = lay.lower_bound({qL, INF});
    auto it_R = lay.lower_bound({qR, INF});
    auto [pL_L, pL_R] = *prev(it_L);
    auto [pR_L, pR_R] = *prev(it_R);
    lay.erase(prev(it_L), it_R);
    if (pL_L < qL) lay.insert({pL_L, qL-1});
    if (qR < pR_R) lay.insert({qR+1, pR_R});
};

void solve() {
    int N; cin >> N;
    
    while (N--) {
        int st, ed; cin >> st, ed = st;
        pair<bool, int> find_res;
        while (ed > 0) {
            find_res = _find(ed);
            if (!find_res.X) break;
            ed = find_res.Y;
        }
        
        if (lay_sz > st-ed and (ed == 0 or (*begin(lay)).X == 0)) {
            _merge(ed+1, st);
            cout << "No\n";
        }
        else {
            lay_sz -= st - ed - 1;
            _delete(ed+1, st);
            lay.insert({ed, ed});
            cout << "Yes\n";
        }
        
        // cout << "lay: ";
        // for (auto [x, y] : lay) cout << "(" << x << "," << y << ") ";
        // cout << lay_sz << "\n";
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
