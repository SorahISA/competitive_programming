#pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

// #define int long long

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(0, INT_MAX); \
                 auto rnd = bind(__dis, __gen);

const int mod = 1E9 + 7;
const int maxn = 3E6 + 5;

int v[maxn];

int32_t main() {
    // fastIO();

    int n, _n, maxVal = 0, nowVal = 0, nowMul = 1, nowLen = 1;
    cin >> n, _n = n;

    for (int i = 0; i < n; ++i) scanf("%d", &v[i]);

    while (_n) maxVal += _n >>= 1;

    for (int i = 1; i < n; ++i) {
        if (v[i] % v[i - 1] == 0) {
            if (v[i] == v[i - 1] * nowMul) nowVal += ++nowLen;
            else nowMul = v[i] / v[i - 1], nowVal += nowLen = 1;
        }
        else nowMul = nowLen = 0;
    }

    // cerr << "NowVal: " << nowVal << "\nMaxVal: " << maxVal << "\n";
    printf("%d\n", maxVal - nowVal);

    return 0;
}
