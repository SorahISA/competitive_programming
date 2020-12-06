#pragma GCC optimize("Ofast", "unroll-loops")

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
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int maxn = 10000 + 5;

int fl[maxn], TIME[maxn];

void solve() {
    
    int op, val, mask = 0;
    set<int> que;
    
    while (cin >> op >> val) {
        if (op == 1) {
            if (mask) {--mask; continue;}
            int cnt = 0;
            for (auto x : que) cnt += x > val;
            for (auto x : que) TIME[x] += cnt;
            que.insert(val), fl[val] = 0;
        }
        if (op == 2) {
            if (mask) {--mask; cout << 1 << "\n"; continue;}
            int cnt = 0;
            for (auto x : que) cnt += x > val;
            for (auto x : que) TIME[x] += cnt;
            que.insert(val), fl[val] = 1;
        }
        if (op == -1) {
            mask += val;
            int give = min((int)que.size(), mask);
            mask -= give;
            for (int i = 1; i <= give; ++i) {
                if (fl[*que.begin()]) cout << TIME[*que.begin()] + i << "\n";
                TIME[*que.begin()] = 0, que.erase(que.begin());
            }
            for (auto x : que) TIME[x] += give * que.size() + give;
        }
    }
    
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
