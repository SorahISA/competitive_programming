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
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())
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
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

bool check_0(int N, int K, vector<int> vec) {
    return is_sorted(ALL(vec));
}

bool check_1(int N, int K, vector<int> vec) {
    int L = -1, R = N;
    for (int i = 0; i < N; ++i) {
        if (vec[i] == i) L = i;
        else break;
    }
    for (int i = N-1; i >= 0; --i) {
        if (vec[i] == i) R = i;
        else break;
    }
    return R - L - 1 <= K;
}

bool check_2(int N, int K, vector<int> vec) {
    int L = -1, R = N;
    for (int i = 0; i < N; ++i) {
        if (vec[i] == i) L = i;
        else break;
    }
    for (int i = N-1; i >= 0; --i) {
        if (vec[i] == i) R = i;
        else break;
    }
    vec = vector<int>(begin(vec) + L + 1, begin(vec) + R);
    for (int &x : vec) x -= L + 1;
    
    // cerr << "check: ";
    // for (int x : vec) cerr << x << " ";
    // cerr << "\n";
    
    vector<int> vec_LR = vec, vec_RL = vec;
    sort(begin(vec_LR), begin(vec_LR) + K), sort(end(vec_RL) - K, end(vec_RL));
    sort(end(vec_LR) - K, end(vec_LR)), sort(begin(vec_RL), begin(vec_RL) + K);
    return is_sorted(ALL(vec_LR)) or is_sorted(ALL(vec_RL));
}

void solve() {
    int N, K; cin >> N >> K;
    
    vector<int> vec(N);
    for (int &x : vec) cin >> x, --x;
    
         if (check_0(N, K, vec)) cout << 0 << "\n";
    else if (check_1(N, K, vec)) cout << 1 << "\n";
    else if (check_2(N, K, vec)) cout << 2 << "\n";
    else                         cout << 3 << "\n";
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
