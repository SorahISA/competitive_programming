#include "dango3.h"
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int int64_t
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ef push_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    cerr << "\u001b[33m" << "At [" << __FUNCTION__ << "], line " << __LINE__ << ": ",\
    cerr << "(" << #__VA_ARGS__ << ") = ", _do(__VA_ARGS__), cerr << "\u001b[0m"
template <typename T> ostream& operator << (ostream &os, vector<T> &_vec) {
    os << "[";
    for (int flag = 0; const T &x : _vec) {
        if (flag) os << ", ";
        os << x, flag = 1;
    }
    os << "]";
    return os;
}
template <typename T> ostream& operator << (ostream &os, set<T> &_st) {
    os << "{";
    for (int flag = 0; const T &x : _st) {
        if (flag) os << ", ";
        os << x, flag = 1;
    }
    os << "}";
    return os;
}
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

/**
 *  int Query(vector<int> x);
 *  void Answer(vector<int> a); // |a| = N
**/

namespace {

const int maxn = 400 + 3;
const int maxm = 25 + 3;

int N, M, c_mx;
vector<int> tp[maxm], Q;
bitset<maxn * maxm> st;

}

void Solve(int _N, int _M) {
    N = _N, M = _M;
    tp[1].eb(1), c_mx = 1;
    
    for (int i = 2; i <= N*M; ++i) {
        int lo = 1, hi = c_mx+1, mi, ret;
        while (lo < hi) {
            mi = (lo + hi) >> 1;
            st.set(), st[i] = 0, Q.clear();
            for (int cnt = 1; cnt <= mi; ++cnt) for (int &x : tp[cnt]) st[x] = 0;
            for (int j = 1; j <= N*M; ++j) if (st[j]) Q.eb(j);
            ret = Query(Q);
            // debug(i, mi, ret, Q);
            if (ret == M-mi) hi = mi;
            else             lo = mi + 1;
        }
        chmax(c_mx, lo);
        tp[lo].eb(i);
    }
    
    // for (int cnt = 1; cnt <= M; ++cnt) debug(cnt, tp[cnt]);
    
    for (int cnt = 1; cnt <= M; ++cnt) Answer(tp[cnt]);
}
