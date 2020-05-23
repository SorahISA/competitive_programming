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

int fl_multi = 0, fl_noans = 0;
int ans_getans = 0, ans_noans = 0;
vector<int> adj[30], InD(30, 0), vis(30, 0);
string seq;

void dfs(int now) {
    queue<int> que;
    int cnt = 0;
    for (auto x : adj[now]) {
        if (++vis[x] == InD[x]) ++cnt, que.push(x);
    }
    if (cnt >= 2) fl_multi = 1;
    
    while (!que.empty()) {
        int nxt = que.front(); que.pop();
        seq.pb('A' + nxt), dfs(nxt);
    }
}

int32_t main() {
    fastIO();
    
    int n, m;
    cin >> n >> m;
    
    vector<pii> edge(m+1);
    for (int tok = 1; tok <= m; ++tok) {
        char a, b;
        cin >> a >> b;
        edge[tok].X = a - 'A';
        edge[tok].Y = b - 'A';
        ++InD[edge[tok].Y];
        adj[edge[tok].X].eb(edge[tok].Y);
    }
    
    /// find if there's an answer ///
    
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (InD[i] == 0) ++cnt, dfs(i);
    }
    if (cnt >= 2) fl_multi = 1;
    
    for (int i = 0; i < n; ++i) {
        if (vis[i] != InD[i]) fl_noans = 1;
    }
    
    if (fl_multi and !fl_noans) {cout << "No answer\n"; return 0;}
    
    /// init ///
    
    vis.assign(30, 0), InD.assign(30, 0);
    for (int i = 0; i < 30; ++i) adj[i].clear();
    
    /// find where the answer occurs ///
    
    for (int tok = 1; tok <= m; ++tok) {
        vis.assign(30, 0);
        ++InD[edge[tok].Y];
        adj[edge[tok].X].eb(edge[tok].Y);
        cnt = fl_multi = fl_noans = 0;
        seq.clear();
        
        for (int i = 0; i < n; ++i) {
            if (InD[i] == 0) ++cnt, seq.pb('A' + i), dfs(i);
        }
        if (cnt >= 2) fl_multi = 1;
        
        if (!ans_getans and !fl_multi) ans_getans = tok;
        
        for (int i = 0; i < n; ++i) {
            if (vis[i] != InD[i]) fl_noans = 1;
        }
        
        if (!ans_noans and fl_noans) ans_noans = tok;
    }
    
    if (fl_noans) cout << "Order conflict after getting pair " << ans_noans << "\n";
    else cout << "Determine the testing sequence after getting pair " << ans_getans << " : " << seq << "\n";
    
    return 0;
}
