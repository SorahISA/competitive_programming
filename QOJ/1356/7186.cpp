#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const int L = 50;
int miss = 0;

int flip(int pos) {
    cout << pos << "\n" << flush;
    string res; cin >> res;
    if (res == "##") exit(0);
    miss += (res[1] == '-');
    return res[0] - 'A';
}

string prepare(string S) {
    string res(L, '?');
    vector<int> app(L/2, 0);
    for (int i = 0; i < L; ++i) {
        res[i] = app[S[i]-'A'] + '0';
        ++app[S[i]-'A'];
    }
    return res;
}

void play(string S) {
    vector<int> A, B;
    for (int i = 0; i < L; ++i) (S[i] == '0' ? A : B).eb(i+1);
    // debug(A);
    // debug(B);
    
    vector<int> know_A(L/2, 0);
    for (int i = 0; i < L/2; i += 2) {
        int ans_A1 = flip(A[i]);
        know_A[ans_A1] = A[i];
        int ans_A2 = flip(A[(i+1)%(L/2)]);
        know_A[ans_A2] = A[(i+1)%(L/2)];
    }
    
    for (int i = 0; i < L/2; ++i) {
        int ans_B = flip(B[i]);
        flip(know_A[ans_B]);
    }
}

int32_t main() {
    fastIO();
    
    string op; cin >> op;
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        string S; cin >> S;
        if (op == "prepare") cout << prepare(S) << "\n" << flush;
        if (op == "play")    play(S);
    }
    // debug(miss);
    
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

#endif
