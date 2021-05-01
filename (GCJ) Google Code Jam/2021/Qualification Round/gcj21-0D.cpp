#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<class T>
ostream& operator << (ostream& os, vector<T> vec) {
    int sz = vec.size();
    for (int i = 0; i < sz; ++i) {
        os << vec[i];
        if (i != sz-1) os << " ";
    }
    return os;
}

int N, Q;

int Query(int i, int j, int k) {
    assert(i != j and i != k and j != k);
    cout << i << " " << j << " " << k << "\n" << flush;
    int ret; cin >> ret;
    if (ret == -1) exit(0);
    return ret;
}

int Query(vector<int> vec) {
    cout << vec << "\n" << flush;
    int ret; cin >> ret;
    if (ret == -1) exit(0);
    return ret;
}

void solve() {
    // if (Q == 300 * 100) { /// testing for Subtask 3 through Subtask 2
        // for (int i = 0; i < 130; ++i) Query(1, 2, 3);
    // }
    
    vector<int> arr(N); iota(ALL(arr), 1);
    vector<tuple<int, int, int, int>> qry;
    for (int i = 0; i < N-2; ++i) {
        random_shuffle(begin(arr), end(arr) - i);
        int ret = Query(arr[0], arr[1], arr[2]);
        qry.eb(arr[0], arr[1], arr[2], ret);
        for (int j : {0, 1, 2}) {
            if (arr[j] == ret) swap(arr[j], arr[N-i-1]);
        }
    }
    
    vector<int> app(N+1, 0), ans{arr[0], arr[1]};
    
    for (auto [i, j, k, ret] : qry) {
        if (i == ans[0] or j == ans[0] or k == ans[0]) {
            ans.insert(begin(ans) + 1, ret); break;
        }
    }
    
    // cout << "TEMP: " << ans << "\n";
    
    for (int i = 0; i < ans.size(); ++i) app[ans[i]] = i+1;
    
    for (auto x : arr) {
        if (app[x]) continue;
        app[x] = 100; /// some number > N
        
        int lo = 0, hi = ans.size()-1, milo, mihi;
        for (auto [i, j, k, ret] : qry) {
            if ((i == x or j == x or k == x) and (app[i] and app[j] and app[k])) {
                vector<int> tmp{app[i], app[j], app[k]};
                sort(ALL(tmp));
                if (ret == x) lo = max(lo, tmp[0]-1), hi = min(hi, tmp[1]-1);
                else if (app[ret] == tmp[0]) hi = min(hi, tmp[0]-1);
                else if (app[ret] == tmp[1]) lo = max(lo, tmp[1]-1);
            }
        }
        
        while (lo + 1 < hi) {
            milo = (lo + lo + hi) / 3;
            mihi = (lo + hi + hi) / 3;
            int ret = Query(ans[milo], ans[mihi], x);
            if (ret == ans[milo]) hi = milo;
            if (ret == ans[mihi]) lo = mihi;
            if (ret == x) lo = milo, hi = mihi;
        }
        ans.insert(begin(ans) + lo+1, x);
        
        for (int i = 0; i < ans.size(); ++i) app[ans[i]] = i+1;
    }
    
    Query(ans);
}

int32_t main() {
    fastIO();
    srand(880301);
    
    int t = 1; cin >> t >> N >> Q;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}