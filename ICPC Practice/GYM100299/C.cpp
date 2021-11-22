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

template<class T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) os << vec[i] << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    
    int ans = *max_element(ALL(v));
    map<int, int> max_gcd;
    for (int i = 0; i < n; ++i) {
        map<int, int> tmp;
        for (auto [g, st] : max_gcd) {
            int gg = __gcd(g, v[i]);
            if (tmp.find(gg) == tmp.end()) tmp[gg] = st;
            else tmp[gg] = min(tmp[gg], st);
        }
        tmp.swap(max_gcd);
        if (max_gcd.find(v[i]) == max_gcd.end()) max_gcd[v[i]] = i;
        for (auto [g, st] : max_gcd) ans = max(ans, (i-st+1) * g);
        // for (auto [g, st] : max_gcd) cout << "(" << g << "," << st << ") ";
        // cout << ans << "\n";
    }
    cout << ans << "\n";
}

int32_t main(int32_t argc, char *argv[]) {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}

/*
3
10
19 17 19 17 19 17 19 17 19 17
10
9 7 9 7 9 7 9 7 9 7
1
100
*/