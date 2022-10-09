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
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &x, T y) {return x > y ? x = y, 1 : 0;}
template<typename T> bool chmax(T &x, T y) {return x < y ? x = y, 1 : 0;}

const int INF = INT_MAX;
const int week = 10'080;

void solve() {
    int L, M; scanf("%lld %lld\n", &L, &M);
    
    int min_p = INF;
    vector<string> candidates;
    vector<tuple<string, int, int, int, int>> mower(M);
    for (auto &[str, p, c, t, r] : mower) {
        char _str[70];
        scanf("%[^,],%lld,%lld,%lld,%lld\n", _str, &p, &c, &t, &r);
        str = string(_str);
        // printf("|%lld|%lld|%lld|%lld|%s|\n", r, t, c, p, str.c_str());
        
        auto val = [&](int x) {
            return c * (min(x % (t+r), t) + t * x / (t+r));
        };
        
        int d = gcd(week, t+r), min_work = INF;
        for (int i = 1; i <= (t+r)/d; ++i) {
            chmin(min_work, val(i * week) / i);
        }
        
        // cout << min_work << "\n";
        
        if (min_work >= L) {
            if (chmin(min_p, p)) candidates.clear();
            if (p == min_p) candidates.eb(str);
        }
    }
    if (!SZ(candidates)) return cout << "no such mower\n", void();
    for (auto &str : candidates) cout << str << "\n";
}

int32_t main() {
    // fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}