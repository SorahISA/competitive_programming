#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define __int128 int64_t
#define __int128_t int64_t
#define __uint128_t uint64_t
#include <atcoder/modint>
using namespace atcoder;
#undef __int128
#undef __int128_t
#undef __uint128_t

using mint = modint1000000007;

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
#define pf pop_front
#define pb pop_back
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

template<typename T>
bool chmin(T &lhs, T rhs) {return lhs <= rhs ? 0 : (lhs = rhs, 1);}

template<typename T>
bool chmax(T &lhs, T rhs) {return lhs >= rhs ? 0 : (lhs = rhs, 1);}

void solve() {
    int N; cin >> N;
    string W; cin >> W;
    
    mint S = 0, D = 0, C = 0;
    mint fst, lst, now = 0, len = 0;
    char fst_tp = '.', lst_tp = '.';
    
    /**
     * S: sum of L*R
     * D: sum of R-L
     * C: numbers of range
     * fst, fst_tp: the place and type of first 'O' or 'X'
     * lst, lst_tp: the place and type of last 'O' or 'X'
     * now: now length
     * len: total length
    **/
    
    for (auto c : W) {
        if (c == '.') len *= 2;
        else          len += 1;
    }
    
    for (auto c : W) {
        if (c == '.') {
            /// duplicate another range but shift by now ///
            if (fst_tp == lst_tp) {
                S = 2 * S + now * D - now * now * C;
                D = 2 * D - 2 * now * C;
                C = 2 * C;
            }
            else {
                /// add a range of [lst, fst+now] ///
                S = 2 * S + now * D - now * now * C + (len - (fst + now)) * (lst + 1);
                D = 2 * D - 2 * now * C + (len - (fst + now)) - (lst + 1);
                C = 2 * C + 1;
            }
            if (lst_tp != '.') lst += now;
            now *= 2;
        }
        else {
            if (c == 'O' or c == 'X') {
                if (lst_tp != '.' and c != lst_tp) {
                    /// add a range of [lst, now] ///
                    S = S + (len - now) * (lst + 1);
                    D = D + (len - now) - (lst + 1);
                    C = C + 1;
                }
                if (fst_tp == '.') fst_tp = c, fst = now;
                lst_tp = c, lst = now;
            }
            now += 1;
        }
        // cout << now.val() << " " << S.val() << " " << D.val() << " " << C.val() << "\n";
    }
    
    cout << S.val() << "\n";
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