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
#define ef push_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) (int)(x).size()
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int maxn = 1 << 18;

int BIT[maxn];

void Add(int idx, int val) {
    while (idx < maxn) BIT[idx] += val, idx += idx & -idx;
}

int Sum(int idx, int ans = 0) {
    while (idx) ans += BIT[idx], idx -= idx & -idx;
    return ans;
}

void solve() {
    int N; cin >> N;
    
    vector<int> vec(N);
    for (int i = 0, tmp; i < N; ++i) {
        cin >> tmp, vec[tmp-1] = i+1;
    }
    reverse(ALL(vec));
    
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        ans += Sum(vec[i]), Add(vec[i], 1);
    }
    cout << ans << "\n";
    
    // for (auto x : vec) cout << x << " ";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}