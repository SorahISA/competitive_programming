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

void solve() {
    int A, B, C, T, ta, tb; cin >> A >> B >> T >> ta >> tb >> C;
    
    vector<pii> need(C);
    for (auto &[a, b] : need) {
        cin >> a >> b, a = ta * max(a - A, 0LL), b = tb * max(b - B, 0LL);
    }
    sort(ALL(need));
    
    int ans = 0;
    Prior<int> pq;
    for (int i = 0; i < C; ++i) {
        pq.push(need[i].Y);
        while (!pq.empty() and pq.top() > T - need[i].X) pq.pop();
        ans = max(ans, (int)pq.size());
    }
    cout << ans << "\n";
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