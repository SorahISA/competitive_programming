#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define ef push_front
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template <typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

struct edge{
    int u,v,w;
    bool operator < (const edge &a) const {
        return w > a.w;
    }
};
const int MAXN = 2e5+5;
vector<edge> E;
vector<int> e[MAXN];
int ok[MAXN], eok[MAXN];
int to(edge ed){
    return (ok[ed.u] ?ed.v:ed.u);
}
void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    for (int i=0;i<m;++i) {
        int u,v,w;
        cin >> u >> v >> w;
        E.eb((edge){u, v, w});
        e[u].emplace_back(i);
        e[v].emplace_back(i);
    }
    
    priority_queue<edge> pq;
    int ans = 1;
    ok[1] = 1;
    for (auto it : e[1]) {
        pq.emplace(E[it]);
        eok[it] = 1;
    }
    while (q--) {
        int cur;
        cin >> cur;
        vector<int> tmp;
        while (SZ(pq) && pq.top().w <= cur) {
            int nxt = to(pq.top());
            pq.pop();
            if (ok[nxt]) continue;
            ok[nxt] = 1;
            ans++;
            tmp.emplace_back(nxt);
        }
        for (auto v : tmp) {
            for (int i=0;i<SZ(e[v]);++i) {
                int eid = e[v][i];
                if (eok[eid]) continue;
                pq.emplace(E[eid]);
                eok[eid] = 1;
            }
        }
        cout << ans << '\n';
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
