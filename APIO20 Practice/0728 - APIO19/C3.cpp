#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)

const int maxn = 1 << 19;
const int INF = 0x7f7f7f7f;

int seg[maxn << 1];
/// single modify, range maximum ///

int Query(int qL, int qR, int id = 1, int nL = 0, int nR = maxn-1) {
    if (qL <= nL and nR <= qR) return seg[id];
    if (qR < nL or nR < qL) return -1; /// return any number <= 0 ///
    
    int qM = qL + qR >> 1;
    int nM = nL + nR >> 1;
    return max(Query(qL, qR, ls(id), nL,     nM),
               Query(qL, qR, rs(id), nM + 1, nR));
}

int32_t main() {
    fastIO();
    
    int n, q, x, l, r;
    string s, op;
    cin >> n >> q >> s;
    
    for (int i = 0, j = maxn; i < n; ++i, ++j) {
        seg[j] = (s[i] == '0' ? INF : 0);
    }
    for (int j = maxn-1; j >= 1; --j) {
        seg[j] = max(seg[ls(j)], seg[rs(j)]);
    }
    
    for (int i = 1; i <= q; ++i) {
        cin >> op;
        if (op == "toggle") {
            cin >> x, x += maxn - 1;
            seg[x] = i;
            while (x >>= 1) seg[x] = max(seg[ls(x)], seg[rs(x)]);
        }
        if (op == "query") {
            cin >> l >> r, l -= 1, r -= 2;
            int ans = Query(l, r);
            cout << (ans == INF ? 0 : i - ans) << "\n";
        }
    }
    
    return 0;
}