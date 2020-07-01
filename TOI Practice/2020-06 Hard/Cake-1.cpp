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

const int maxn = 1 << 17;

struct Seg {
    int pre, suf, sum, ans;
    Seg(int _pre = 0, int _suf = 0, int _sum = 0, int _ans = 0) :
        pre(_pre), suf(_suf), sum(_sum), ans(_ans) {}
};

int segtree[maxn << 1], seg_pre[maxn << 1], seg_suf[maxn << 1], seg_sum[maxn << 1];

Seg Query(int qL, int qR, int id = 1, int L = 0, int R = maxn-1) {
    if (qR < L or R < qL) return Seg{0, 0, 0, 0};
    if (qL <= L and R <= qR) return Seg{seg_pre[id], seg_suf[id], seg_sum[id], segtree[id]};
    
    int mi = L + R >> 1;
    Seg ansT;
    Seg ansL = Query(qL, qR, id << 1, L, mi);
    Seg ansR = Query(qL, qR, id << 1 | 1, mi + 1, R);
    
    ansT.ans = max({0LL, ansL.ans, ansR.ans, ansL.suf + ansR.pre});
    ansT.pre = max({0LL, ansL.pre, ansL.sum + ansR.pre});
    ansT.suf = max({0LL, ansR.suf, ansL.suf + ansR.sum});
    ansT.sum = ansL.sum + ansR.sum;
    return ansT;
}

int32_t main() {
    fastIO();
    
    int n, k;
    cin >> n >> k;
    
    for (int i = 0; i < n; ++i) {
        cin >> segtree[maxn + i], seg_sum[maxn + i] = segtree[maxn + i];
        seg_pre[maxn + i] = seg_suf[maxn + i] = max(0LL, segtree[maxn + i]);
    }
    
    for (int i = maxn-1; i >= 1; --i) {
        int lt = i << 1, rt = lt | 1;
        segtree[i] = max({0LL, segtree[lt], segtree[rt], seg_suf[lt] + seg_pre[rt]});
        seg_pre[i] = max({0LL, seg_pre[lt], seg_pre[rt] + seg_sum[lt]});
        seg_suf[i] = max({0LL, seg_suf[rt], seg_suf[lt] + seg_sum[rt]});
        seg_sum[i] = seg_sum[lt] + seg_sum[rt];
    }
    
    int maxAns = 0;
    for (int i = 0, j = k-1; j < n; ++i, ++j) {
        maxAns = max(maxAns, Query(i, j).ans);
    }
    
    cout << maxAns << "\n";
    
    return 0;
}
