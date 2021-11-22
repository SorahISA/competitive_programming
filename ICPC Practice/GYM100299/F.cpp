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
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) os << vec[i] << " ";
    return os;
}

const int dx[] = {1,  1, -1, -1};
const int dy[] = {1, -1,  1, -1};

int ans;
vector<string> vec(12);

void dfs(int nx, int ny, int now = 0) {
    ans = max(ans, now);
    for (int d = 0; d < 4; ++d) {
        if (vec[nx+dx[d]][ny+dy[d]] == 'B' and vec[nx+2*dx[d]][ny+2*dy[d]] == '#') {
            vec[nx][ny] = '#', vec[nx+dx[d]][ny+dy[d]] = '#', vec[nx+2*dx[d]][ny+2*dy[d]] = 'W';
            dfs(nx+2*dx[d], ny+2*dy[d], now+1);
            vec[nx][ny] = 'W', vec[nx+dx[d]][ny+dy[d]] = 'B', vec[nx+2*dx[d]][ny+2*dy[d]] = '#';
        }
    }
}

void solve() {
    ans = 0;
    vec[0] = vec[11] = string(12, '.');
    for (int i = 1; i <= 10; ++i) {
        cin >> vec[i], vec[i] = "." + vec[i] + ".";
    }
    
    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            if (vec[i][j] == 'W') dfs(i, j);
        }
    }
    cout << ans << "\n";
}

int32_t main(int32_t argc, char *argv[]) {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}