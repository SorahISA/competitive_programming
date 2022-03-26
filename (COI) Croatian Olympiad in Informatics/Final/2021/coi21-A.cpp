// #pragma GCC optimize("Ofast", "unroll-loops")
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

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int INF = INT_MAX;

struct People {
    int l, t, r;
    
    friend istream& operator >> (istream &is, People &people) {
        is >> people.l >> people.t >> people.r;
        return is;
    }
};

void solve() {
    int N, K, X; cin >> N >> K >> X;
    
    vector<People> people(N);
    // vector<int> cnt(1005, 0), sum(1005, 0);
    map<int, pii> cnt;
    for (auto &p : people) {
        cin >> p, ++cnt[p.l].X, --cnt[p.r+1].X;
        ++cnt[p.l+p.t].Y, --cnt[p.r+1].Y;
    }
    
    // partial_sum(ALL(cnt), begin(cnt));
    vector<pair<int, pii>> precnt(1, {0, {0, 0}});
    for (auto &[key, val] : cnt) precnt.eb(key, pii{precnt.back().Y.X + val.X, precnt.back().Y.Y + val.Y});
    for (auto &[key, val] : precnt) if (val.X < K) val.Y = 0;
    
    vector<pair<pii, int>> val;
    for (int i = 1; i < precnt.size()-1; ++i) {
        if (precnt[i].Y.Y) val.eb(pii{precnt[i].X, precnt[i+1].X-1}, precnt[i].Y.Y);
    }
    
    int ans = 0;
    for (int L = val[0].X.X, R = val[0].X.Y, tokL = 0, tokR = 0, sum = 0; tokR < val.size(); R = val[++tokR].X.Y) {
        sum += (val[tokR].X.Y - val[tokR].X.X + 1) * val[tokR].Y;
        while (L <= R - X) {
            if (val[tokL].X.Y > R - X) {
                sum -= ((R - X + 1) - L) * val[tokL].Y;
                L = R - X + 1;
            }
            else {
                sum -= (val[tokL].X.Y - L + 1) * val[tokL].Y;
                L = val[++tokL].X.X;
            }
        }
        // cout << sum << "\n";
        ans = max(ans, sum);
    }
    cout << ans << "\n";
    
    // cout << cnt << "\n";
    // cout << precnt << "\n";
    // cout << val << "\n";
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