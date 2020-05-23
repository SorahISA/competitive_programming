// #pragma GCC target("avx2")
// #pragma GCC optimize("O3", "unroll-loops")

// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// #define int long long

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(0, INT_MAX); \
                 auto rnd = bind(__dis, __gen);

const int mod = 1E9 + 7;

bool sign1(int dir) {return dir == 1 or dir == 4;}

bool sign2(int dir) {return dir == 1 or dir == 2;}

int main() {
    fastIO();

    int n;
    cin >> n;

    vector<int> v(2 * n), pl(n);
    for (int i = 0; i < 2*n; ++i) cin >> v[i];
    for (int i = 0; i < n; ++i) cin >> pl[i];
    sort(v.begin(), v.end());

    for (int i = 0; i < 2*n; i += 2) v[i] *= -1;

    vector<pair<int, int>> ans(n);

    /// 1, 4 --> right ///
    /// 2, 3 --> left  ///

    /// 1, 2 --> up    ///
    /// 3, 4 --> down  ///

    int c1 = 0, c2 = 0;
    for (int i = 1; i < n; ++i) {
        if (sign1(pl[i]) != sign1(pl[i - 1])) ++c1;
        if (sign2(pl[i]) != sign2(pl[i - 1])) ++c2;
    }

    /// first dimension ///

    int tokL = n - c1 - 1, tokR = n - c1 - 1;

    if (sign1(pl[0]) != (v[tokL] > 0)) {
        for (int i = 0; i < n; ++i) v[i] *= -1;
    }
    ans[0].first = v[tokL];

    for (int i = 1; i < n; ++i) {
        ans[i].first = (sign1(pl[i]) == sign1(pl[i - 1])) ? v[--tokL] : v[++tokR];
    }

    // assert(tokL == 0 and tokR == n-1);

    /// second dimension ///

    tokL = 2*n - c2 - 1, tokR = 2*n - c2 - 1;

    if (sign2(pl[0]) != (v[tokL] > 0)) {
        for (int i = 0; i < n; ++i) v[n + i] *= -1;
    }
    ans[0].second = v[tokL];

    for (int i = 1; i < n; ++i) {
        ans[i].second = (sign2(pl[i]) == sign2(pl[i - 1])) ? v[--tokL] : v[++tokR];
    }

    // assert(tokL == n and tokR == 2*n-1);

    /// print answer ///

    for (int i = 0; i < n; ++i) {
        if (ans[i].first  > 0) cout << '+'; cout << ans[i].first  << " ";
        if (ans[i].second > 0) cout << '+'; cout << ans[i].second << "\n";
    }

    return 0;
}
