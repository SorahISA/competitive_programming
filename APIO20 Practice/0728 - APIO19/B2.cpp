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

struct Edge {
    int u, v, w;
};

const int maxn = 1 << 16;
const int INF = 0x7f7f7f7f;

int seg[maxn << 1];
/// single modify, range maximum ///

int Query(int qL, int qR, int id = 1, int nL = 0, int nR = maxn-1) {
    if (qL <= nL and nR <= qR) return seg[id];
    if (qR < nL or nR < qL) return INF; /// return any number > 10^9 ///
    
    int qM = qL + qR >> 1;
    int nM = nL + nR >> 1;
    return min(Query(qL, qR, ls(id), nL,     nM),
               Query(qL, qR, rs(id), nM + 1, nR));
}

int32_t main() {
    fastIO();
    
    int n, m, q;
    cin >> n >> m;
    
    vector<Edge> edge(m);
    for (auto &e : edge) cin >> e.u >> e.v >> e.w, --e.u, --e.v;
    for (int i = 0, j = maxn; i < m; ++i, ++j) seg[j] = edge[i].w;
    for (int j = maxn-1; j >= 1; --j) seg[j] = min(seg[ls(j)], seg[rs(j)]);
    
    cin >> q;
    
    for (int i = 1; i <= q; ++i) {
        int op, st, wi;
        cin >> op >> st >> wi;
        
        if (op == 1) {
            st += maxn - 1;
            seg[st] = wi;
            while (st >>= 1) seg[st] = min(seg[ls(st)], seg[rs(st)]);
        }
        if (op == 2) {
            --st;
            int ansL, ansR;
            
            int l = st, r = n-1, mi;
            while (l < r) {
                mi = l + r >> 1;
                if (Query(st, mi) >= wi) l = mi + 1;
                else r = mi;
            }
            ansR = l;
            
            l = -1, r = st-1;
            while (l < r) {
                mi = l + r + 1 >> 1;
                if (Query(mi, st-1) >= wi) r = mi - 1;
                else l = mi;
            }
            ansL = r;
            
            // cout << ansR << " " << ansL << " ";
            cout << ansR - ansL << "\n";
        }
    }
    
    return 0;
}