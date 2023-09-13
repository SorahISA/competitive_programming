#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int N, M; cin >> N >> M;
    
    priority_queue<pair<int, int>> pq;
    
    for (int i = 0, a; i < N; ++i) cin >> a, pq.emplace(a, 1);
    for (int i = 0, b, c; i < M; ++i) cin >> b >> c, pq.emplace(c, b);
    
    int sum = 0, card = 0;
    while (card < N) {
        auto [num, cnt] = pq.top(); pq.pop();
        int use = min(N - card, cnt);
        sum += use * num, card += use;
    }
    cout << sum << "\n";
    
    return 0;
}
