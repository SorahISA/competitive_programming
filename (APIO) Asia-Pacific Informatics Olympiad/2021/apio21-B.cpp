#include "jumps.h"
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

const int INF = 1E9;
const int maxn = 1 << 18;
const int lgmx = 18;
// const int maxn = 1 << 4;
// const int lgmx = 4;

int N, sparse[lgmx][maxn], inv[maxn];
pii jump[lgmx][maxn]; /// (jump lo_edge, jump hi_edge)
pii LR[lgmx][maxn]; /// (jump left, jump right)
vector<int> H;

inline int chmin(int &x, int y) {return x <= y ? 0 : x = y, 1;}

inline int QueryMax(int L, int R) {
    int lay = __lg(R - L + 1);
    return max(sparse[lay][L], sparse[lay][R - (1<<lay) + 1]);
}

void init(int _N, vector<int> _H) {
    N = _N + 2;
    H.eb(N + 1); for (auto x : _H) H.eb(x); H.eb(N + 2);
    
    for (int i = 0; i < N; ++i) sparse[0][i] = H[i], inv[H[i]] = i;
    
    for (int lay = 1; lay < lgmx; ++lay) {
        for (int i = 0; i < N-(1<<lay)+1; ++i) {
            sparse[lay][i] = max(sparse[lay-1][i], sparse[lay-1][i+(1<<lay-1)]);
        }
    }
    
    jump[0][0] = LR[0][0] = {0, N-1}, jump[0][N-1] = LR[0][N-1] = {N-1, N-1};
    
    for (int i = 1, lo, mi, hi; i < N-1; ++i) {
        auto &jmp = jump[0][i];
        auto &lr = LR[0][i];
        
        lo = 0, hi = i;
        while (lo < hi) {
            mi = lo + hi + 1 >> 1;
            QueryMax(mi, i) > H[i] ? lo = mi : hi = mi - 1;
        }
        jmp.X = lr.X = lo;
        
        lo = i, hi = N-1;
        while (lo < hi) {
            mi = lo + hi >> 1;
            QueryMax(i, mi) > H[i] ? hi = mi : lo = mi + 1;
        }
        jmp.Y = lr.Y = lo;
        
        if (H[jmp.X] > H[jmp.Y]) swap(jmp.X, jmp.Y);
    }
    
    for (int lay = 1; lay < lgmx; ++lay) {
        for (int i = 0; i < N; ++i) {
            auto &anc = jump[lay-1][i];
            jump[lay][i].X = jump[lay-1][anc.X].X;
            jump[lay][i].Y = jump[lay-1][anc.Y].Y;
            auto &par = LR[lay-1][i];
            LR[lay][i].X = LR[lay-1][par.X].X;
            LR[lay][i].Y = LR[lay-1][par.Y].Y;
        }
    }
}

int minimum_jumps(int A, int B, int C, int D) {
    ++A, ++B, ++C, ++D;
    
    if (B + 1 == C) return LR[0][B].Y <= D ? 1 : -1;
    
    int mid = QueryMax(B+1, C-1);
    if (LR[0][inv[mid]].Y > D) return -1;
    if (H[B] > mid) return LR[0][B].Y <= D ? 1 : -1;
    
    int S, lo = A, hi = B, mi;
    while (lo < hi) {
        mi = lo + hi >> 1;
        if (QueryMax(mi, B) > mid) lo = mi + 1;
        else hi = mi;
    }
    S = inv[QueryMax(lo, B)];
    
    // cout << "start at " << S - 1 << "\n";
    
    if (A <= LR[0][S].X and LR[0][LR[0][S].X].Y <= D) return 1;
    
    int ans = 0;
    
    for (int i = lgmx-1; i >= 0; --i) {
        if (H[jump[i][S].Y] <= mid) S = jump[i][S].Y, ans += 1 << i;
    }
    
    if (H[S] == mid) return ans + 1;
    if (LR[0][LR[0][S].X].Y <= D) return ans + 2;
    
    for (int i = lgmx-1; i >= 0; --i) {
        if (LR[i][S].Y < C) S = LR[i][S].Y, ans += 1 << i;
    }
    
    return C <= LR[0][S].Y and LR[0][S].Y <= D ? ans + 1 : -1;
}
