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

const int maxn = 20 + 1;

bitset<maxn> state[maxn];
int p[maxn*maxn], sz[maxn*maxn];

int Find(int x) {return x ^ p[x] ? p[x] = Find(p[x]) : x;}

void Union(int r1, int c1, int r2, int c2) {
    int p1 = Find(r1*maxn + c1), p2 = Find(r2*maxn + c2);
    if (p1 == p2) return;
    if (sz[p1] > sz[p2]) swap(p1, p2);
    sz[p2] += sz[p1], p[p1] = p2;
}

void solve() {
    int R, C; cin >> R >> C;
    
    vector<string> A(R, string(C, ' '));
    for (auto &str : A) cin >> str;
    
    vector<int> types;
    for (int tp = 0; tp < (1<<4); ++tp) {
        int fl = 0;
        for (int i = 0; i < R-1; ++i) {
            for (int j = 0; j < C-1; ++j) {
                if (A[i+1][j+1] == "BW"[tp >> 0 & 1] and
                    A[i+1][j]   == "BW"[tp >> 1 & 1] and
                    A[i][j+1]   == "BW"[tp >> 2 & 1] and
                    A[i][j]     == "BW"[tp >> 3 & 1]) {
                    fl = 1;
                }
            }
        }
        for (int i = 0; i < R-1; ++i) {
            for (int j = 0; j < C; ++j) {
                if (A[i+1][j] == "BW"[tp >> 0 & 1] and
                    A[i+1][j] == "BW"[tp >> 1 & 1] and
                    A[i][j]   == "BW"[tp >> 2 & 1] and
                    A[i][j]   == "BW"[tp >> 3 & 1]) {
                    fl = 1;
                }
            }
        }
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C-1; ++j) {
                if (A[i][j+1] == "BW"[tp >> 0 & 1] and
                    A[i][j]   == "BW"[tp >> 1 & 1] and
                    A[i][j+1] == "BW"[tp >> 2 & 1] and
                    A[i][j]   == "BW"[tp >> 3 & 1]) {
                    fl = 1;
                }
            }
        }
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (A[i][j] == "BW"[tp >> 0 & 1] and
                    A[i][j] == "BW"[tp >> 1 & 1] and
                    A[i][j] == "BW"[tp >> 2 & 1] and
                    A[i][j] == "BW"[tp >> 3 & 1]) {
                    fl = 1;
                }
            }
        }
        if (fl) types.eb(tp);
    }
    
    int ans = 1;
    for (int cutR = 0; cutR <= R; ++cutR) {
        for (int cutC = 0; cutC <= C; ++cutC) {
            for (int tp : types) {
                for (int i = 0; i < maxn; ++i) state[i].reset();
                fill(sz, sz + maxn*maxn, 1), iota(p, p + maxn*maxn, 0);
                
                for (int i = 0; i < R; ++i) {
                    for (int j = 0; j < C; ++j) {
                        if (i >= cutR and j >= cutC) state[i][j] = A[i][j] == "BW"[tp >> 0 & 1];
                        if (i >= cutR and j <  cutC) state[i][j] = A[i][j] == "BW"[tp >> 1 & 1];
                        if (i <  cutR and j >= cutC) state[i][j] = A[i][j] == "BW"[tp >> 2 & 1];
                        if (i <  cutR and j <  cutC) state[i][j] = A[i][j] == "BW"[tp >> 3 & 1];
                    }
                }
                
                // if (cutR == 2 and cutC == 2 and tp == 6) {
                    // cout << "=== TEST ===\n";
                    // for (int i = 0; i < R; ++i) {
                        // for (int j = 0; j < C; ++j) cout << state[i][j];
                        // cout << "\n";
                    // }
                // }
                
                for (int i = 0; i < R; ++i) {
                    for (int j = 0; j < C-1; ++j) {
                        if (state[i][j] & state[i][j+1]) Union(i, j, i, j+1);
                    }
                }
                for (int i = 0; i < R-1; ++i) {
                    for (int j = 0; j < C; ++j) {
                        if (state[i][j] & state[i+1][j]) Union(i, j, i+1, j);
                    }
                }
                
                ans = max(ans, *max_element(sz, sz + maxn*maxn));
            }
        }
    }
    cout << ans << "\n";
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