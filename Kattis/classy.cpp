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
    int n; cin >> n;
    
    vector<pair<string, string>> ranks;
    while (n--) {
        string name; cin >> name, name.pop_back();
        string clas; cin >> clas;
        string trash; cin >> trash;
        string pri;
        for (int i = 0; i < clas.size(); ++i) {
            if (clas.substr(i, 5) == "upper")  pri += '0', i += 4;
            if (clas.substr(i, 6) == "middle") pri += '1', i += 5;
            if (clas.substr(i, 5) == "lower")  pri += '2', i += 4;
        }
        reverse(ALL(pri)), pri.resize(10, '1');
        ranks.eb(pri, name);
    }
    sort(ALL(ranks));
    
    for (auto [pri, name] : ranks) cout << name << "\n";
    cout << string(30, '=') << "\n";
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