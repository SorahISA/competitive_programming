#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

vector<int> Solve(int N) {
    vector<int> id(N); iota(ALL(id), 0);
    
    function<void(int, int)> recur = [&](int L, int R) {
        if (L == R) return;
        int M = (L + R) >> 1;
        recur(L, M), recur(M+1, R);
        inplace_merge(begin(id) + L, begin(id) + M + 1, begin(id) + R + 1, [&](int a, int b) { return !Query(a, b); });
    };
    
    recur(0, N-1);
    
    int n = min(N, int(10));
    vector<int> win(n, 0);
    for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) {
        ++win[Query(id[i], id[j]) ? i : j];
    }
    
    int zero = 0;
    for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) {
        if (win[i] == 1 and win[j] == 1) zero = (Query(id[i], id[j]) ? i : j);
    }
    reverse(begin(id), begin(id) + zero + 1);
    
    for (int lst = zero, now = zero + 1; now < N; ++now) {
        if (Query(id[lst], id[now])) {
            reverse(begin(id) + lst + 1, begin(id) + now + 1);
            lst = now;
        }
    }
    
    vector<int> S(N);
    for (int i = 0; i < N; ++i) S[id[i]] = i;
    return S;
}

#else

#ifdef local
#include "C/monster.h"
#else
#include "monster.h"
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
// #define int int64
using float80 = long double;
// #define double float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

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

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) { cerr << _t << "\n"; }
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) { cerr << _t << ", ", _do(_u...); }
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif
