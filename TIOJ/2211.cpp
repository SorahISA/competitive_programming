#ifndef local
#include "lib2211.h"
#endif

#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

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
#define ef push_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) (int)(x).size()
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

#ifdef local

int Init() {
    int N; cin >> N;
    return N;
}

int Query(int a, int b) {
    int ret; cin >> ret;
    return ret;
}

void Report(int a) {
    cout << "ANS: " << a << "\n";
}

#endif

void solve() {
    int N = Init(), sq_N = ceil(sqrt(N));
    
    if (N <= 800) {
        for (int i = 1; i <= N; ++i) {
            if (Query(i, 1) == 1) return Report(i);
        }
    }
    
    vector<int> val{1};
    for (int i = 1; i <= sq_N; ++i) val.eb(Query(1, i));
    
    for (int i = 1; i <= sq_N; ++i) {
        if (val[i] == 1) return Report(val[i-1]);
    }
    
    for (int i = 1; i <= sq_N; ++i) {
        int jump = min(i * sq_N, N), qry = Query(val[1], jump);
        for (int j = 1; j <= sq_N; ++j) {
            /// check if f^{j}(x) = f^{jump+1}(x) ///
            if (val[j] == qry) return Report(Query(1, jump - j));
        }
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
