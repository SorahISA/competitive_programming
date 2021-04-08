#pragma GCC optimize("Ofast", "unroll-loops")
#include "Anna.h"
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

namespace {

int used[15], minUnused = 1;

int check(int nx, int ny, int gx, int gy) {
    if (abs(nx - gx) <= 1 and abs(ny - gy) <= 1) {
        int val = 3 * (gx-nx+1) + (gy-ny+1) + 1;
        return val;
    }
    if (ny+1 < gy) return 10;
    if (gy < ny-1) return 11;
    if (nx+1 < gx) return 12;
    if (gx < nx-1) return 13;
}

} // namespace

void Anna(int N, int K, vector<int> R, vector<int> C) {
    vector<vector<int>> flag;
    for (int k = 0; k < 9; ++k) {
        flag.assign(N, vector<int>(N, 0));
        memset(used, 0x00, sizeof(used)), minUnused = 1;
        
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                int p = 3 * ((r+k/3) % 3) + ((c+k%3) % 3);
                if (p == 0) flag[r][c] = 14;
                if (1 <= p and p <= 7) flag[r][c] = check(r, c, R[p-1], C[p-1]);
                if (1 <= flag[r][c] and flag[r][c] <= 9) {
                    used[flag[r][c]] = 1;
                    // cerr << "(" << r << "," << c << "): " << flag[r][c] << "\n";
                }
            }
        }
        
        if (used[9]) continue; /// main difference from L = 13
        else {
            while (used[minUnused]) ++minUnused;
            // cerr << "minUnused:  " << minUnused << "\n";
            break;
        }
    }
    
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) flag[r][c] = flag[r][c] ? flag[r][c] : minUnused;
    }
    
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (flag[r][c] >= 10) --flag[r][c];
            if (flag[r][c] > minUnused) --flag[r][c];
            SetFlag(r, c, flag[r][c]);
        }
    }
    
    // for (int r = 0; r < N; ++r) {
        // for (int c = 0; c < N; ++c) cerr << flag[r][c] << " \n"[c == N-1];
    // }
}

/*
11
100 7 45 45 55 55 65 65 37 29 48 16 45 44 46 45 55 65
100 7 45 45 55 55 65 65 37 29 48 16 45 44 46 45 65 55
100 7 45 45 55 55 65 65 37 29 48 16 45 44 46 45 45 55
100 7 45 45 55 55 65 65 37 29 48 16 45 44 46 45 55 45
100 7 45 45 55 55 65 65 37 29 48 16 45 44 46 45 45 64
100 7 45 45 55 55 65 65 37 29 48 16 45 44 46 45 45 65
100 7 45 45 55 55 65 65 37 29 48 16 45 44 46 45 65 45
100 7 45 45 55 55 65 65 37 29 48 16 45 44 46 45 45 54
100 7 45 45 55 55 65 65 37 29 48 16 45 44 46 45 54 45
100 7 45 45 55 55 65 65 37 29 48 16 45 44 46 45  1 98
100 7 39 48 67 19 35 29 88 60 95 12 47 71  3 86 24 19
*/