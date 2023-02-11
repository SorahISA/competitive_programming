#include "art.h"
#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
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

// #define X first
// #define Y second
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
    cerr << "\u001b[33m" << "At [" << __FUNCTION__ << "], line " << __LINE__ << ", ",\
    cerr << "(" << #__VA_ARGS__ << ") = ", _do(__VA_ARGS__), cerr << "\u001b[0m"
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

/**
 *  int publish(vector<int>); /// permutation -> #inverse_pair
 *  void answer(vector<int>); /// permutation : #inverse_pair = 0
**/

void move_begin(vector<int> &vec, int p) {
    while (p > 0) swap(vec[p], vec[p-1]), --p;
}

void move_k(vector<int> &vec, int k, int p = 0) {
    while (p < k) swap(vec[p], vec[p+1]), ++p;
}

void solve(int N) {
    vector<int> A(N);
    iota(ALL(A), 1);
    
    int lst = publish(A), now, lo;
    for (int i = 1; i < N; ++i) {
        move_begin(A, i);
        now = publish(A);
        /// hi + lo = i; hi - lo = lst - now ///
        lo = (i - lst + now) / 2;
        move_k(A, lo);
        lst = now - lo;
    }
    answer(A);
}
