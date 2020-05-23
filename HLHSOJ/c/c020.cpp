#pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

// #define int long long

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(0, MAXN); \
                 auto rnd = bind(__dis, __gen);

const int MAXN = 1E6;
const int maxn = 2E6 + 5;

vector<int> adj[maxn];
int p[maxn];
char ans[maxn];

int R(int x) {
    return x ^ p[x] ? p[x] = R(p[x]) : x;
}

int U(int x, int y) {
    if (R(x) == R(y)) return 0;
    p[p[x]] = p[y]; return 1;
}

int32_t main() {
    // fastIO();
    
    int n, m, u, v, ptr = 0;
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i <= n; ++i) p[i] = i;
    
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &u, &v);
        if (u < v) swap(u, v);
        adj[u].emplace_back(v);
    }
    
    for (int i = 0; i < n; ++i) {
        for (auto x : adj[i]) U(i, x);
        while (R(ptr) == R(0)) ++ptr;
        ans[i] = (ptr > i ? '1' : '0');
    }
    
    ans[n] = '\0';
    printf("%s\n", ans);
    
    return 0;
}
