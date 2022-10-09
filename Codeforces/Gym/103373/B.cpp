#include <bits/stdc++.h>
using namespace std;

#define int long long

#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int N; cin >> N;
    
    int sum = 0;
    for (int i = 1; i*i <= N; ++i) {
        if (N % i == 0) {
            sum += i;
            if (i * i != N) sum += N / i;
        }
    }
    sum -= N;
    
         if (sum >  N) cout << "abundant\n";
    else if (sum == N) cout << "perfect\n";
    else               cout << "deficient\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}