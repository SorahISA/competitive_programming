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
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 1 << 17;

int BIT[maxn];

int Sum(int idx, int ans = 0) {
    ++idx;
    while (idx) ans += BIT[idx], idx -= idx & -idx;
    return ans;
}

void Add(int idx, int val) {
    ++idx;
    while (idx < maxn) BIT[idx] += val, idx += idx & -idx;
}

void solve() {
    int N; cin >> N;
    
    int even, odd = 0;
    vector<int> vec(N);
    for (auto &x : vec) cin >> x, x &= 1, odd += x;
    even = N - odd;
    
    if (abs(odd - even) > 1) return cout << -1 << "\n", void();
    
    int ans = N * N;
    if (odd >= even) {
        vector<int> perm(N);
        for (int i = 0, odd_cnt = 0, even_cnt = 0; i < N; ++i) {
            if (vec[i]) perm[2*odd_cnt++] = i;
            else        perm[2*even_cnt++ + 1] = i;
        }
        int odd_ans = 0;
        for (auto x : perm) {
            odd_ans += x - Sum(x), Add(x, 1);
        }
        for (auto x : perm) Add(x, -1);
        ans = min(ans, odd_ans);
    }
    if (even >= odd) {
        vector<int> perm(N);
        for (int i = 0, odd_cnt = 0, even_cnt = 0; i < N; ++i) {
            if (vec[i]) perm[2*odd_cnt++ + 1] = i;
            else        perm[2*even_cnt++] = i;
        }
        int even_ans = 0;
        for (auto x : perm) {
            even_ans += x - Sum(x), Add(x, 1);
        }
        for (auto x : perm) Add(x, -1);
        ans = min(ans, even_ans);
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}