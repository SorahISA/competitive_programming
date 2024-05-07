#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int INF = LLONG_MAX >> 2;

void solve() {
    int N; cin >> N;
    string S; cin >> S;
    int A, B, C; cin >> A >> B >> C;
    
    if (N <= 2) { cout << min(A, B) * N << "\n"; return; }
    
    auto calc = [&](string T) -> int {
        // debug(T);
        int n = SZ(T), cost = 0, L = 0, R = n;
        if (A <= B) {
            for (int i = 0, cost_remove = 0, cost_change = 0; i < R; i += 3) {
                cost_remove += 3 * A;
                cost_change += ((T[i] != 'R') + (T[i+1] != 'G') + (T[i+2] != 'B')) * C;
                if (cost_remove < cost_change) cost += cost_remove, cost_remove = 0, cost_change = 0, L = i+3;
            }
            for (int i = n, cost_remove = 0, cost_change = 0; i > L; i -= 3) {
                cost_remove += 3 * B;
                cost_change += ((T[i-3] != 'R') + (T[i-2] != 'G') + (T[i-1] != 'B')) * C;
                if (cost_remove < cost_change) cost += cost_remove, cost_remove = 0, cost_change = 0, R = i-3;
            }
        }
        else {
            for (int i = n, cost_remove = 0, cost_change = 0; i > L; i -= 3) {
                cost_remove += 3 * B;
                cost_change += ((T[i-3] != 'R') + (T[i-2] != 'G') + (T[i-1] != 'B')) * C;
                if (cost_remove < cost_change) cost += cost_remove, cost_remove = 0, cost_change = 0, R = i-3;
            }
            for (int i = 0, cost_remove = 0, cost_change = 0; i < R; i += 3) {
                cost_remove += 3 * A;
                cost_change += ((T[i] != 'R') + (T[i+1] != 'G') + (T[i+2] != 'B')) * C;
                if (cost_remove < cost_change) cost += cost_remove, cost_remove = 0, cost_change = 0, L = i+3;
            }
        }
        for (int i = L; i < R; i += 3) {
            cost += ((T[i] != 'R') + (T[i+1] != 'G') + (T[i+2] != 'B')) * C;
        }
        return cost;
    };
    
    int ans = INF;
    chmin(ans, 0 * A + ((N-0)%3) * B + calc(S.substr(0, (N-0)/3*3)));
    chmin(ans, 1 * A + ((N-1)%3) * B + calc(S.substr(1, (N-1)/3*3)));
    chmin(ans, 2 * A + ((N-2)%3) * B + calc(S.substr(2, (N-2)/3*3)));
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
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
#define int int64
using float80 = long double;
#define double float80
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
