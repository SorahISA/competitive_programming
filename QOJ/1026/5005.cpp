#include <bits/stdc++.h>
using namespace std;

#define int int64_t
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define ALL(x) begin(x), end(x)
#define SZ(x) ((int)(x).size())
#define eb emplace_back
#define ee emplace

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int INF = 0x3f3f3f3f3f3f3f3f;
const int maxn = 1005;

void solve() {
    int N, M; cin >> N >> M;
    
    vector<int> A(2*N), B(2*N);
    for (int i = 0; i < N; ++i) cin >> A[i], A[i+N] = A[i];
    for (int i = 0; i < N; ++i) cin >> B[i], B[i+N] = B[i];
    
    int max_ans = 0;
    for (int len = 1; len <= N; ++len) {
        for (int L = 1, R = len; R < 2*N; ++L, ++R) {
            int mv = min(abs(N-L), abs(N-R)) + (len - 1);
            
            int ans = 0;
            Prior<pii> pq;
            for (int i = L; i <= R; ++i) pq.ee(A[i], B[i]);
            for (int i = 0; i < M-mv; ++i) {
                if (pq.top().first <= 0) break;
                ans += pq.top().first;
                pq.ee(pq.top().first - pq.top().second, pq.top().second);
                pq.pop();
            }
            chmax(max_ans, ans);
        }
    }
    cout << max_ans << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve();
    }
    
    return 0;
}
