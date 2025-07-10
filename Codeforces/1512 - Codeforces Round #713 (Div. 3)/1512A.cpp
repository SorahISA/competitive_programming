#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N; cin >> N;
    
    vector<int> A(N);
    for (int &x : A) cin >> x;
    
    int mode = (A[0] == A[1] or A[0] == A[2] ? A[0] : A[1]);
    for (int i = 0; i < N; ++i) {
        if (A[i] != mode) { cout << i+1 << "\n"; return; }
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
