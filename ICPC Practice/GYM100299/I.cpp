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

template<class T1, class T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << p.first+1 << " " << p.second+1;
    return os;
}

template<class T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) os << vec[i] << "\n";
    return os;
}

void solve() {
    int n; cin >> n;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    
    vector<pii> op; /// (L, R)
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (v[j] == i+1) {
                while (j > i) {
                    if ((i^j)&1) op.eb(i, j);
                    else         op.eb(i+1, j);
                    // cout << "back: " << op.back() << "\n";
                    for (int k1 = op.back().X, k2 = (op.back().X+op.back().Y+1)/2; k2 <= op.back().Y; ++k1, ++k2) {
                        swap(v[k1], v[k2]);
                    }
                    j = i + j >> 1;
                }
                break;
            }
        }
    }
    
    cout << op.size() << "\n" << op;
    // cout << "v:\n" << v << "\n";
}

int32_t main(int32_t argc, char *argv[]) {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}