#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;

#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

string s;
int n;

void solve() {
    cin >> n >> s;
    s = "$" + s;
    deque<int> dq;
    for(int i = 1; i <= n; i++) {
        if(s[i] == 'L') {
            dq.push_front(i);
        }
        else if(s[i] == 'R') {
            dq.push_back(i);
        }
        else if(s[i] >= 'D') {
            int x = s[i] - 'D';
            if(SZ(dq) < x + 1) {
                cout << "ERROR\n";
                continue;
            }
            for(int j = 0; j < x; j++) {
                int tmp = dq.back();
                dq.pop_back();
                dq.push_front(tmp);
            }
            cout << dq.back() << '\n';
            dq.pop_back();
            for(int j = 0; j < x; j++) {
                int tmp = dq.front();
                dq.pop_front();
                dq.push_back(tmp);
            }
        }
        else {
            int x = s[i] - 'A';
            if(SZ(dq) < x + 1) {
                cout << "ERROR\n";
                continue;
            }
            for(int j = 0; j < x; j++) {
                int tmp = dq.front();
                dq.pop_front();
                dq.push_back(tmp);
            }
            cout << dq.front() << '\n';
            dq.pop_front();
            for(int j = 0; j < x; j++) {
                int tmp = dq.back();
                dq.pop_back();
                dq.push_front(tmp);
            }
        }
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
