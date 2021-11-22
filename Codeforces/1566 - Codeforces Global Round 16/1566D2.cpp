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
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

template<typename T>
bool chmin(T &lhs, T rhs) {return lhs <= rhs ? 0 : (lhs = rhs, 1);}

template<typename T>
bool chmax(T &lhs, T rhs) {return lhs >= rhs ? 0 : (lhs = rhs, 1);}

const int INF = INT_MAX;

void solve() {
    int N, M; cin >> N >> M;
    
    vector<int> A(N * M);
    for (auto &x : A) cin >> x;
    
    vector<int> sorted_A = A;
    sort(ALL(sorted_A));
    
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int max_val = sorted_A[(i+1)*M-1];
        deque<int> choose, choose_max;
        for (int j = 0; j < N*M; ++j) {
            if (A[j] <  max_val) choose.eb(j);
            if (A[j] == max_val) choose_max.eb(j);
            if (choose.size() + choose_max.size() > M) choose_max.pop_back();
        }
        for (auto x : choose_max) choose.eb(x);
        sort(ALL(choose));
        for (int j = 0; j < M; ++j) {
            for (int k = j+1; k < M; ++k) {
                if (A[choose[j]] < A[choose[k]]) ++ans;
            }
        }
        for (auto x : choose) A[x] = INF;
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}