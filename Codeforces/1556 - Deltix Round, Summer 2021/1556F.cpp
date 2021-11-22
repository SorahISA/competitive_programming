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

const int mod = 1E9 + 7;
const int maxn = 14 + 1;

int N;
vector<int> prob, F_ans(1 << maxn, -1);
vector<vector<int>> H(maxn, vector<int>(1 << maxn, 1));

int modinv(int x) {
    int base = x, exp = mod-2, ans = 1;
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        base = base * base % mod, exp >>= 1;
    }
    return ans;
}

void calc_H() {
    /* probability of for all t \in T, there exists x -> T */
    for (int x = 0; x < N; ++x) {
        for (int T = 1; T < 1<<N; ++T) {
            int lb = __lg(T & -T);
            H[x][T] = H[x][T^(1<<lb)] * (prob[x] * modinv(prob[x] + prob[lb]) % mod) % mod;
        }
    }
}

int G(int S, int T) {
    /* probability of for all s \in S, t \in T, there exists s -> t */
    int ans = 1;
    for (int s = 0; s < N; ++s) {
        if (~S >> s & 1) continue;
        ans = ans * H[s][T] % mod;
    }
    return ans;
}

int F(int S) {
    /* probability of s \in S forms cycle (everyone in S wins) */
    if (F_ans[S] != -1) return F_ans[S];
    int ans = 1;
    for (int U = (S-1) & S; U > 0; U = (U-1) & S) {
        ans = (ans - F(U) * G(U, S^U) % mod + mod) % mod;
    }
    return F_ans[S] = ans;
}

int P(int S) {
    /* probability of only set S wins */
    return G(S, S^((1<<N)-1)) * F(S) % mod;
}

void solve() {
    cin >> N;
    
    prob.resize(N);
    for (auto &x : prob) cin >> x;
    calc_H();
    
    int ans = 0;
    for (int S = 1; S < 1<<N; ++S) {
        ans = (ans + P(S) * __builtin_popcount(S)) % mod;
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}