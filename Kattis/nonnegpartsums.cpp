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

void solve(int n) {
    vector<int> v(n), sum(n), minPre(n), minSuf(n);
    for (auto &x : v) cin >> x;
    
    partial_sum(ALL(v), begin(sum));
    minPre = minSuf = sum;
    for (int i = 1; i < n; ++i) minPre[i] = min(minPre[i], minPre[i-1]);
    for (int i = n-2; i >= 0; --i) minSuf[i] = min(minSuf[i], minSuf[i+1]);
    
    int ans = minPre.back() >= 0;
    for (int i = 0; i < n-1; ++i) {
        if (minSuf[i+1] < sum[i]) continue;
        if (minPre[i] < -(sum.back() - sum[i])) continue;
        ++ans;
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int n;
    while (cin >> n and n) {
        solve(n);
    }
    
    return 0;
}

/*
-2  3 -4 -1  1  2 -3  4  9
-2 +5 -7 +3 +2 +1 -5 +7 +5
*/