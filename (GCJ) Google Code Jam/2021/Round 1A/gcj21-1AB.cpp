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

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxp = 499;

vector<int> factorize(int x) {
    vector<int> ret;
    for (int i = 2; i * i <= x and i <= maxp; ++i) {
        while (x % i == 0) x /= i, ret.eb(i);
    }
    if (x > 1) ret.eb(x);
    return ret;
}

void solve() {
    int n; cin >> n;
    
    int sum = 0;
    // vector<int> cards(maxp+1);
    map<int, int> cards;
    for (int i = 0; i < n; ++i) {
        int p, c; cin >> p >> c;
        sum += p * c, cards[p] = c;
    }
    
    for (int i = sum-1; i >= max(2LL, sum-maxp*60); --i) {
        auto factor = factorize(i);
        int fl = 1;
        for (auto x : factor) fl &= --cards[x] >= 0;
        for (auto x : factor) ++cards[x];
        if (fl and accumulate(ALL(factor), 0) == sum - i) return cout << i << "\n", void();
    }
    cout << 0 << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}