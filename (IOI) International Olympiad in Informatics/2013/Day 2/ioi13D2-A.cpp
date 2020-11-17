#include "cave.h"

// #pragma GCC target("avx2")
#pragma GCC optimize("Ofast", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
// template <typename T>
// using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int maxn = 5000 + 5;

// void answer(int S[], int D[]);
// int tryCombination(int S[]);

int ans[maxn], pls[maxn], tmp[maxn];

void exploreCave(int N) {
    memset(ans, 0xff, sizeof(ans));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) tmp[j] = ans[j] >= 0 ? ans[j] : 1;
        int on = tryCombination(tmp);
        int st = on > i or on == -1;
        
        int lo = 0, hi = N-1, mi, ret;
        while (lo < hi) {
            mi = lo + hi >> 1;
            for (int j = 0; j < N; ++j) tmp[j] = ans[j] >= 0 ? ans[j] : (j > mi) ^ st;
            ret = tryCombination(tmp);
            if (ret > i or ret == -1) hi = mi;
            else                      lo = mi + 1;
        }
        pls[lo] = i;
        ans[lo] = st;
    }
    answer(ans, pls);
}
