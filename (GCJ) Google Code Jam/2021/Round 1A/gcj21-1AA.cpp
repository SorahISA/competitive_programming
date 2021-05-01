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

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

void solve() {
    int n; cin >> n;
    
    vector<string> arr(n);
    for (auto &str : arr) cin >> str;
    
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i].size() > arr[i-1].size()) {
            continue;
        }
        else if (arr[i].size() == arr[i-1].size() and arr[i] <= arr[i-1]) {
            ++ans, arr[i] += '0';
        }
        else if (arr[i] > arr[i-1].substr(0, arr[i].size())) {
            while (arr[i].size() < arr[i-1].size()) ++ans, arr[i] += '0';
        }
        else if (arr[i] == arr[i-1].substr(0, arr[i].size()) and
                 arr[i-1].substr(arr[i].size()) != string(arr[i-1].size() - arr[i].size(), '9')) {
            ans += arr[i-1].size() - arr[i].size();
            arr[i] = arr[i-1];
            for (int j = arr[i].size()-1; ;--j) {
                if (arr[i][j] == '9') arr[i][j] = '0';
                else {++arr[i][j]; break;}
            }
        }
        else {
            while (arr[i].size() < arr[i-1].size() + 1) ++ans, arr[i] += '0';
        }
    }
    // cerr << arr << "\n";
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}