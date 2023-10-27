#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

struct BIT {
    
    unordered_map<int, int> bit;
    int maxn, l, r, inv;
    
    BIT(int N = 0, int _l = -1, int _r = -1) {init(N, _l, _r);}
    void init(int N, int _l = -1, int _r = -1) {
        // debug("init");
        maxn = (1 << (__lg(N+1) + 1));
        l = (_l == -1 ? 1 : _l);
        r = (_r == -1 ? N : _r);
        inv = 0;
    }
    
    void add(int idx, int val) {
        while (idx < maxn) bit[idx] += val, idx += idx & -idx;
    }
    
    int sum(int idx, int ans = 0) {
        while (idx) ans += bit[idx], idx -= idx & -idx;
        return ans;
    }
};

void solve() {
    int N; cin >> N;
    
    vector<int> A(N+1);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    
    vector<BIT> BITs(1, N);
    vector<int> place(N+1, 0); place[0] = -1;
    for (int i = N; i >= 1; --i) {
        BITs[0].inv += BITs[0].sum(A[i] - 1);
        BITs[0].add(A[i], 1);
    }
    
    multiset<int> invs; invs.ee(BITs[0].inv);
    for (int q = 1; q <= N; ++q) {
        cout << *rbegin(invs) << " \n"[q == N];
        int pos; cin >> pos, pos ^= *rbegin(invs);
        int id = place[pos]; place[pos] = -1;
        // debug(pos, id);
        
        invs.erase(invs.find(BITs[id].inv));
        
        if (pos - BITs[id].l < BITs[id].r - pos) {
            /// remove from left ///
            int l = BITs[id].l;
            // debug("left", l, pos);
            if (l < pos) BITs.eb(N, l, l-1);
            for (int i = l; i <= pos; ++i) {
                BITs[id].inv -= BITs[id].sum(A[i] - 1);
                BITs[id].add(A[i], -1), ++BITs[id].l;
                if (i < pos) {
                    BITs.back().inv += BITs.back().r - BITs.back().l + 1 - BITs.back().sum(A[i]);
                    BITs.back().add(A[i], 1), ++BITs.back().r;
                    place[i] = SZ(BITs) - 1;
                }
            }
            invs.ee(BITs[id].inv);
            if (l < pos) invs.ee(BITs.back().inv);
        }
        else {
            /// remove from right ///
            int r = BITs[id].r;
            // debug("right", r, pos);
            if (pos < r) BITs.eb(N, r+1, r);
            for (int i = r; i >= pos; --i) {
                BITs[id].inv -= BITs[id].r - BITs[id].l + 1 - BITs[id].sum(A[i]);
                BITs[id].add(A[i], -1), --BITs[id].r;
                if (pos < i) {
                    BITs.back().inv += BITs.back().sum(A[i] - 1);
                    BITs.back().add(A[i], 1), --BITs.back().l;
                    place[i] = SZ(BITs) - 1;
                }
            }
            invs.ee(BITs[id].inv);
            if (pos < r) invs.ee(BITs.back().inv);
        }
        // debug(invs);
        // debug(place);
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
// #define double __float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "%sAt [%s], line %d: (%s) = ", "\u001b[33m", __FILE__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "%s", "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

template <typename T>
ostream & operator << (ostream &os, const vector<T> &vec) {
    os << "[";
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << ", ";
        os << vec[i];
    }
    os << "]";
    return os;
}

template <typename T>
ostream & operator << (ostream &os, const multiset<T> &st) {
    os << "[";
    for (int i = 0; const T &t : st) {
        if (i) os << ", ";
        os << t, ++i;
    }
    os << "]";
    return os;
}

#endif
