#pragma GCC optimize("Ofast", "unroll-loops")
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
#define ef push_front
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())
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
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    vector<pair<int, string>> num{{0, "0"}};
    for (int i = 1, x; i <= N; ++i) {
        cin >> x;
        string val = num.back().Y;
        if (x > num.back().X) {
            int diff = x - num.back().X;
            for (int j = SZ(val)-1; j >= 0; --j) {
                while (diff and val[j] < '9') --diff, ++val[j];
            }
            while (diff) val = (char)(min(diff, 9) + '0') + val, diff = max(diff - 9, 0);
        }
        else {
            val = "0" + val;
            for (int j = SZ(val)-1, pre = num.back().X; j >= 0; --j) {
                if (val[j] != '9' and pre + 1 <= x) {
                    // cerr << "in: " << j << " " << pre+1 << " <= " << x << "\n";
                    ++val[j];
                    for (int k = j+1; k < SZ(val); ++k) val[k] = '0';
                    for (int k = SZ(val)-1, diff = x-pre-1; diff > 0; --k) {
                        val[k] = (char)(min(diff, 9) + '0'), diff = max(diff - 9, 0);
                    }
                    break;
                }
                pre -= val[j] - '0';
            }
            if (val[0] == '0') val = val.substr(1);
        }
        num.eb(x, val);
    }
    
    for (auto &ans : num | views::drop(1)) cout << ans.Y << "\n";
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
