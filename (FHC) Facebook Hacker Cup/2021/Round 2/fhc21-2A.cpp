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

template<typename T>
bool chmin(T &lhs, T rhs) {return lhs <= rhs ? 0 : (lhs = rhs, 1);}

template<typename T>
bool chmax(T &lhs, T rhs) {return lhs >= rhs ? 0 : (lhs = rhs, 1);}

vector<vector<int>> dress;

void solve() {
    int N, M; cin >> N >> M;
    
    dress.assign(N+1, vector<int>(M));
    for (auto &vec : dress) for (auto &x : vec) cin >> x;
    
    int match = 0;
    map<int, int> change, now_cnt, nxt_cnt;
    for (auto x : dress[0]) ++now_cnt[x];
    for (int i = 0; i < N; ++i) {
        // cout << i << ": " << SZ(now_cnt) << "\n";
        for (auto x : dress[i+1]) ++nxt_cnt[x];
        for (auto [id, val] : now_cnt) {
            if (nxt_cnt.count(id)) {
                match += min(val, nxt_cnt[id]);
                change[id] += max(val - nxt_cnt[id], (int)0);
            }
            else {
                change[id] += val;
            }
        }
        swap(now_cnt, nxt_cnt);
        map<int, int>().swap(nxt_cnt);
    }
    // cout << match << "\n";
    
    int no_change = 0;
    for (auto x : dress[0]) ++nxt_cnt[x];
    for (auto [id, val] : nxt_cnt) {
        no_change += max(val - change[id], (int)0);
    }
    
    cout << N * M - match - M + no_change << "\n";
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
