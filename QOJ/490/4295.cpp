#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

void solve() {
    int N; cin >> N;
    
    vector<int> A(N), B(N);
    for (int &x : A) cin >> x;
    for (int &x : B) cin >> x;
    
    int sumA = accumulate(ALL(A), int(0));
    int sumB = accumulate(ALL(B), int(0));
    
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < N; ++i) {
        if (sumB - B[i] > sumA and B[i] > sumA - A[i]) {
            return cout << "NO" << "\n", void();
        }
        else if (sumB - B[i] > sumA) {
            ++cnt1;
        }
        else if (B[i] > sumA - A[i]) {
            ++cnt2;
        }
    }
    
    if (cnt1 == N or cnt2 >= 2) cout << "NO" << "\n";
    else                        cout << "YES" << "\n";
}

signed main() {
    IOS();
    int t = 1; cin >> t;
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
// #define double __float80
using pii = pair<int, int>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)

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

// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

#endif
