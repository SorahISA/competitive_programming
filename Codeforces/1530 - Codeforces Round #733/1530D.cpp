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
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i] + 1;
    }
    return os;
}

void solve() {
    srand(rng());
    
    int N; cin >> N;
    
    vector<int> arr(N), app(N, 0);
    set<int> st[N], unpicked;
    for (int i = 0; i < N; ++i) unpicked.insert(i);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i], --arr[i], ++app[arr[i]];
        if (app[arr[i]] == 1) unpicked.erase(arr[i]);
        st[arr[i]].insert(i);
    }
    int K = N - unpicked.size();
    
    vector<int> ans(N, -1);
    for (int i = 0; i < N; ++i) {
        if (st[i].empty()) continue;
        // cerr << "set: " << i << "\n";
        int flag = 1, largest = *prev(end(st[i]));
        for (auto x : st[i]) {
            // cerr << "==> now at: " << x << "\n";
            auto iter = unpicked.upper_bound(x);
            if (x == largest and flag) ans[x] = i;
            else if (iter == end(unpicked)) {
                iter = begin(unpicked);
                if (*iter == x) ans[x] = i, flag = 0;
                else ans[x] = *iter, unpicked.erase(iter);
            }
            else ans[x] = *iter, unpicked.erase(iter);
        }
    }
    cout << K << "\n" << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}