// #pragma GCC target("avx2")
// #pragma GCC optimize("O3", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

const int INF = 1E9;
const int maxm = 1 << 17;

struct Query {
    int x, y, z;
    Query() {x = y = z = 0;}
};

vector<int> p, sz, pool[2*maxm]; /// pool for binary search

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
void U(int x, int y) {x = R(x), y = R(y); x ^ y ? sz[y] += sz[x], p[x] = y : 0LL;}

void solve() {
    int n, m; cin >> n >> m, p.resize(n+1), sz.resize(n+1);
    
    vector<pii> edge(m);
    for (auto &[x, y] : edge) cin >> x >> y;
    
    int q; cin >> q;
    vector<Query> query(q);
    for (auto &qry : query) cin >> qry.x >> qry.y >> qry.z;
    for (int i = 0; i < q; ++i) pool[1].eb(i);
    
    for (int i = 0, blk = maxm, id = 1; i < 17; ++i, blk >>= 1) {
        iota(ALL(p), 0), fill(ALL(sz), 1);
        for (int j = 0; j < maxm; ++j) {
            if (j < m) U(edge[j].X, edge[j].Y);
            if ((j + 1) % blk == 0) {
                for (auto qid : pool[id]) {
                    // cout << "[[DEBUG]] " << id << " " << qid << ": ";
                    auto qry = query[qid];
                    // cout << R(qry.x) << " " << R(qry.y) << " ";
                    // cout << sz[R(qry.x)] << " " << sz[R(qry.y)] << "\n";
                    if (R(qry.x) == R(qry.y)) {
                        if (sz[R(qry.x)] >= qry.z) pool[id<<1].eb(qid);
                        else pool[(id<<1)+2].eb(qid);
                    }
                    else {
                        if (sz[R(qry.x)] + sz[R(qry.y)] >= qry.z) pool[id<<1].eb(qid);
                        else pool[(id<<1)+2].eb(qid);
                    }
                }
                vector<int>().swap(pool[id++]);
            }
        }
    }
    
    vector<int> ans(q, INF);
    iota(ALL(p), 0), fill(ALL(sz), 1);
    for (int id = maxm; id < maxm+m; ++id) {
        U(edge[id-maxm].X, edge[id-maxm].Y);
        for (auto qid : pool[id]) {
            // cout << "[[DEBUG]] " << id << " " << qid << ": ";
            auto qry = query[qid];
            // cout << R(qry.x) << " " << R(qry.y) << " ";
            // cout << sz[R(qry.x)] << " " << sz[R(qry.y)] << "\n";
            if (R(qry.x) == R(qry.y)) {
                if (sz[R(qry.x)] >= qry.z) ans[qid] = id - maxm;
                else ans[qid] = id + 1 - maxm;
            }
            else {
                if (sz[R(qry.x)] + sz[R(qry.y)] >= qry.z) ans[qid] = id - maxm;
                else ans[qid] = id + 1 - maxm;
            }
        }
    }
    for (auto x : ans) cout << x+1 << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
