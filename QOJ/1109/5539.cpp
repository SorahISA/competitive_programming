#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

void solve() {
    int N, M; cin >> N >> M;
    
    vector<pair<int, string>> con(N);
    for (auto &[x, t] : con) cin >> x >> t, --x;
    
    set<string> valid;
    for (int ban = -1; ban < N; ++ban) {
        string ans(M, '?');
        for (int i = 0; i < N; ++i) {
            if (i == ban) continue;
            auto &[x, t] = con[i];
            ans.replace(begin(ans) + x, begin(ans) + x + SZ(t), t);
        }
        bool is_valid = true;
        for (int i = 0; i < N and is_valid; ++i) {
            if (i == ban) continue;
            auto &[x, t] = con[i];
            if (ans.substr(x, SZ(t)) != t) is_valid = false;
        }
        if (is_valid and count(ALL(ans), '?')) continue;
        if (is_valid) valid.ee(ans);
        if (SZ(valid) > 1) return cout << -2 << "\n", void();
    }
    if (SZ(valid)) cout << *begin(valid) << "\n";
    else cout << -1 << "\n";
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
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
using pii = pair<int, int>;

#define SZ(a) ((int)(a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front

#ifdef local
#define IOS() void()
#define debug(...) \
    fprintf(stderr, "%sAt [%s], line %d: (%s) = ", "\u001b[33m", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "%s", "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define debug(...) void()
#define endl '\n'
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

#endif
