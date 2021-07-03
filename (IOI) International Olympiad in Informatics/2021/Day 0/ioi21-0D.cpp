#include "gift.h"
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
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<pii> merge_overlap(vector<pii> &vec) {
    sort(ALL(vec));
    vector<pii> ret;
    int L = vec.front().X, maxR = vec.front().Y;
    for (auto [l, r] : vec) {
        if (l <= maxR) maxR = max(maxR, r);
        else ret.eb(L, maxR), tie(L, maxR) = tie(l, r);
    }
    ret.eb(L, maxR);
    return ret;
}

int construct(int N, int R, vector<int> A, vector<int> B, vector<int> X) {
    
    vector<pii> identical;
    for (int i = 0; i < N; ++i) identical.eb(i, i);
    for (int i = 0; i < R; ++i) {
        if (X[i] == 1) identical.eb(A[i], B[i]);
    }
    identical = merge_overlap(identical);
    
    string str(N, ' ');
    for (int i = 0; i < identical.size(); ++i) {
        // cerr << identical[i].X << " " << identical[i].Y << "\n";
        for (int j = identical[i].X; j <= identical[i].Y; ++j) str[j] = "RB"[i & 1];
    }
    
    vector<int> pre_cntB(N+1, 0);
    for (int i = 0; i < N; ++i) {
        pre_cntB[i+1] = pre_cntB[i] + (str[i] == 'B');
    }
    
    for (int i = 0; i < R; ++i) {
        if (X[i] == 2) {
            if (pre_cntB[B[i]+1] - pre_cntB[A[i]] == B[i] - A[i] + 1 or
                pre_cntB[B[i]+1] - pre_cntB[A[i]] == 0) {
                return 0;
            }
        }
    }
    
    return craft(str), 1;
}
