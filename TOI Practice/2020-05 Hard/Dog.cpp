#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 1E18;

pii mv[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int32_t main() {
	fastIO();

	int n, sx, sy;
	cin >> n >> sx >> sy, ++sx, ++sy;

	vector<vector<int>> MAP(n+5, vector<int>(n+5, INF));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) cin >> MAP[i][j];
	}
	
	int ans = 0;
	vector<vector<bool>> vis(n+5, vector<bool>(n+5, 0));
	queue<pii> que; que.push({sx, sy});

	while (!que.empty()) {
		pii nxt = que.front(); que.pop();
		if (vis[nxt.X][nxt.Y]) continue;
		vis[nxt.X][nxt.Y] = 1, ++ans;

		for (auto d : mv) {
			if (abs(MAP[nxt.X + d.X][nxt.Y + d.Y] - MAP[nxt.X][nxt.Y]) <= 2) {
				que.push({nxt.X + d.X, nxt.Y + d.Y});
			}
		}
	}

	cout << ans << "\n";

	return 0;
}
