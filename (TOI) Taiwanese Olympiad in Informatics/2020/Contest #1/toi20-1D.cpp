// #pragma GCC target("avx2")
#pragma GCC optimize("Ofast", "unroll-loops")

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

const int INF = 0x7f7f7f7f;
const int mod = 1E9 + 7;
const int maxn = 1E6 + 5;
const double eps = 1e-6;

int stk[maxn], sz; /// to replace deque

inline double intersect(pair<double, double> p1, pair<double, double> p2) {
    return (p2.Y*p2.Y - p1.Y*p1.Y + p2.X*p2.X - p1.X*p1.X) / (2.0 * (p2.X - p1.X));
}

int32_t main() {
    fastIO();
    
    int n;
    double L;
    cin >> n >> L;
    
    vector<pair<double, double>> pt(n);
    for (auto &p : pt) {
        int xx, yy;
        cin >> xx >> yy;
        p.X = xx, p.Y = yy;
    }
    sort(ALL(pt), [](auto p1, auto p2) {
        if (abs(p1.X - p2.X) < eps) return p1.Y < p2.Y;
        return p1.X < p2.X;
    });
    
    vector<double> ans;
    for (int i = 1, tok = 1; i < n; ++i) {
        if (abs(pt[i].X - pt[i - 1].X) > eps) swap(pt[i], pt[tok++]);
        else ans.eb(0);
        if (i == n - 1) pt.resize(n = tok);
    }
    
    if (n >= 2) {
        stk[sz++] = 0, stk[sz++] = 1;
        for (int i = 2; i < n; ++i) {
            int lst1 = stk[sz - 1]; --sz;
            int lst2 = stk[sz - 1];
            int fl = 0; /// whether pushing back lst1
            
            while (intersect(pt[lst2], pt[lst1]) > intersect(pt[lst2], pt[i])) {
                ans.eb(0);
                if (sz < 2) {fl = 1; break;}
                lst1 = stk[sz - 1], --sz;
                lst2 = stk[sz - 1];
            }
            
            if (!fl) stk[sz++] = lst1;
            stk[sz++] = i;
        }
        
        ans.eb(max((double)0.0,     intersect(pt[stk[0]],      pt[stk[1]])));
        ans.eb(max((double)0.0, L - intersect(pt[stk[sz - 2]], pt[stk[sz - 1]])));
        for (int i = 1; i < sz-1; ++i) {
            double pR = intersect(pt[stk[i]], pt[stk[i + 1]]);
            double pL = intersect(pt[stk[i - 1]], pt[stk[i]]);
            pR = max((double)0.0, min(L, pR));
            pL = max((double)0.0, min(L, pL));
            ans.eb(pR - pL);
        }
    }
    else {
        ans.eb(L);
    }
    
    sort(ALL(ans));
    cout << fixed << setprecision(8);
    cout << ans[0] << " " << ans[(ans.size() - 1) / 2] << " " << ans[ans.size() - 1] << "\n";
    
    return 0;
}
