#include <bits/stdc++.h>
using namespace std;

using lli = long long;
using pii = pair<int, int>;
using pll = pair<lli, lli>;
template <typename T>
using Vector = vector<vector<T>>;
template <typename T>
using Prior = priority_queue<T>;
template <typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define IOS() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define X first
#define Y second
#define Push push_back
#define ALL(x) x.begin(), x.end()
#define RALL(x) x.rbegin(), x.rend()

const lli mod = 1E9 + 7;

void solve() {
    int n, m;
    string s;
    cin >> n >> m >> s;

    /// take maximum steps from N to 0 ///
    vector<int> steps;
    for (int i = n, j = max(i-m, 0); i > 0; j = max(i-m, 0)) {
        for (; j < i; ++j) {
            // printf("check: %d\n", j);
            if (s[j] == '0') {
                steps.Push(i - j);
                break;
            }
        }
        if (j == i) {
            cout << -1 << "\n";
            return;
        }
        // printf("    towards: %d\n", j);
        i = j;
    }

    accumulate(RALL(steps), 0, [](auto a, auto b) {
        cout << b << " ";
        return 0;
    });
    cout << "\n";
}

int main() {
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
