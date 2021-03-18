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

template<class T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << "\n";
        os << vec[i];
    }
    return os;
}

const int maxn = 1 << 17;

struct Query {
    int P, K, id;
    Query() {P = K = id = 0;}
};

struct Segment {
    int L, R;
    vector<Query> query;
    Segment() {L = R = 0;}
};

vector<Segment> seg(2*maxn);
int BIT[maxn+1];

void Add(int idx, int val) {
    ++idx;
    while (idx <= maxn) BIT[idx] += val, idx += idx & -idx;
}

int Sum(int idx, int ans = 0) {
    ++idx;
    while (idx) ans += BIT[idx], idx -= idx & -idx;
    return ans;
}

int RangeSum(int L, int R) {
    if (R >= maxn) R = maxn - 1;
    if (L < 0) L = 0;
    return Sum(R) - Sum(L-1);
}

void solve() {
    int n, q; cin >> n >> q;
    
    vector<pii> v(n); /// (num, id)
    for (int i = 0; i < n; ++i) cin >> v[i].X, v[i].Y = i;
    sort(ALL(v));
    
    seg[1].L = 0, seg[1].R = maxn-1, seg[1].query.resize(q);
    for (int i = 0; i < q; ++i) cin >> seg[1].query[i].P >> seg[1].query[i].K, seg[1].query[i].id = i;
    
    for (int i = 1, tok = 0; i < maxn; ++i) {
        /// clear ///
        if (__builtin_popcount(i) == 1) tok = 0, memset(BIT, 0x00, sizeof(BIT));
        
        /// add everyone in [seg[i].L, seg[i].R] ///
        while (tok < n and v[tok].X <= seg[i].R) Add(v[tok++].Y, 1);
        
        /// set child range ///
        int M = seg[i].L + seg[i].R >> 1;
        seg[i<<1].L = seg[i].L, seg[i<<1].R = M;
        seg[i<<1|1].L = M + 1, seg[i<<1|1].R = seg[i].R;
        
        /// do binary search ///
        for (auto qry : seg[i].query) {
            if (RangeSum(qry.P - seg[i].R, qry.P + seg[i].R) < qry.K) seg[2*i+2].query.eb(qry);
            else seg[2*i].query.eb(qry);
        }
    }
    
    vector<int> ans(q);
    
    memset(BIT, 0x00, sizeof(BIT));
    for (int i = 0, j = maxn, tok = 0; i < maxn; ++i, ++j) {
        /// add everyone in [seg[j].L, seg[j].R] ///
        while (tok < n and v[tok].X <= seg[j].R) Add(v[tok++].Y, 1);
        
        /// set answer ///
        for (auto qry : seg[j].query) {
            if (RangeSum(qry.P - seg[j].R, qry.P + seg[j].R) < qry.K) ans[qry.id] = i + 1;
            else ans[qry.id] = i;
        }
    }
    
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}