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
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

struct Candidates {
    int A, B, C, D, E;
    
    Candidates(int _A = 0, int _B = 0, int _C = 0, int _D = 0, int _E = 0) :
        A(_A), B(_B), C(_C), D(_D), E(_E) {}
    
    friend istream& operator >> (istream &is, Candidates &cand) {
        is >> cand.A >> cand.B >> cand.C >> cand.D >> cand.E;
        return is;
    }
};

void solve() {
    int N; cin >> N;
    
    vector<Candidates> cand(N);
    for (auto &x : cand) cin >> x;
    
    int lo = 1, hi = 1E9, mi, fl;
    while (lo < hi) {
        mi = lo + hi + 1 >> 1, fl = 0;
        
        vector<int> cnt(1<<5, 0);
        for (int i = 0; i < N; ++i) {
            cnt[((cand[i].A >= mi) << 4) | ((cand[i].B >= mi) << 3) | ((cand[i].C >= mi) << 2)
                                         | ((cand[i].D >= mi) << 1) | ((cand[i].E >= mi) << 0)] = 1;
        }
        
        for (int i = 0; i < 1<<5; ++i) {
            for (int j = i; j < 1<<5; ++j) {
                for (int k = j; k < 1<<5; ++k) {
                    if ((i | j | k) != 0b11111) continue;
                    fl |= cnt[i] & cnt[j] & cnt[k];
                }
            }
        }
        
        if (fl) lo = mi;
        else hi = mi - 1;
    }
    cout << lo << "\n";
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