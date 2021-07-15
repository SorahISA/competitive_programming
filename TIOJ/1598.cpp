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
#define pb pop_back
#define pf pop_front
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

const int INF = INT_MAX;
const int maxc = 1E6;

void solve() {
    int N, B; cin >> N >> B;
    
    vector<int> arr(N);
    for (auto &x : arr) cin >> x;
    
    int lo = 0, hi = maxc, mi;
    while (lo < hi) {
        mi = lo + hi >> 1;
        int share = 0;
        for (int i = 0; i < N; ++i) {
            /**
             * first K seconds: distribute into (2^{K-1}, 2^K] peoples
             *     (let it be 2^K - p) and eat p cookies in total
             * last mi-K seconds: eat (2^K - p) * (mi - K) cookies in total
            **/
            if (arr[i] <= mi) continue;
            int min_share = INF;
            for (int j = 1; (1 << j) <= arr[i] and j < mi-1; ++j) {
                /// solve p <= \frac{2^j(mi-j) - arr_i}{mi-j-1} ///
                int up = (1 << j) * (mi - j) - arr[i];
                int dn = mi - j - 1;
                int max_p = up / dn + (up < 0 and up % dn ? -1 : 0);
                // cerr << mi << ": " << i << ": " << j << ": " << max_p << "\n";
                if (max_p < 0 or max_p >= (1 << j-1)) continue;
                min_share = min(min_share, (1 << j) - max_p - 1);
            }
            share += min_share;
            // cerr << "==> " << mi << ": " << i << ": " << min_share << "\n";
        }
        // cerr << "==> ==> " << mi << ": " << share << "\n";
        if (share <= B) hi = mi;
        else            lo = mi + 1;
    }
    cout << lo << "\n";
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