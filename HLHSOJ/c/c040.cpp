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
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 2E6 + 5;

int scc_id = 0;
vector<int32_t> adj[maxn];
int32_t scc[maxn], sz[maxn];
int minVal[maxn];
stack<int32_t> stk;

vector<int> st;
vector<pii> v;

void dfs(int now) {
    scc[now] = scc_id, minVal[scc_id] = st[now];
    stk.push(now);
    
    while (!stk.empty()) {
        now = stk.top(), stk.pop();
        ++sz[scc_id], minVal[scc_id] = min(minVal[scc_id], st[now]);
        
        for (auto x : adj[now]) {
            if (!scc[x]) scc[x] = scc_id, stk.push(x);
        }
    }
}

int32_t main() {
    // freopen("s06_01.in", "r", stdin);
    fastIO();
    
    int n, tok = 0, tot = 0;
    cin >> n, v.resize(n);
    
    for (auto &x : v) cin >> x.X >> x.Y, st.eb(x.X), st.eb(x.Y);
    sort(ALL(st));
    st.resize(unique(ALL(st)) - st.begin());
    for (auto x : st) tot += x;
    
    for (auto &x : v) {
        x.X = lower_bound(ALL(st), x.X) - st.begin();
        x.Y = lower_bound(ALL(st), x.Y) - st.begin();
        adj[x.X].eb(x.Y), adj[x.Y].eb(x.X);
    }
    
    for (int i = 0; i < st.size(); ++i) {
        if (!scc[i]) ++scc_id, dfs(i);
    }
    
    for (auto x : v) --sz[scc[x.X]];
    
    for (int i = 1; i <= scc_id; ++i) {
        if (sz[i] == 1) tot -= minVal[i]; /// N nodes, N-1 edges ///
    }
    
    cout << tot << "\n";
    
    return 0;
}
