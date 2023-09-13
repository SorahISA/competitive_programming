#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

int match(const string &S, const string &T) {
    int res = 0;
    for (int i = 0; i < 8; ++i) res += (S[i] == T[i]);
    return res;
}

int guess(const auto &valid, string ges) {
    if (SZ(valid) == 1 and valid[0] == ges) return 0;
    vector<int> ans(9, 0);
    for (const string &str : valid) ++ans[match(str, ges)];
    return *max_element(ALL(ans));
}

string find_best(const auto &global_valid, const auto &valid) {
    string ges;
    for (int min_worse = SZ(valid) + 1; const string &str : global_valid) {
        int res = guess(valid, str);
        if (chmin(min_worse, res)) ges = str;
    }
    return ges;
}

void reduce(auto &valid, string ges, int res) {
    vector<string> _valid;
    for (string &str : valid) {
        if (match(str, ges) == res) _valid.eb(str);
    }
    valid.swap(_valid);
}

// void solve(const vector<string> &global_valid, vector<string> valid, string ans) {
void solve(const vector<string> &global_valid, vector<string> valid) {
    vector<int> candidate;
    for (int i = 1; i <= 10; ++i) {
        string ges = find_best(global_valid, valid);
        // debug(ans, SZ(ges), ges);
        
        cout << ges << "\n" << flush;
        // int res = match(ges, ans);
        int res; cin >> res;
        reduce(valid, ges, res);
        candidate.eb(SZ(valid));
        
        if (res == 8) {
            // debug(ans, i, candidate);
            return;
        }
        
        // debug(ans, res);
        // debug(ans, i, candidate);
        // debug(valid);
    }
    // debug(ans, candidate);
}

vector<string> init() {
    string white = "BBKNNQRR";
    
    vector<string> valid;
    do {
        int chk_n = 0, pos_r1 = -1, pos_r2 = -1, pos_k = -1;
        for (int i = 0; i < 8; ++i) {
            if (white[i] == 'B') chk_n ^= i;
            if (white[i] == 'K') pos_k = i;
            if (white[i] == 'R') {
                if (pos_r1 == -1) pos_r1 = i;
                else              pos_r2 = i;
            }
        }
        if ((chk_n & 1) and pos_r1 < pos_k and pos_k < pos_r2) valid.eb(white);
    } while (next_permutation(ALL(white)));
    
    // debug(SZ(valid));
    return valid;
}

int32_t main() {
    fastIO();
    auto valid = init();
    
    // for (string ans : valid) solve(valid, valid, ans);
    // solve(valid, valid, "RNQNBKRB"s);
    
    string str;
    while (cin >> str and str != "END") {
        int game; cin >> game;
        // debug(game);
        solve(valid, valid);
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

#endif
