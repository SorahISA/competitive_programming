#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define eb emplace_back
#define X first
#define Y second
#ifdef local
#define debug(...) do{\
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S &&..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs){return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs){return lhs < rhs ? lhs = rhs, 1 : 0;}

const int INF = 0x3f3f3f3f3f3f3f3f;

map<int, int> mp;
int L;
void addrange(int l, int r, int val) {
    chmax(l, 1LL), chmin(r, L+1);
    chmin(l, L+1), chmax(r, 1LL);
    mp[l] += val, mp[r] -= val;
}

void solve() {
    int n;
    cin >> n >> L;
    vector<int> x(n), a(n);
    for (int i=0;i<n;++i) cin >> x[i];
    for (int i=0;i<n;++i) cin >> a[i];
    
    for (int i=0;i<n;++i) {
        int cur = a[i];
        int sqcur = sqrt(cur);
        addrange(x[i], x[i] + 1, cur);
        for (int j=2;j<=sqcur;++j) {
            int val = cur / j;
            int pos1 = x[i] - j + 1, pos2 = x[i] + j - 1;
            addrange(pos1, pos1 + 1, val);
            addrange(pos2, pos2 + 1, val);
            
        }
        int st = a[i] / sqcur - 1;
        for (int j=st;j>=1;--j) {
            int l = cur / (j + 1) + x[i];
            int r = cur / j + x[i];
            addrange(l, r, j);
            l = x[i] + 1 - cur / j;
            r = x[i] + 1 - cur / (j+1);
            addrange(l, r, j);
        }
    }
    
    int mn = INF, mx = 0, sum = 0;
    for (auto [pos, val] : mp) {
        if (pos == L+1) break;
        sum += val;
        chmin(mn, sum);
        chmax(mx, sum);
        debug(sum, pos, val);
    }
    cout << mn << ' ' << mx << endl;
}

signed main() {
    IOS();
    int _ = 1;
    // cin >> _;
    for (int i=1;i<=_;++i) {
        solve();
    }
}
