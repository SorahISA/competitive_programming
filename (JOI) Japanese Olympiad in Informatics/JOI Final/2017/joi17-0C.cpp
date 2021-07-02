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

const int INF = 1E9;
const int mod = 1E9 + 7;

int32_t main() {
    fastIO();
    
    int h, w;
    cin >> h >> w;
    
    int _max = 0;
    vector<vector<int>> v(h, vector<int>(w));
    for (auto &x : v) for (auto &y : x) cin >> y, _max = max(_max, y);
    
    int lo = 0, hi = INF, mi, inMin, inMax;
    vector<int> heiL, heiR;
    while (lo < hi) {
        mi = lo + hi >> 1;
        
        heiL.clear(), heiR.clear();
        for (auto vec : v) {
            for (int i = 0; i < w; ++i) {
                if (vec[i] < _max - mi) {heiL.eb(i); break;}
                if (i == w-1) heiL.eb(w);
            }
            for (int i = w-1; i >= 0; --i) {
                if (vec[i] < _max - mi) {heiR.eb(i+1); break;}
                if (i == 0) heiR.eb(0);
            }
        }
        for (int i = 1; i < h; ++i) heiL[i] = min(heiL[i-1], heiL[i]);
        for (int i = 1; i < h; ++i) heiR[i] = max(heiR[i-1], heiR[i]);
        
        inMin = INF, inMax = 0;
        for (int i = 0; i < h; ++i) {
            for (int j = heiL[i]; j < w; ++j) inMax = max(inMax, v[i][j]), inMin = min(inMin, v[i][j]);
        }
        if (inMax - inMin <= mi) {hi = mi; continue;}
        
        inMin = INF, inMax = 0;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < heiR[i]; ++j) inMax = max(inMax, v[i][j]), inMin = min(inMin, v[i][j]);
        }
        if (inMax - inMin <= mi) {hi = mi; continue;}
        
        heiL.clear(), heiR.clear();
        for (auto vec : v) {
            for (int i = 0; i < w; ++i) {
                if (vec[i] < _max - mi) {heiL.eb(i); break;}
                if (i == w-1) heiL.eb(w);
            }
            for (int i = w-1; i >= 0; --i) {
                if (vec[i] < _max - mi) {heiR.eb(i+1); break;}
                if (i == 0) heiR.eb(0);
            }
        }
        for (int i = h-2; i >= 0; --i) heiL[i] = min(heiL[i+1], heiL[i]);
        for (int i = h-2; i >= 0; --i) heiR[i] = max(heiR[i+1], heiR[i]);
        
        inMin = INF, inMax = 0;
        for (int i = 0; i < h; ++i) {
            for (int j = heiL[i]; j < w; ++j) inMax = max(inMax, v[i][j]), inMin = min(inMin, v[i][j]);
        }
        if (inMax - inMin <= mi) {hi = mi; continue;}
        
        inMin = INF, inMax = 0;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < heiR[i]; ++j) inMax = max(inMax, v[i][j]), inMin = min(inMin, v[i][j]);
        }
        if (inMax - inMin <= mi) {hi = mi; continue;}
        
        lo = mi + 1;
    }
    
    cout << lo << "\n";
    
    return 0;
}
