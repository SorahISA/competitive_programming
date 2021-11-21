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
    int N, K; cin >> N >> K;
    
    vector<int> v(N), cnt(N+1, 0);
    for (int &x : v) cin >> x;
    sort(ALL(v));
    
    auto LNDS = [=](vector<int> &vec) {
        int len = 1;
        vector<int> lnds(N, 0);
        lnds[0] = vec[0];
        for (int i = 1; i < N; ++i) {
            int p = upper_bound(begin(lnds), begin(lnds) + len, vec[i]) - begin(lnds);
            lnds[p] = vec[i], chmax(len, p + 1);
        }
        return len;
    };
    
    for (int i = N-1, max_app = 0; i >= 0; --i) {
        chmax(max_app, ++cnt[v[i]]);
        if (i + max_app == K) {
            vector<int> ans(begin(v), begin(v) + i), left(begin(v) + i, end(v));
            while (SZ(ans) < N) {
                for (int j = 0; j < SZ(left); ++j) {
                    vector<int> tmp = ans;
                    tmp.eb(left[j]);
                    for (int k = SZ(left)-1; k >= 0; --k) {
                        if (j != k) tmp.eb(left[k]);
                    }
                    if (LNDS(tmp) == K) {
                        ans.eb(left[j]);
                        left.erase(begin(left) + j);
                        break;
                    }
                }
            }
            cout << ans << "\n";
            return;
        }
    }
    
    cout << -1 << "\n";
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
