#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

const int maxn = 1 << 19;

int BIT[maxn];

void Add(int idx, int val) {
    while (idx < maxn) BIT[idx] ^= val, idx += idx & -idx;
}

int Sum(int idx, int ans = 0) {
    while (idx) ans ^= BIT[idx], idx -= idx & -idx;
    return ans;
}

int SumR(int idxL, int idxR) {
    return Sum(idxR) ^ Sum(idxL-1);
}

void solve() {
    int N, Q; cin >> N >> Q;
    
    for (int i = 1, tmp; i <= N; ++i) cin >> tmp, Add(i, tmp);
    
    while (Q--) {
        int op, x, y; cin >> op >> x >> y;
             if (op == 1) Add(x, y);
        else if (op == 2) cout << SumR(x, y) << "\n";
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