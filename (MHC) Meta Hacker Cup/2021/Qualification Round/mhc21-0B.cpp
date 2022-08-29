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

void solve() {
    int N; cin >> N;
    
    vector<string> state(N);
    for (auto &str : state) cin >> str;
    
    int min_cost = N+1, min_cnt = 0;
    
    for (int i = 0; i < N; ++i) {
        int flag = 1, cost = 0;
        for (int j = 0; j < N; ++j) {
            if (state[i][j] == 'O') flag = 0;
            if (state[i][j] == '.') ++cost;
        }
        if (flag) {
            if (cost < min_cost) min_cost = cost, min_cnt = 1;
            else if (cost == min_cost) ++min_cnt;
        }
    }
    
    for (int i = 0; i < N; ++i) {
        int flag = 1, cost = 0;
        for (int j = 0; j < N; ++j) {
            if (state[j][i] == 'O') flag = 0;
            if (state[j][i] == '.') ++cost;
        }
        if (flag) {
            if (cost < min_cost) min_cost = cost, min_cnt = 1;
            else if (cost == min_cost) ++min_cnt;
        }
    }
    
    if (min_cnt == 0) return cout << "Impossible\n", void();
    
    if (min_cost == 1) {
        vector<int> cnt_h_x(N, 0), cnt_v_x(N, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (state[i][j] == 'X') ++cnt_h_x[i], ++cnt_v_x[j];
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (state[i][j] == '.' and cnt_h_x[i] == N-1 and cnt_v_x[j] == N-1) --min_cnt;
            }
        }
    }
    
    cout << min_cost << " " << min_cnt << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}