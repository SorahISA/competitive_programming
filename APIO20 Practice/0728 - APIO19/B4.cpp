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

struct Edge {
    int u, v, w;
};

struct Query {
    int op, st, wi, ti;
};

const int maxn = 5E4 + 5;
const int INF = 0x7f7f7f7f;

vector<int> par(maxn), sz(maxn, 1);

int R(int x) {return x ^ par[x] ? par[x] = R(par[x]) : x;}
void U(int x, int y) {if (R(x) != R(y)) sz[par[y]] += sz[par[x]], par[par[x]] = par[y];}

int32_t main() {
    fastIO();
    iota(ALL(par), 0);
    
    int n, m, Q, tok = 0;
    cin >> n >> m;
    
    vector<Edge> edge(m);
    for (auto &e : edge) cin >> e.u >> e.v >> e.w;
    sort(ALL(edge), [](auto e1, auto e2) {return e1.w > e2.w;});
    edge.pb({0, 0, 0});
    
    cin >> Q;
    
    vector<Query> query(Q);
    for (auto &q : query) cin >> q.op >> q.st >> q.wi, q.ti = tok++;
    sort(ALL(query), [](auto q1, auto q2) {return q1.wi > q2.wi;});
    
    vector<int> ans(Q);
    int tokE = 0, tokQ = 0;
    while (tokQ < Q) {
        if (edge[tokE].w >= query[tokQ].wi) {
            U(edge[tokE].u, edge[tokE].v), ++tokE;
        }
        else {
            ans[query[tokQ].ti] = sz[R(query[tokQ].st)], ++tokQ;
        }
    }
    
    for (auto x : ans) cout << x << "\n";
    
    return 0;
}