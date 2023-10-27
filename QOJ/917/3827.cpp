#include <bits/stdc++.h>
using namespace std;

#ifdef local
#define fastIO() void()
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#endif

void solve() {
    int N; scanf("%d ", &N);
    
    vector<vector<array<int, 3>>> trans(N-1, vector<array<int, 3>>(3));
    for (auto &vec : trans) for (auto &[x, y, z] : vec) {
        scanf("%*c%d%*c %d%*c %d%*c ", &x, &y, &z), --x;
        // printf("::: (%d)(%d)(%d)\n", x, y, z);
    }
    
    int M; cin >> M;
    
    while (M--) {
        
        int L; cin >> L;
        
        vector<int> tape(30, 2);
        for (int i = 0; i < L; ++i) cin >> tape[i+10];
        
        int state = 0, pos = 10;
        for (int _step = 1; _step <= 10 and state != N-1; ++_step) {
            // printf("state = %d, pos = %d, tape = %d\n", state+1, pos-9, tape[pos]);
            auto [x, y, z] = trans[state][tape[pos]];
            tape[pos] = z, state = x, pos += y;
        }
        cout << (state == N-1 ? "yes" : "no") << "\n";
    }
    
}

int32_t main() {
    // fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Machine #" << _ << ":\n";
        solve();
    }
    
    return 0;
}
