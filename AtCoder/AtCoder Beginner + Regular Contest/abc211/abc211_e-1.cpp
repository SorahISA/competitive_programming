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
        os << vec[i];
    }
    return os;
}

const int dx[] = {1, 0, -1,  0};
const int dy[] = {0, 1,  0, -1};

vector<string> mp;
set<uint64_t> ans;

inline int has_marks_around(int nx, int ny) {
    for (int d = 0; d < 4; ++d) {
        if (mp[nx + dx[d]][ny + dy[d]] == '?') return 1;
    }
    return 0;
}

void dfs(int N, int K, int lx, int ly) {
    
    // for (int i = 0; i < N+2; ++i) cout << mp[i] << "\n";
    
    if (K == 0) {
        uint64_t val = 0;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (mp[i][j] == '?') val ^= (uint64_t)1 << ((i-1)*N+(j-1));
            }
        }
        return ans.insert(val), void();
    }
    
    for (int i = lx; i <= N; ++i) {
        for (int j = (i == lx ? ly+1 : 1); j <= N; ++j) {
            if (mp[i][j] == '.' and has_marks_around(i, j)) {
                mp[i][j] = '?', dfs(N, K-1, lx, ly), mp[i][j] = '.';
            }
        }
    }
}

void solve() {
    int N, K; cin >> N >> K;
    mp.assign(N+2, string(N+2, '#'));
    
    for (int i = 1; i <= N; ++i) {
        cin >> mp[i], mp[i] = '#' + mp[i] + '#';
    }
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (mp[i][j] == '.') {
                mp[i][j] = '?', dfs(N, K-1, i, j), mp[i][j] = '.';
            }
        }
    }
    cout << ans.size() << "\n";
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