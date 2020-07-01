#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define ALL(x) x.begin(), x.end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0)

int32_t main() {
    fastIO();
    
    int r, c;
    cin >> r >> c;
    
    int arr[r][c];
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) cin >> arr[i][j];
    }

    int dx[] = {1, 1,  1,  0, -1, -1, -1, 0};
    int dy[] = {1, 0, -1, -1, -1,  0,  1, 1};
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (arr[i][j] < 5) continue;
            for (int dir = 0; dir < 8; ++dir) {
                if (0 <= i + dx[dir] and i + dx[dir] < r and
                    0 <= j + dy[dir] and j + dy[dir] < c) {
                    if (arr[i+dx[dir]][j+dy[dir]] >= 5) {
                        ++arr[i][j], ++arr[i+dx[dir]][j+dy[dir]];
                    }
                }
            }
        }
    }
    
    int cntall = 0, cnt1 = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (arr[i][j] != 1) continue;
            ++cntall;
            for (int dir = 0; dir < 8; ++dir) {
                if (0 <= i + dx[dir] and i + dx[dir] < r and
                    0 <= j + dy[dir] and j + dy[dir] < c) {
                    if (arr[i+dx[dir]][j+dy[dir]] == 5) {++cnt1; break;}
                }
            }
        }
    }
    
    cout << cnt1 << " " << cntall - cnt1 << "\n";
    
    return 0;
}
