#include <bits/stdc++.h>
using namespace std;

#define int int64_t
using pii = pair<int, int>;

#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#endif

void solve() {
    int N; cin >> N;
    
    vector<int> stone(N);
    for (int &x : stone) cin >> x;
    
    while ((N & 1) and count_if(ALL(stone), [](int x) {return ~x & 1;}) == N) {
        for (int &x : stone) x /= 2;
    }
    
    cout << (count_if(ALL(stone), [](int x) {return x & 1;}) == N ? 0 : 1) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) solve();
    
    return 0;
}
