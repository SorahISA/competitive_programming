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
const int maxn = 2E5 + 5;

int fl_triangle = 1, fl_color = 1, tok = 0;
vector<pii> col[maxn]; /// (id , col)

void recur(int L, int R) {
    // cerr << "in recur : " << L << " " << R << "\n";
    queue<pii> que;
    while (tok < R and fl_triangle) {
        ++tok;
        int sz = col[tok].size();
        for (int i = 1; i < sz-1; ++i) {
            int now = col[tok][i].X;
            int lst = col[tok][i-1].X;
            if ((L <= now and now <= R) or tok == R) que.push({lst, now});
            else fl_triangle = 0;
        }
        while (!que.empty()) {
            auto [l, r] = que.front(); que.pop();
            recur(l, r);
        }
    }
}

int32_t main() {
    fastIO();
    
    int sub, n;
    cin >> sub >> n;
    
    for (int i = 1; i <= n; ++i) {
        char c; cin >> c;
        col[i].eb(i%n+1, c^'0');
        col[i%n+1].eb(i, c^'0');
    }
    
    for (int i = 1; i <= n-3; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        col[a].eb(b, c);
        col[b].eb(a, c);
    }
    
    for (int i = 1; i <= n; ++i) {
        sort(ALL(col[i]), [=](auto a, auto b) {
            return (a.X - i + n) % n < (b.X - i + n) % n;
        });
        // for (auto x : col[i]) cerr << x.Y << " "; cerr << "\n";
        int sz = col[i].size();
        for (int j = 1; j < sz; ++j) {
            if (col[i][j].Y == col[i][j-1].Y) fl_color = 0;
        }
    }
    
    recur(1, n);
    
    if (!fl_triangle) cout << "neispravna triangulacija\n";
    else if (!fl_color) cout << "neispravno bojenje\n";
    else cout << "tocno\n";
    
    return 0;
}
