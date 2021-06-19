#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define pf pop_front
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
        os << vec[i];
    }
    return os;
}

const int INF = INT_MAX;
const int maxn = 30 * (int)2E5 + 10;

template<size_t sz>
struct Trie {
    int cnt[sz], sub[sz][2], idx[sz];
    
    Trie() {
        memset(cnt, 0x00, sizeof(cnt));
        memset(sub, 0xff, sizeof(sub));
        memset(idx, 0xff, sizeof(idx));
    }
    
    void Print() {
        deque<pii> deq{{0, 0}}; /// (idx, val)
        while (!deq.empty()) {
            auto [now, val] = deq.front(); deq.pf();
            if (sub[now][0] != -1 and cnt[sub[now][0]]) deq.eb(sub[now][0], val << 1);
            if (sub[now][1] != -1 and cnt[sub[now][1]]) deq.eb(sub[now][1], val << 1 | 1);
            if (idx[now] != -1) cout << "(" << val << "," << idx[now] << ") ";
        }
        cout << "\n";
    }
    
    void Insert(int x, int id) {
        static int tok = 0;
        int now = 0;
        for (int i = 29; i >= 0; --i) {
            if (sub[now][x>>i&1] == -1) sub[now][x>>i&1] = ++tok;
            ++cnt[now], now = sub[now][x>>i&1];
        }
        ++cnt[now], idx[now] = id;
    }
    
    void Delete(int x) {
        int now = 0;
        for (int i = 29; i >= 0; --i) {
            --cnt[now], now = sub[now][x>>i&1];
        }
        --cnt[now], idx[now] = -1;
    }
    
    pii FindMinXor(int x) {
        int now = 0, val = 0;
        for (int i = 29; i >= 0; --i) {
            if (sub[now][x>>i&1] != -1 and cnt[sub[now][x>>i&1]]) {
                now = sub[now][x>>i&1], val = val << 1;
            }
            else {
                now = sub[now][(x>>i&1)^1], val = val << 1 | 1;
            }
        }
        return {val, idx[now]};
    }
};

vector<int> p, sz;
vector<vector<int>> group;

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}

int U(int x, int y) {
    x = R(x), y = R(y);
    if (x == y) return 0;
    sz[y] += sz[x], p[x] = y;
    for (auto _ : group[x]) group[y].eb(_);
    vector<int>().swap(group[x]);
    return 1;
}

Trie<maxn> trie;

void solve() {
    int N; cin >> N;
    
    vector<int> arr(N);
    for (auto &x : arr) cin >> x;
    sort(ALL(arr)), arr.resize(unique(ALL(arr)) - begin(arr));
    N = arr.size();
    
    p.resize(N), iota(ALL(p), 0);
    sz.assign(N, 1), group.resize(N);
    for (int i = 0; i < N; ++i) group[i].eb(i);
    for (int i = 0; i < N; ++i) trie.Insert(arr[i], i);
    
    int edge_cnt = 0;
    int64_t ans = 0;
    vector<pii> minO(N); /// (dis, id)
    vector<int> vis(N);
    while (edge_cnt < N-1) {
        fill(ALL(minO), pii{INF, -1}), fill(ALL(vis), 0);
        for (int i = 0; i < N; ++i) {
            int now = R(i);
            if (vis[now]) continue;
            vis[now] = 1;
            for (auto x : group[now]) trie.Delete(arr[x]);
            // trie.Print();
            for (auto x : group[now]) {
                auto [xor_val, xor_id] = trie.FindMinXor(arr[x]);
                if (xor_val < minO[now].X) minO[now] = {xor_val, xor_id};
            }
            for (auto x : group[now]) trie.Insert(arr[x], x);
        }
        // cout << minO << "\n";
        for (int i = 0; i < N; ++i) {
            if (minO[i].Y == -1) continue;
            if (U(R(i), minO[i].Y)) ++edge_cnt, ans += minO[i].X;
        }
        // cout << p << " : " << edge_cnt << " " << ans << "\n";
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}