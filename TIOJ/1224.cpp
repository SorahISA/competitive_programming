#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

int rdi() {
    int _n = 0, _f = 0;
    char _c = getchar();
    while (_c < '0' or _c > '9') _f |= _c == '-', _c = getchar();
    while (_c >= '0' and _c <= '9') _n = (_n << 3) + (_n << 1) + (_c ^ 48), _c = getchar();
    return _f ? -_n : _n;
}

void pti(int x, char c = ' ') {printf("%lld%c", x, c);}

const int maxn = 1 << 20;

struct SegTree {
    int sum, tag;
} seg[2*maxn];

vector<tuple<int, int, int>> Query[maxn];

void RangeAdd(int ql, int qr, int val, int now = 1, int l = 0, int r = maxn-1) {
    // cout << __FUNCTION__ << ": " << now << " [" << l << ", " << r << "]\n";
    if (qr < l or r < ql) return;
    
    int lt = now << 1, rt = lt | 1, m = l + r >> 1;
    
    if (ql <= l and r <= qr) seg[now].tag += val;
    else RangeAdd(ql, qr, val, lt, l, m), RangeAdd(ql, qr, val, rt, m+1, r);
    
    if (seg[now].tag) seg[now].sum = r - l + 1;
    else if (l != r) seg[now].sum = seg[lt].sum + seg[rt].sum;
    else seg[now].sum = 0;
}

void solve() {
    int n; cin >> n;
    
    for (int i = 0; i < n; ++i) {
        int x1, x2, y1, y2; cin >> x1 >> x2 >> y1 >> y2;
        Query[y1].eb(x1, x2-1, 1);
        Query[y2].eb(x1, x2-1, -1);
    }
    
    int64_t ans = 0;
    for (int i = 0; i < maxn; ++i) {
        for (auto [l, r, v] : Query[i]) {
            // cout << "Query " << l << " " << r << " " << v << "\n";
            RangeAdd(l, r, v);
        }
        ans += seg[1].sum;
        // cout << "Add " << seg[1].sum << "\n";
        // cout << string(15, '-') << "\n";
        // for (int j = 1; j < 2*maxn; ++j) cout << seg[j].sum << " " << seg[j].tag << "\n";
        // cout << string(15, '-') << "\n";
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}