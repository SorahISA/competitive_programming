#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

int Count(const string &S, const string &T) {
    if (SZ(T) == 1) return count(ALL(S), T[0]);
    int cnt = 0;
    for (int i = 0; i <= SZ(S)-SZ(T); ++i) {
        if (S.substr(i, SZ(T)) == T) ++cnt;
    }
    return cnt;
}

int solve0(string S) {
    if (Count(S, "0")) return -1;
    return 0;
}

int solve00(string S) {
    if (Count(S, "0") > Count(S, "1") + 1) return -1;
    return Count(S, "00");
}

int solve01(string S) {
    return (S.front() == '0') + (S.back() == '1') + Count(S, "10") - 1;
}

int solve000(string S) {
    if (Count(S, "0") > Count(S, "1") * 2 + 2) return -1;
    int ans = 0, n_adj = 0, n_single = 0, n_even = 0;
    S += "1";
    for (int i = 0, lst = -1; i < SZ(S); ++i) {
        if (S[i] == '1') {
            ans += (i - lst - 2) / 2;
                 if (i - lst - 1 == 0) ++n_adj;
            else if (i - lst - 1 == 1) ++n_single;
            else                       n_even += (i - lst - 1) / 2 - 1;
            lst = i;
        }
    }
    return ans + min(max(n_even - n_adj, int(0)), n_single);
}

int solve001(string S) {
    return Count(S, "001");
}

int solve010(string S) {
    return (Count(S, "010") + 1) / 2;
}

void solve() {
    string S; cin >> S;
    string T; cin >> T;
    
    auto flip = [&]() { for (char &c : S) c ^= 1; };
    auto rev  = [&]() { reverse(ALL(S)); };
    
    int ans = 0;
    if (T ==   "0")                ans = solve0(S);
    if (T ==   "1") flip(),        ans = solve0(S);
    if (T ==  "00")                ans = solve00(S);
    if (T ==  "01")                ans = solve01(S);
    if (T ==  "10")         rev(), ans = solve01(S);
    if (T ==  "11") flip(),        ans = solve00(S);
    if (T == "000")                ans = solve000(S);
    if (T == "001")                ans = solve001(S);
    if (T == "010")                ans = solve010(S);
    if (T == "011") flip(), rev(), ans = solve001(S);
    if (T == "100")         rev(), ans = solve001(S);
    if (T == "101") flip(),        ans = solve010(S);
    if (T == "110") flip(),        ans = solve001(S);
    if (T == "111") flip(),        ans = solve000(S);
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
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

using i64 = long long;
#define int i64
using f80 = long double;
#define double f80
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
