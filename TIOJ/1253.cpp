#include <bits/stdc++.h>
using namespace std;

#define int long long
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

const int maxn = 2000 + 5;

vector<int> adj[maxn], vis(maxn), match(maxn, -1);

bool dfs(int now) {
    if (vis[now]) return 0;
    vis[now] = 1;
    for (auto x : adj[now]) {
        if (match[x] == -1 or dfs(match[x])) {
            match[x] = now; return 1;
        }
    }
    return 0;
}

void solve(int n, int k) {
    for (int i = 0; i < maxn; ++i) adj[i].clear();
    fill(ALL(vis), 0), fill(ALL(match), -1);
    
    for (int i = 0; i < k; ++i) {
        int a, b; cin >> a >> b;
        adj[a].eb(n + b), adj[n + b].eb(a);
    }
    
    int ans = 0;
    for (int i = 1; i <= n; ++i) fill(ALL(vis), 0), ans += dfs(i);
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1, n, k; // cin >> t;
    while (cin >> n >> k and max(n, k)) {
        cout << "Case #" << t++ << ":"; solve(n, k);
    }
    
    return 0;
}