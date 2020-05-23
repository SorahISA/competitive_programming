// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
// template <typename T>
// using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(0, 1); \
                 auto rnd = bind(__dis, __gen);

const int INF = 1E18;
const int mod = 1E9 + 7;

vector<pii> adj[30], dag[30];
vector<int> vis(30, 0), dis(30, INF), InD(30, 0), trans(30, INF), lstID(30, 0);
vector<string> ans(30), realans(30);
queue<int> seq;

void bfs(int now) {
    vis[now] = 1;
    for (auto x : adj[now]) {
        if (dis[x.X] > dis[now] + 1) dis[x.X] = dis[now] + 1, seq.push(x.X);
    }
    
    while (!seq.empty()) {
        int nxt = seq.front(); seq.pop();
        if (vis[nxt]) continue;
        bfs(nxt);
    }
}

void dfs(int now, int lst) {
    for (auto x : dag[now]) {
        if (trans[x.X] > trans[now] + (x.Y != lst)) {
            trans[x.X] = trans[now] + (x.Y != lst);
            ans[x.X] = ans[now] + (char)('A' + x.X);
            realans[x.X] = realans[now];
            if (x.Y != lst) realans[x.X] += to_string(x.Y), lstID[x.X] = x.Y;
            realans[x.X].pb('A' + x.X);
        }
        else if (trans[x.X] == trans[now] + (x.Y != lst)) {
            if (ans[x.X] > ans[now] + (char)('A' + x.X)) {
                ans[x.X] = ans[now] + (char)('A' + x.X);
                realans[x.X] = realans[now];
                if (x.Y != lst) realans[x.X] += to_string(x.Y), lstID[x.X] = x.Y;
                realans[x.X].pb('A' + x.X);
            }
            else if (ans[x.X] == ans[now] + (char)('A' + x.X)) {
                // cout << "hello ? lst = " << lstID[x.X] << "\n";
                // cout << "now on line " << x.Y << " from " << now << " to " << x.X << "\n";
                // cout << "... and the real ans is " << realans[x.X] << "\n";
                if (lstID[x.X] > x.Y) {
                    realans[x.X] = realans[now];
                    realans[x.X] += to_string(x.Y), lstID[x.X] = x.Y;
                    realans[x.X].pb('A' + x.X);
                }
            }
        }
        dfs(x.X, x.Y);
    }
}

int32_t main() {
    fastIO();
    
    int n, m, sz;
    string str;
    cin >> n >> m;
    
    for (int i = 1; i <= m; ++i) {
        cin >> str, sz = str.size();
        for (int j = 1; j < sz; ++j) {
            adj[str[j-1]-'A'].eb(str[j]-'A', i);
            adj[str[j]-'A'].eb(str[j-1]-'A', i);
        }
    }
    
    int s, t;
    char _s, _t;
    cin >> _s >> _t, s = _s - 'A', t = _t - 'A';
    
    dis[s] = 1, bfs(s);
    
    for (int i = 0; i < n; ++i) {
        for (auto x : adj[i]) {
            if (dis[x.X] == dis[i] + 1) ++InD[x.X], dag[i].eb(x);
        }
    }
    
    trans[s] = 0, dfs(s, 0);
    
    cout << dis[t] << "\n";
    cout << realans[t][0] << _s << realans[t].substr(1) << "\n";
    
    return 0;
}
